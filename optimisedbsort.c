#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<unistd.h>
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define MAX_FILE_NAME 100
//shuf -i 0-3600 -n 20 > numbers.txt in bash/zsh to put into file
void swap();

void bubble_normal(int A[], int SIZE)
{
	int N = SIZE;
	int i=0, j=0; 
	int first;
	double start,end;
	start=omp_get_wtime();
	for( i = 0; i < N-1; i++ )
	{
		first = i % 2; 
		for( j = first; j < N-1; j += 1 )
		{
			if( A[ j ] > A[ j+1 ] )
			{
				swap( &A[ j ], &A[ j+1 ] );
			}
		}
	}
end=omp_get_wtime();
for(i=0;i<N;i++)
	{
		printf(ANSI_COLOR_BLUE" %d "ANSI_COLOR_RESET,A[i]);
	}
	// for(i=0;i<N;i++)
	// {
	// 	printf(" %d",A[i]);
	// }

printf("Time Serial= %f\n",(end-start));
printf("----------------------------\n");
}
int main (int argc, char *argv[]) {

	for(int i=10;i<=1000000000;i=i*10){
		char str[]="shuf -i 0-3600 -n ";
		char input_size[50];
		printf("input size=%d\n",i);
		sprintf(input_size,"%d",i);
		strcat(str,input_size);
		strcat(str," > numbers.txt");
		system(str);
	//system("shuf -i 0-3600 -n 20 > numbers.txt");
	FILE *fp; 
    int count = 0;  // Line counter (result) 
    char filename[MAX_FILE_NAME]; 
    char c;  // To store a character read from file 
  
    // Get file name from user. The file should be 
    // either in current folder or complete path should be provided 
    printf("Reading numbers.txt...\n");
  
    // Open the file 
    fp = fopen("numbers.txt", "r"); 
  
    // Check if file exists 
    if (fp == NULL) 
    { 
        printf("Could not open file %s", filename); 
        return 0; 
    } 
  
    // Extract characters from file and store in character c 
    for (c = getc(fp); c != EOF; c = getc(fp)) 
        if (c == '\n') // Increment count if this character is newline 
            count = count + 1; 
  
    // Close the file 
    fclose(fp); 
	FILE *myFile;

    myFile=fopen("numbers.txt","r");
    int SIZE = count;
	int A[SIZE];
	for(int i=0;i<SIZE;i++)
	{
	    fscanf(myFile,"%d",&A[i]);
	}
	//int A[5] = {6,9,1,3,7};
	int N = SIZE;
	int i=0, j=0; 
	int first;
	double start,end;
	start=omp_get_wtime();
	for( i = 0; i < N-1; i++ )
	{
		first = i % 2; 
		#pragma omp parallel for default(none),shared(A,first,N)
		for( j = first; j < N-1; j += 1 )
		{
			if( A[ j ] > A[ j+1 ] )
			{
				swap( &A[ j ], &A[ j+1 ] );
			}
		}
	}
end=omp_get_wtime();
	for(i=0;i<N;i++)
	{
		printf(ANSI_COLOR_BLUE" %d"ANSI_COLOR_RESET,A[i]);
	}

printf("Time Parallel= %f\n",(end-start));
printf("\n");
sleep(10);
bubble_normal(A,count);
}
}

void swap(int *num1, int *num2)
{

	int temp = *num1;
	*num1 =  *num2;
	*num2 = temp;
}