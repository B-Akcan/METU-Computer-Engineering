#include <stdio.h>

int main() {
    int length, number_of_tribes, i, j, k, armies[100][7], width, height, time, position, speed, attack_interval, number_of_attacks, wall[100000];
    scanf("%i %i", &length, &number_of_tribes);
    for (j=0 ; j<=length ; j++)
        wall[j]=1;
    for (; j<100000 ; j++)
        wall[j]=0;
    for (i=0 ; i<number_of_tribes ; i++)
    {
        scanf("%i %i %i %i %i %i %i", &armies[i][0], &armies[i][1], &armies[i][2], &armies[i][3], &armies[i][4], &armies[i][5], &armies[i][6]);
        width=armies[i][0], height=armies[i][1], time=armies[i][2], position=armies[i][3], speed=armies[i][4], attack_interval=armies[i][5], number_of_attacks=armies[i][6];
        while (number_of_attacks > 0)
        {
            for (k=position ; k < position + width ; k++)
            {
                if (k >= 0 && wall[k] != 0 && wall[k] < height)
                    wall[k] = height;
            }
            position += attack_interval * speed;
            number_of_attacks--;
        }
    }
    time -= 1;
    j=0;
    while (j <= length)
    {
        printf("%i", wall[j]);
        j++;
        if (j != length+1)
            printf(" ");
    }
    printf("\n");
    return 0;
}