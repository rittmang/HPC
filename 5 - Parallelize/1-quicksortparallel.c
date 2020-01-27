#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

//partition function
long int partition(long int arr[],long int low,long int high)
{
    long int pivot=arr[high];
    long int i=low-1;
    long int temp;
    for(long int j=low;j<high;j++)
    {
        if(arr[j]<pivot)
        {
            i++;
            temp=arr[i];arr[j]=arr[i];arr[i]=temp;
        }
    }

    temp=arr[i+1];
    arr[i+1]=arr[high];
    arr[high]=temp;

    return i+1;
}

long int quicksort_parallel(long int arr[],long int low,long int high)
{
    if(low<high)
    {
        long int mid=partition(arr,low,high);
 
            #pragma omp task
                quicksort_parallel(arr,low,mid-1);
        
            #pragma omp task
                quicksort_parallel(arr,mid+1,high);
            
    }
}

long int quicksort_serial(long int arr[],long int low,long int high)
{
    if(low<high)
    {
        long int mid=partition(arr,low,high);
        quicksort_serial(arr,low,mid-1);
        quicksort_serial(arr,mid+1,high);
    }
}
int main()
{
    long int temp;
    long int n;
    

    printf("Enter number of elements:");
    scanf("%ld",&n);
    long int arr[n],arr1[n];
    printf("Filling array randomly");
    for(long int i=0;i<n;i++)
    {
        arr[i]=(rand()%100000);
        arr1[i]=arr[i];
    }
    double starttime1=omp_get_wtime();
    quicksort_serial(arr,0,n-1);
    double endtime1=omp_get_wtime();
    printf("\nSerial quicksort took:%lf time",(endtime1-starttime1));
    
    double starttime2=omp_get_wtime();
    #pragma omp parallel
    #pragma omp single
    quicksort_parallel(arr1,0,n-1);
    //#pragma ompt taskwait
    double endtime2=omp_get_wtime();
    printf("\nParallel quicksort took:%lf time",(endtime2-starttime2));
}
//faster parallel quicksort only 100000 ke baad