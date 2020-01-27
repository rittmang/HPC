#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

void print(int a[], int n)
{
	for(int i=0; i<n; i++)
		printf("%d ",a[i]);
	printf("\n");
}
void bubsort(int array[],int size)
{
	int temp;

	for (int i = 0; i < size/2; i++)
	{
		#pragma omp parallel for private(temp)  
		for (int j = 0; j < size-1; j+=2) //for even phase
		{
			if (array[j]>array[j+1])
			{
				temp=array[j];
				array[j]=array[j+1];
				array[j+1]=temp;
			}
		}
		#pragma omp parallel for private(temp)  
		for (int j = 1; j < size-1; j+=2) //for odd phase
		{
			if (array[j]>array[j+1])
			{
				temp=array[j];
				array[j]=array[j+1];
				array[j+1]=temp;
			}
		}	
	}	
}// end of parallel bubble sort

int main()
{
    int size;
    printf("Enter size of array:");
    scanf("%d",&size);
    int a[size];
    for(int i=0;i<size;i++)
        scanf("%d",&a[i]);
    printf("\nUnsorted array:");
    print(a,size);

    bubsort(a,size);
    printf("\nSorted array:");
    print(a,size);
    
}
