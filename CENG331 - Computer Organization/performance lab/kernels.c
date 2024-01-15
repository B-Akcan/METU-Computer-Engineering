/********************************************************
 * Kernels to be optimized for the CS:APP Performance Lab
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
/*
 * Please fill in the following team_t struct
 */
team_t team = {
        "BatuMert",    /* Team Name */

        "e258018",    /* First student ID */
        "Batuhan Akçan",    /* First student name */
        
        "e251692",        /* Second student ID */
        "Mert Sönmezer"         /* Second student name */
};


/*******************************************************
 * BATCHED MATRIX MULTIPLICATION \W SUM REDUCTION KERNEL
 *******************************************************/

/*********************************************************************************
 * Your different versions of the batched matrix multiplication functions go here
 *********************************************************************************/

/*
 * naive_batched_mm - The naive baseline version of batched matrix multiplication
 */
 
char naive_batched_mm_descr[] = "naive_batched_mm: Naive baseline implementation";
void naive_batched_mm(int dim, int *b_mat, int *mat, int *dst) {
    int i,j,k,l;
    
    for (i = 0; i < dim; i++) {
        for (j = 0; j < dim; j++) {
            for (k = 0; k < dim; k++) {
            	if (i == 0){
            	    dst[RIDX(j, k, dim)] = 0;
            	}
            	for (l = 0; l < dim; l++){
                    dst[RIDX(j, k, dim)] += b_mat[RIDX(i*dim+j, l, dim)] * mat[RIDX(l, k, dim)];
                }
            }
        }
    }
}

/*
 * batched_mm - Your current working version of batched matrix multiplication
 * IMPORTANT: This is the version you will be graded on
 */  
