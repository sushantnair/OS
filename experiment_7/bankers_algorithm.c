#include<stdio.h>
void main()
{
    printf("------------------------------------------------------------------\n");
    printf("------------------------BANKER'S ALGORITHM------------------------\n"); 
    printf("------------------------------------------------------------------\n");
    int i, j, k, np, nr;
    np = 5; //Number of processes
    nr = 3; //Number of resources
    int alloc[np][nr];
    int max[np][nr];
    int avail[nr];
    printf("This program deals with five processes P0 through P4.\n");
    printf("There are three resources A, B and C.\n");
    int ch_val;
    printf("Enter 1 for default values of processes and resources.\n");
    printf("Enter 2 to input custom values of processes and resources.\nEnter your choice: ");
    scanf("%d", &ch_val);
    switch(ch_val)
    {
        case 1:     
            // Initialize alloc matrix
            alloc[0][0] = 0;
            alloc[0][1] = 1;
            alloc[0][2] = 0;
            alloc[1][0] = 2;
            alloc[1][1] = 0;
            alloc[1][2] = 0;
            alloc[2][0] = 3;
            alloc[2][1] = 0;
            alloc[2][2] = 2;
            alloc[3][0] = 2;
            alloc[3][1] = 1;
            alloc[3][2] = 1;
            alloc[4][0] = 0;
            alloc[4][1] = 0;
            alloc[4][2] = 2;
            // Initialize max matrix
            max[0][0] = 7;
            max[0][1] = 5;
            max[0][2] = 3;
            max[1][0] = 3;
            max[1][1] = 2;
            max[1][2] = 2;
            max[2][0] = 9;
            max[2][1] = 0;
            max[2][2] = 2;
            max[3][0] = 2;
            max[3][1] = 2;
            max[3][2] = 2;
            max[4][0] = 4;
            max[4][1] = 3;
            max[4][2] = 3;
             // Available Resources
            avail[0] = 3;
            avail[1] = 3;
            avail[2] = 2;
            break;
        case 2:
            for(i = 0; i < np; i++){
                for(j = 0; j < nr; j++){
                    printf("\nIn Allocation Matrix, enter value for P%d%d: ", i, j);
                    scanf("%d", &alloc[i][j]);
                    printf("\nIn Maximum Matrix, enter value for P%d%d: ", i, j);
                    scanf("%d", &max[i][j]);
                }
            }
            for(j = 0; j < nr; j++){
                printf("\nEnter Available Resource %d: ", j);
                scanf("%d", &avail[j]);
            }
            break;
        default:
            printf("\nPlease enter correct choice and try again.");
    }   
    int f[np], ans[np], ind = 0;
    for(k = 0; k < np; k++){
        f[k] = 0;
    }
    int need[np][nr];
    for(i = 0; i < np; i++){
        for(j = 0; j < nr; j++)
            need[i][j] = max[i][j] - alloc[i][j];
    }
    // Print the table headers
    printf("-----------------------------------------------------------------\n");
    printf("      ALLOCATION      |     MAX     |  AVAILABLE  |    NEED     |\n");
    printf("-----------------------------------------------------------------\n");
    printf("Process   A    B    C |  A   B   C  |  A   B   C  |  A   B   C  |\n");
    printf("-----------------------------------------------------------------\n");
    int y = 0;
    for(k = 0; k < 5; k++){
        for(i = 0; i < np; i++){
            if(f[i] == 0){
                int flag = 0;
                for(j = 0; j < nr; j++){
                    if(need[i][j] > avail[j]){
                        flag = 1;
                        break;
                    }
                }
                if(flag == 0){
                    ans[ind++] = i;
                    for(y = 0; y < nr; y++)
                        avail[y] += alloc[i][y];
                    f[i] = 1;
                    printf("P%d        %d    %d    %d |  %d   %d   %d  |  %d   %d   %d  |  %d   %d   %d  |\n",
                           i, alloc[i][0], alloc[i][1], alloc[i][2],
                           max[i][0], max[i][1], max[i][2],
                           avail[0], avail[1], avail[2],
                           need[i][0], need[i][1], need[i][2]);
                }
            }
        }
    }
    printf("------------------------------------------------------------------\n");
    int flag = 1;
    for(int i = 0; i < np; i++){
        if(f[i] == 0){
            flag = 0;
            printf("\nThe system is not safe.");
            break;
        }
    }
    if(flag == 1){
        printf("\nFollowing is the SAFE Sequence\n");
        for(i = 0; i < np - 1; i++)
            printf("P%d -> ", ans[i]);
        printf("P%d\n", ans[np - 1]);
    }
}