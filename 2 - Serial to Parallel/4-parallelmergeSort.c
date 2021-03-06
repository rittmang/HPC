#include<stdio.h>
#include<omp.h>
//using namespace std;
//performs the bottom up combine operation
void merge(int a[], int l, int m, int r)
{
	int temp[m-l+1], temp2[r-m];
	//copy first part to temporary array
	for(int i=0; i<(m-l+1); i++)
		temp[i]=a[l+i];
	//copy second part to temporary array
	for(int i=0; i<(r-m); i++)
		temp2[i]=a[m+1+i];
	int i=0, j=0, k=l;
	//combine the arrays on the basis of order
	while(i<(m-l+1) && j<(r-m))
	{
		if(temp[i]<temp2[j])
			a[k++]=temp[i++];
		else
			a[k++]=temp2[j++];
	}
	//to combine the remainder of the two arrays
	while(i<(m-l+1))
		a[k++]=temp[i++];
	while(j<(r-m))
		a[k++]=temp2[j++];

}
/* 
This function is the main hotspot of the algorithm which I have chosen to parallelise
The calls labelled call 1 and call 2 are essentially independent since they are operating on distinct
parts of the array and hence can be called in parallel.
*/

void mergeSort(int a[], int l, int r)
{
	if(l<r)
	{
		//cout<<"came here";
		int m=(l+r)/2;
		#pragma omp parallel sections num_threads(2)
		{
			#pragma omp section
			{
				mergeSort(a,l,m); //call 1
			}
			#pragma omp section
			{
				mergeSort(a,m+1,r); //call 2
			}
		}
		merge(a,l,m,r); //this function is outside the parallel sections since it merges and access the same data 
	}
}
//a simple print function to print all the elements
void print(int a[], int n)
{
	for(int i=0; i<n; i++)
		printf("%d ",a[i]);
	printf("\n");
}
int main()
{
	int n;
    printf("Input length");
	scanf("%d",&n);
	int a[n];
	for(int i=0; i<n; i++)
		scanf("%d",&a[i]);
	printf("\nUnsorted array; ");
	print(a,n);
	//call should be to a wrapper function that calls the mergeSort function
	mergeSort(a,0,n-1);
	printf("\nSorted array: ");
	print(a,n);
	return 0;
}