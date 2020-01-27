#include<stdio.h>
#include<omp.h>
#include<stdlib.h>

int main(){
	int n;
	printf("enter array size:- ");
	scanf("%d", &n);
	int arr[n];
	int i;
	int e=1;
//	double str = omp_get_wtime();
	for(int i=0; i<n; i++)
	{
		scanf("%d",&arr[i] );
	}

	/*for(i=0;i<((n+1)/2);i++)
	{
		int j;
		#pragma omp parallel for
		for(j=0;j<n;j+=2)
		{
			if(arr[j]>arr[j+1])
			{
				int temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}

		}

		#pragma omp parallel for
		for(j=1;j<n-1;j+=2)
		{
			int temp1;
			if(arr[j]>arr[j+1])
			{
				temp1 = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp1;
			}
		}
	}
*/

int s=0;
int temp;
while(e || s)
{
	e=0;
	#pragma omp parallel for private(temp)
	for(i=s;i<n-1;i=i+2)
	{
		if(arr[i]>arr[i+1])
		{
			temp = arr[i];
			arr[i] = arr[i+1];
			arr[i+1] = temp;
			e=1;
		}
	}
		if(s==0)
		s=1;
		else
		s=0;

}










	for(int i=0;i<n;i++)
	{
		printf("%d\t", arr[i]);
	}
	printf("\n");
	//printf("\nTime of Execution: %lf", omp_get_wtime()-str);
	return 0;
}