char batched_mm_descr[] = "Batched MM with sum reduction: Current working version";
void batched_mm(int dim, int *b_mat, int *mat, int *dst)
{
	int size = dim * dim;
    int i,j,k;
	int *temp = (int *) malloc(size * sizeof(int));

	// Result Matrix Initialization
    for (i = 0; i < size; i += 32)
    {
        temp[i] = 0;
        temp[i+1] = 0;
        temp[i+2] = 0;
        temp[i+3] = 0;
        temp[i+4] = 0;
        temp[i+5] = 0;
        temp[i+6] = 0;
        temp[i+7] = 0;
        temp[i+8] = 0;
        temp[i+9] = 0;
        temp[i+10] = 0;
        temp[i+11] = 0;
        temp[i+12] = 0;
        temp[i+13] = 0;
        temp[i+14] = 0;
        temp[i+15] = 0;
        temp[i+16] = 0;
        temp[i+17] = 0;
        temp[i+18] = 0;
        temp[i+19] = 0;
        temp[i+20] = 0;
        temp[i+21] = 0;
        temp[i+22] = 0;
        temp[i+23] = 0;
        temp[i+24] = 0;
        temp[i+25] = 0;
        temp[i+26] = 0;
        temp[i+27] = 0;
        temp[i+28] = 0;
        temp[i+29] = 0;
        temp[i+30] = 0;
        temp[i+31] = 0;
    }

    // Summing each matrix value in the b_mat
	int j_times_dim, i_times_size=0, dim_cube = size*dim, i_times_size_plus_j_times_dim, i_times_size_plus_j_times_dim_plus_k;
    int j_times_dim_plus_k;
	while (i_times_size < dim_cube)
	{
        j_times_dim = 0;
		while (j_times_dim < size)
		{
            i_times_size_plus_j_times_dim = i_times_size + j_times_dim;
            j_times_dim_plus_k = j_times_dim + dim - 1;
            i_times_size_plus_j_times_dim_plus_k = i_times_size_plus_j_times_dim + dim - 1;
			while (j_times_dim_plus_k >= j_times_dim)
			{
				temp[j_times_dim_plus_k] += b_mat[i_times_size_plus_j_times_dim_plus_k];
                temp[j_times_dim_plus_k - 1] += b_mat[i_times_size_plus_j_times_dim_plus_k - 1];
                temp[j_times_dim_plus_k - 2] += b_mat[i_times_size_plus_j_times_dim_plus_k - 2];
                temp[j_times_dim_plus_k - 3] += b_mat[i_times_size_plus_j_times_dim_plus_k - 3];
                temp[j_times_dim_plus_k - 4] += b_mat[i_times_size_plus_j_times_dim_plus_k - 4];
                temp[j_times_dim_plus_k - 5] += b_mat[i_times_size_plus_j_times_dim_plus_k - 5];
                temp[j_times_dim_plus_k - 6] += b_mat[i_times_size_plus_j_times_dim_plus_k - 6];
                temp[j_times_dim_plus_k - 7] += b_mat[i_times_size_plus_j_times_dim_plus_k - 7];
                temp[j_times_dim_plus_k - 8] += b_mat[i_times_size_plus_j_times_dim_plus_k - 8];
                temp[j_times_dim_plus_k - 9] += b_mat[i_times_size_plus_j_times_dim_plus_k - 9];
                temp[j_times_dim_plus_k - 10] += b_mat[i_times_size_plus_j_times_dim_plus_k - 10];
                temp[j_times_dim_plus_k - 11] += b_mat[i_times_size_plus_j_times_dim_plus_k - 11];
                temp[j_times_dim_plus_k - 12] += b_mat[i_times_size_plus_j_times_dim_plus_k - 12];
                temp[j_times_dim_plus_k - 13] += b_mat[i_times_size_plus_j_times_dim_plus_k - 13];
                temp[j_times_dim_plus_k - 14] += b_mat[i_times_size_plus_j_times_dim_plus_k - 14];
                temp[j_times_dim_plus_k - 15] += b_mat[i_times_size_plus_j_times_dim_plus_k - 15];
                temp[j_times_dim_plus_k - 16] += b_mat[i_times_size_plus_j_times_dim_plus_k - 16];
                temp[j_times_dim_plus_k - 17] += b_mat[i_times_size_plus_j_times_dim_plus_k - 17];
                temp[j_times_dim_plus_k - 18] += b_mat[i_times_size_plus_j_times_dim_plus_k - 18];
                temp[j_times_dim_plus_k - 19] += b_mat[i_times_size_plus_j_times_dim_plus_k - 19];
                temp[j_times_dim_plus_k - 20] += b_mat[i_times_size_plus_j_times_dim_plus_k - 20];
                temp[j_times_dim_plus_k - 21] += b_mat[i_times_size_plus_j_times_dim_plus_k - 21];
                temp[j_times_dim_plus_k - 22] += b_mat[i_times_size_plus_j_times_dim_plus_k - 22];
                temp[j_times_dim_plus_k - 23] += b_mat[i_times_size_plus_j_times_dim_plus_k - 23];
                temp[j_times_dim_plus_k - 24] += b_mat[i_times_size_plus_j_times_dim_plus_k - 24];
                temp[j_times_dim_plus_k - 25] += b_mat[i_times_size_plus_j_times_dim_plus_k - 25];
                temp[j_times_dim_plus_k - 26] += b_mat[i_times_size_plus_j_times_dim_plus_k - 26];
                temp[j_times_dim_plus_k - 27] += b_mat[i_times_size_plus_j_times_dim_plus_k - 27];
                temp[j_times_dim_plus_k - 28] += b_mat[i_times_size_plus_j_times_dim_plus_k - 28];
                temp[j_times_dim_plus_k - 29] += b_mat[i_times_size_plus_j_times_dim_plus_k - 29];
                temp[j_times_dim_plus_k - 30] += b_mat[i_times_size_plus_j_times_dim_plus_k - 30];
                temp[j_times_dim_plus_k - 31] += b_mat[i_times_size_plus_j_times_dim_plus_k - 31];

                j_times_dim_plus_k -= 32;
                i_times_size_plus_j_times_dim_plus_k -= 32;
			}
            j_times_dim += dim;
		}
        i_times_size += size;
	}

    // Matrix Multiplication
    int res;
    int offset = dim*(dim-1),initIndex = dim >> 5;
    int *rwSrc2_1 = malloc(size * sizeof(int));
    int *rwSrc2_2 = mat, *rwSrc2_3 = rwSrc2_1;
    int *tmpSrc2_1, *tmpSrc2_2, *tmpSrc2_3, *tmpSrc2_4, *dstTmp, *tmpSrc1;

    for (i = dim; i > 0 ; --i) 
    {
        tmpSrc2_1 = rwSrc2_3;
        tmpSrc2_2 = rwSrc2_2;
        for (j = initIndex; j > 0 ; --j) 
        {
            *tmpSrc2_1  = tmpSrc2_2[0];
            tmpSrc2_1  += dim;
            *tmpSrc2_1  = tmpSrc2_2[1];
            tmpSrc2_1  += dim;
            *tmpSrc2_1  = tmpSrc2_2[2];
            tmpSrc2_1  += dim;
            *tmpSrc2_1  = tmpSrc2_2[3];
            tmpSrc2_1  += dim;
            *tmpSrc2_1  = tmpSrc2_2[4];
            tmpSrc2_1  += dim;
            *tmpSrc2_1  = tmpSrc2_2[5];
            tmpSrc2_1  += dim;
            *tmpSrc2_1  = tmpSrc2_2[6];
            tmpSrc2_1  += dim;
            *tmpSrc2_1  = tmpSrc2_2[7];
            tmpSrc2_1  += dim;
            *tmpSrc2_1  = tmpSrc2_2[8];
            tmpSrc2_1  += dim;
            *tmpSrc2_1  = tmpSrc2_2[9];
            tmpSrc2_1  += dim;
            *tmpSrc2_1  = tmpSrc2_2[10];
            tmpSrc2_1  += dim;
            *tmpSrc2_1  = tmpSrc2_2[11];
            tmpSrc2_1  += dim;
            *tmpSrc2_1  = tmpSrc2_2[12];
            tmpSrc2_1  += dim;
            *tmpSrc2_1  = tmpSrc2_2[13];
            tmpSrc2_1  += dim;
            *tmpSrc2_1  = tmpSrc2_2[14];
            tmpSrc2_1  += dim;
            *tmpSrc2_1  = tmpSrc2_2[15];
            tmpSrc2_1  += dim;
            *tmpSrc2_1  = tmpSrc2_2[16];
            tmpSrc2_1  += dim;
            *tmpSrc2_1  = tmpSrc2_2[17];
            tmpSrc2_1  += dim;
            *tmpSrc2_1  = tmpSrc2_2[18];
            tmpSrc2_1  += dim;
            *tmpSrc2_1  = tmpSrc2_2[19];
            tmpSrc2_1  += dim;
            *tmpSrc2_1  = tmpSrc2_2[20];
            tmpSrc2_1  += dim;
            *tmpSrc2_1  = tmpSrc2_2[21];
            tmpSrc2_1  += dim;
            *tmpSrc2_1  = tmpSrc2_2[22];
            tmpSrc2_1  += dim;
            *tmpSrc2_1  = tmpSrc2_2[23];
            tmpSrc2_1  += dim;
            *tmpSrc2_1  = tmpSrc2_2[24];
            tmpSrc2_1  += dim;
            *tmpSrc2_1  = tmpSrc2_2[25];
            tmpSrc2_1  += dim;
            *tmpSrc2_1  = tmpSrc2_2[26];
            tmpSrc2_1  += dim;
            *tmpSrc2_1  = tmpSrc2_2[27];
            tmpSrc2_1  += dim;
            *tmpSrc2_1  = tmpSrc2_2[28];
            tmpSrc2_1  += dim;
            *tmpSrc2_1  = tmpSrc2_2[29];
            tmpSrc2_1  += dim;
            *tmpSrc2_1  = tmpSrc2_2[30];
            tmpSrc2_1  += dim;
            *tmpSrc2_1  = tmpSrc2_2[31];
            tmpSrc2_1  += dim;

            tmpSrc2_2 += 32;
        }
        rwSrc2_2 += dim;
        ++rwSrc2_3;
    }    

    dst += dim - 1;
    rwSrc2_1 += offset;

    initIndex = dim >> 5;
    for (i = dim; i > 0 ; --i) 
    {   
        tmpSrc2_3 = rwSrc2_1;
        dstTmp  = dst;
        for (j = dim; j > 0 ; --j) 
        {
            res = 0;
            tmpSrc1  = temp;
            tmpSrc2_4 = tmpSrc2_3;

            for (k = initIndex; k > 0 ; --k) 
            {
                res += (tmpSrc1[0] * tmpSrc2_4[0]) + (tmpSrc1[1] * tmpSrc2_4[1]) + (tmpSrc1[2] * tmpSrc2_4[2]) +
                        (tmpSrc1[3] * tmpSrc2_4[3]) + (tmpSrc1[4] * tmpSrc2_4[4]) + (tmpSrc1[5] * tmpSrc2_4[5]) +
                        (tmpSrc1[6] * tmpSrc2_4[6]) + (tmpSrc1[7] * tmpSrc2_4[7]) + (tmpSrc1[8] * tmpSrc2_4[8]) +
                        (tmpSrc1[9] * tmpSrc2_4[9]) + (tmpSrc1[10] * tmpSrc2_4[10]) + (tmpSrc1[11] * tmpSrc2_4[11]) +
                        (tmpSrc1[12] * tmpSrc2_4[12]) + (tmpSrc1[13] * tmpSrc2_4[13]) + (tmpSrc1[14] * tmpSrc2_4[14]) +
                        (tmpSrc1[15] * tmpSrc2_4[15]) + (tmpSrc1[16] * tmpSrc2_4[16]) + (tmpSrc1[17] * tmpSrc2_4[17]) +
                        (tmpSrc1[18] * tmpSrc2_4[18]) + (tmpSrc1[19] * tmpSrc2_4[19]) + (tmpSrc1[20] * tmpSrc2_4[20]) +
                        (tmpSrc1[21] * tmpSrc2_4[21]) + (tmpSrc1[22] * tmpSrc2_4[22]) + (tmpSrc1[23] * tmpSrc2_4[23]) +
                        (tmpSrc1[24] * tmpSrc2_4[24]) + (tmpSrc1[25] * tmpSrc2_4[25]) + (tmpSrc1[26] * tmpSrc2_4[26]) +
                        (tmpSrc1[27] * tmpSrc2_4[27]) + (tmpSrc1[28] * tmpSrc2_4[28]) + (tmpSrc1[29] * tmpSrc2_4[29]) +
                        (tmpSrc1[30] * tmpSrc2_4[30]) + (tmpSrc1[31] * tmpSrc2_4[31]);
                tmpSrc1 += 32;
                tmpSrc2_4 += 32;
            }

            *dstTmp = res;
            --dstTmp;
            tmpSrc2_3 -= dim;
        }
        dst += dim;
        temp += dim;
    }  
}

