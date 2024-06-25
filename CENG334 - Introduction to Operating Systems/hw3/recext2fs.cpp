#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include "ext2fs.h"
#include "identifier.cpp"
#include <vector>
#include <typeinfo>

using namespace std;

#define BLOCK_OFFSET(block_id) (block_id * block_size)
#define INODE_OFFSET(inode_id) ((inode_id - 1) * EXT2_INODE_SIZE)

void print_filesystem_preorder(struct ext2_inode *inode, int hyphen_count);

int image;
int image2;
uint32_t block_size;
uint8_t *identifier;
struct ext2_block_group_descriptor *bgd_table;
struct ext2_super_block super;
int main(int argc, char* argv[])
{
	struct ext2_block_group_descriptor curr_bg;
	uint32_t num_block_groups;
	uint32_t inodes_per_group;
	unsigned char *inode_bitmap;
	struct ext2_inode root;

	identifier = parse_identifier(argc, argv);

	// Open image
	if ((image = open(argv[1], O_RDWR)) < 0)
		return 1;
	if ((image2 = open(argv[1], O_RDWR)) < 0)
		return 1;

	// Read super block
	lseek(image, EXT2_BOOT_BLOCK_SIZE, SEEK_SET);
	read(image, &super, sizeof(ext2_super_block));

	if (super.magic != EXT2_SUPER_MAGIC)
		return 1;

	// Read values that we will need
	block_size = EXT2_UNLOG(super.log_block_size);
	inodes_per_group = super.inodes_per_group;
	num_block_groups = (inodes_per_group + super.inode_count - 1) / inodes_per_group;

	// Allocate memory
	inode_bitmap = new unsigned char[block_size];
	bgd_table = new struct ext2_block_group_descriptor[num_block_groups];

	// Read block group descriptor table
	lseek(image, (super.first_data_block+1) * block_size, SEEK_SET);
	read(image, bgd_table, sizeof(ext2_block_group_descriptor)*num_block_groups);

	// Read root inode
	lseek(image, BLOCK_OFFSET(bgd_table[0].inode_table) + INODE_OFFSET(2), SEEK_SET);
	read(image, &root, sizeof(ext2_inode));

	// Set bits of reserved inodes
	lseek(image, BLOCK_OFFSET(bgd_table[0].inode_bitmap), SEEK_SET);
	read(image, inode_bitmap, block_size);
	for (int curr_inode_no = 1; curr_inode_no < super.first_inode; curr_inode_no++)
	{
		int i = (curr_inode_no - 1) / 8;
		int j = (curr_inode_no - 1) % 8;
		inode_bitmap[i] |= (1 << j);
	}
	lseek(image, BLOCK_OFFSET(bgd_table[0].inode_bitmap), SEEK_SET);
	write(image, inode_bitmap, block_size);

	// Iterate all block groups
	for (int curr_bgID = 0; curr_bgID < num_block_groups; curr_bgID++)
	{
		// Read the inode bitmap of the current block group
		lseek(image, BLOCK_OFFSET(bgd_table[curr_bgID].inode_bitmap), SEEK_SET);
		read(image, inode_bitmap, block_size);

		ext2_inode curr_inode;

		// Iterate all inodes in a block group
		for (int curr_inode_no = 1; curr_inode_no < inodes_per_group+1; curr_inode_no++)
		{
			// Read the current inode
			lseek(image, BLOCK_OFFSET(bgd_table[curr_bgID].inode_table) + INODE_OFFSET(curr_inode_no), SEEK_SET);
			read(image, &curr_inode, sizeof(ext2_inode));

			// If current inode is not deleted, set its bit in the bitmap
			if (curr_inode.creation_time > curr_inode.deletion_time)
			{
				int i = (curr_inode_no - 1) / 8;
				int j = (curr_inode_no - 1) % 8;
				inode_bitmap[i] |= (1 << j);
			}
		}

		// Write the inode bitmap of the current block group
		lseek(image, BLOCK_OFFSET(bgd_table[curr_bgID].inode_bitmap), SEEK_SET);
		write(image, inode_bitmap, block_size);
	}

	//cout << "-root/" << endl;
	//print_filesystem_preorder(&root, 2);

	delete [] inode_bitmap;
	delete [] bgd_table;

	close(image);
	close(image2);

	return 0;
}

void print_filesystem_preorder(struct ext2_inode *inode, int hyphen_count)
{
	if (inode == NULL)
		return;

	// Read all direct block ids
	uint32_t block_ids[EXT2_NUM_DIRECT_BLOCKS];
	for (int i=0; i<EXT2_NUM_DIRECT_BLOCKS; i++)
		block_ids[i] = inode->direct_blocks[i];

	// Read all direct blocks
	unsigned char direct_blocks[EXT2_NUM_DIRECT_BLOCKS][block_size];
	for (int i=0; i<EXT2_NUM_DIRECT_BLOCKS; i++)
	{
		lseek(image, BLOCK_OFFSET(block_ids[i]), SEEK_SET);
		read(image, direct_blocks[i], block_size);
	}

	// Iterate all direct blocks
	for (int i=0; i<EXT2_NUM_DIRECT_BLOCKS; i++)
	{
		if (block_ids[i] == 0)
			continue;

		lseek(image, BLOCK_OFFSET(block_ids[i]), SEEK_SET);

		// Iterate all dir entries in the block
		int len = 0;
		int first_or_second = 0;
		while (len < block_size)
		{
			first_or_second++;

			// Read ext2_dir_entry excluding name
			struct ext2_dir_entry ext2_dir_ent;
			read(image, &ext2_dir_ent, 8);
			
			// Read name field of dir_ent
			char name[(int) ext2_dir_ent.name_length];
			read(image, name, (int) ext2_dir_ent.name_length);

			lseek(image, ext2_dir_ent.length - ext2_dir_ent.name_length - sizeof(ext2_dir_ent), SEEK_CUR);

			if (first_or_second > 2)
			{
				// Print directory or file name with hyphens
				if ((int) ext2_dir_ent.file_type == EXT2_D_FTYPE)
				{
					for (int k=0; k<hyphen_count; k++)
						cout << '-';
					cout << string(name, ext2_dir_ent.name_length) << endl;
				}
				else if ((int) ext2_dir_ent.file_type == EXT2_D_DTYPE)
				{
					for (int k=0; k<hyphen_count; k++)
						cout << '-';
					cout << string(name, ext2_dir_ent.name_length) << "/" << endl;

					// If directory, call the function again with child inodes
					struct ext2_inode child;
					int bg_id = (ext2_dir_ent.inode - 1) / super.inodes_per_group;
					lseek(image2, BLOCK_OFFSET(bgd_table[bg_id].inode_table) + INODE_OFFSET(ext2_dir_ent.inode), SEEK_SET);
					read(image2, &child, sizeof(ext2_inode));

					print_filesystem_preorder(&child, hyphen_count+1);
				}
			}

			len += ext2_dir_ent.length;
		}
	}
}
