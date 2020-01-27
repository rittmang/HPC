#include<stdio.h>
#include<omp.h>
#include<time.h>
#define max 10000




void populate(int arr[])
{
    for(int i=0;i<max;i++)
    {
        arr[i] = max-i;
    }
}

void display(int arr[])
{
    for(int i=0;i<max;i++)
    {
        printf("%d\t",arr[i]);
    }
}

void bubblesort(int arr[])
{
    int i;
    for(i=0;i<(max+1)/2;i++)
    {
        int j;
        #pragma omp parallel for private(j)
        for(j=0;j<max-1;j = j+2)
        {
            int temp;
            if(arr[j]>arr[j+1])
            {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }

        int k;
        #pragma omp parallel for private(k)
        for(k=1;k<max-1;k = k+2)
        {
            int temp;
            if(arr[k]>arr[k+1])
            {
                temp = arr[k];
                arr[k] = arr[k+1];
                arr[k+1] = temp;
            }
        }
    }
}

int main()
{
    float ts=0,tp=0,start,end;
    int n=2;

    int a[max];

    populate(a);

    //display(a);
    start = omp_get_wtime();
    bubblesort(a);
    end = omp_get_wtime();
    tp = end-start;
    //printf("#################################################################################################################################################################################################################################");
    display(a);
    printf("Tp = %f",tp);
}