/*********************************************************************
 * register_batched_mm_functions - Register all of your different versions
 *     of the batched matrix multiplication functions  with the driver by calling the
 *     add_batched_mm_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.
 *********************************************************************/

void register_batched_mm_functions() {
    add_batched_mm_function(&naive_batched_mm, naive_batched_mm_descr);
    add_batched_mm_function(&batched_mm, batched_mm_descr);
    /* ... Register additional test functions here */
}




/************************
 * POINT REFLECTION KERNEL
 ************************/

/*********************************************************
 * Your different versions of the point reflection go here
 *********************************************************/

/*
 * naive_reflect - The naive baseline version of point reflection
 */
char naive_reflect_descr[] = "Naive Point Reflection: Naive baseline implementation";
void naive_reflect(int dim, int *src, int *dst) {
    int i, j;

    for (i = 0; i < dim; i++) {
		for (j = 0; j < dim; j++) {
	    	dst[RIDX(dim-1-i, dim-1-j, dim)] = src[RIDX(i, j, dim)];
		}
    }
}


/*
 * reflect - Your current working version of reflect
 * IMPORTANT: This is the version you will be graded on
 */
char reflect_descr[] = "Point Reflection: Current working version";
void reflect(int dim, int *src, int *dst)
{
	int dim_calculation = dim * dim;
	dim_calculation -= 1;
	
	int dim_times_i = 0;
	
	int ni, dim_times_i_plus_j, ni_minus_j, dim_times_i_plus_dim;
	for (int i = 0; i < dim; ++i)
	{
		ni = dim_calculation - dim_times_i;
		dim_times_i_plus_j = dim_times_i;
		ni_minus_j = ni;
		dim_times_i_plus_dim = dim_times_i + dim;
		
		while (dim_times_i_plus_j < dim_times_i_plus_dim)
		{
			dst[ni_minus_j] = src[dim_times_i_plus_j];
			dst[ni_minus_j - 1] = src[dim_times_i_plus_j + 1];
			dst[ni_minus_j - 2] = src[dim_times_i_plus_j + 2];
			dst[ni_minus_j - 3] = src[dim_times_i_plus_j + 3];
            dst[ni_minus_j - 4] = src[dim_times_i_plus_j + 4];
			dst[ni_minus_j - 5] = src[dim_times_i_plus_j + 5];
			dst[ni_minus_j - 6] = src[dim_times_i_plus_j + 6];
			dst[ni_minus_j - 7] = src[dim_times_i_plus_j + 7];
            dst[ni_minus_j - 8] = src[dim_times_i_plus_j + 8];
			dst[ni_minus_j - 9] = src[dim_times_i_plus_j + 9];
			dst[ni_minus_j - 10] = src[dim_times_i_plus_j + 10];
			dst[ni_minus_j - 11] = src[dim_times_i_plus_j + 11];
            dst[ni_minus_j - 12] = src[dim_times_i_plus_j + 12];
			dst[ni_minus_j - 13] = src[dim_times_i_plus_j + 13];
			dst[ni_minus_j - 14] = src[dim_times_i_plus_j + 14];
			dst[ni_minus_j - 15] = src[dim_times_i_plus_j + 15];
            dst[ni_minus_j - 16] = src[dim_times_i_plus_j + 16];
			dst[ni_minus_j - 17] = src[dim_times_i_plus_j + 17];
			dst[ni_minus_j - 18] = src[dim_times_i_plus_j + 18];
			dst[ni_minus_j - 19] = src[dim_times_i_plus_j + 19];
            dst[ni_minus_j - 20] = src[dim_times_i_plus_j + 20];
			dst[ni_minus_j - 21] = src[dim_times_i_plus_j + 21];
			dst[ni_minus_j - 22] = src[dim_times_i_plus_j + 22];
			dst[ni_minus_j - 23] = src[dim_times_i_plus_j + 23];
            dst[ni_minus_j - 24] = src[dim_times_i_plus_j + 24];
			dst[ni_minus_j - 25] = src[dim_times_i_plus_j + 25];
			dst[ni_minus_j - 26] = src[dim_times_i_plus_j + 26];
			dst[ni_minus_j - 27] = src[dim_times_i_plus_j + 27];
            dst[ni_minus_j - 28] = src[dim_times_i_plus_j + 28];
			dst[ni_minus_j - 29] = src[dim_times_i_plus_j + 29];
			dst[ni_minus_j - 30] = src[dim_times_i_plus_j + 30];
			dst[ni_minus_j - 31] = src[dim_times_i_plus_j + 31];
            

			dim_times_i_plus_j += 32;
			ni_minus_j -= 32;
		}

		dim_times_i += dim;
	}
}

/******************************************************************************
 * register_reflect_functions - Register all of your different versions
 *     of the reflect with the driver by calling the
 *     add_reflect_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 ******************************************************************************/

void register_reflect_functions() {
    add_reflect_function(&naive_reflect, naive_reflect_descr);
    add_reflect_function(&reflect, reflect_descr);
    /* ... Register additional test functions here */
}
