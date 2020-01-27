#include<omp.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_FILE_NAME 100
#define MAX_LINES 33//number of lines/3 i.e 99/3 = 33 for a 99 line input vec1.txt 
//shuf -i 0-3600 -n 99 > vec1.txt
//shuf -i 0-3600 -n 99 > vec2.txt
//add enter at vec2.txt start
//gcc -fopenmp vectaddition.c
//(cat vec1.txt vec2.txt) | ./a.out 
int main(int argc,char *argv[])
{
    int i;
    int values1[MAX_LINES][3];
    int values2[MAX_LINES][3];
    for(int i=0;i<MAX_LINES;i++)
    {
        for(int j=0;j<3;j++)
        {
            scanf("%d",&values1[i][j]);
        }
        printf("\nGot line:");
        for(int j=0;j<3;j++)
        {
            printf("%d",values1[i][j]);
        }
    }
    for(int i=0;i<MAX_LINES;i++)
    {
        for(int j=0;j<3;j++)
        {
            scanf("%d",&values2[i][j]);
        }
        printf("\nGot line 2:");
        for(int j=0;j<3;j++)
        {
            printf("%d",values2[i][j]);
        }
    }
    int count=0;
    
    int answer[MAX_LINES][3];
    i=0;
    int j;
    #pragma omp parallel for shared(values1,values2,answer) private(i,j)
    for(i=0;i<MAX_LINES;i++)
    {
        for(j=0;j<3;j++)
        {

            printf("\n%d\t+\t%d",values1[i][j],values2[i][j]);
            answer[i][j]=values1[i][j]+values2[i][j];
            printf("=%d\n",answer[i][j]);
        }
        printf("\n");
    }

}