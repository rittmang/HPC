#include<stdio.h>
#include<omp.h>
void main()
{
    int a,b,c,d,e,f;
    printf("Enter a,b");
    scanf("%d",&a);
    scanf("%d",&b);
    //omp_set_num_threads(10);
    #pragma omp parallel
    {
        int ID=omp_get_thread_num();
        printf("C block id is %d\n",ID);
        c=a+b;
        //int d=a-b;
        //int e=a*b;
        //int f=a/b;
        printf("c=%d\n",c);
    }
    #pragma omp parallel
    {
        int ID=omp_get_thread_num();
        printf("D block id is %d\n",ID);
        //int c=a+b;
        d=a-b;
        //int e=a*b;
        //int f=a/b;
        printf("d=%d\n",d);
    }
    #pragma omp parallel
    {
        int ID=omp_get_thread_num();
        printf("E block id is %d\n",ID);
        //int c=a+b;
        //int d=a-b;
        e=a*b;
        //int f=a/b;
        printf("e=%d\n",e);
    }
    #pragma omp parallel
    {
        int ID=omp_get_thread_num();
        printf("F block id is %d\n",ID);
        //int c=a+b;
        //int d=a-b;
        //int e=a*b;
        f=a/b;
        printf("f=%d\n",f);
    }
    printf("c=%d,d=%d,e=%d,f=%d\n",c,d,e,f);
}