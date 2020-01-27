#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

void print_arr(int n, int arr[n]);
void serial(int n, int a[n], int b[n], int c[n]);
void parallel(int n, int a[n], int b[n], int c[n]);
int main(){
clock_t t;
double start;
double end;
int n,i;
printf("Enter array size : ");
scanf("%d" , &n);
int a[n],b[n],c1[n];
int c2[n];
for(i = 0; i < n; i++){
a[i] = rand() % n;
b[i] = rand() % n;
}
t = clock();
serial(n,a,b,c2);
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
printf("Serial execution time is : %f \n",time_taken);
printf("\n");
start = omp_get_wtime();
parallel(n,a,b,c1);
end = omp_get_wtime();
double p_ex = end - start;
printf("Parallel execution time is : %f\n",p_ex);

}



void serial(int n, int a[n], int b[n], int c[n]){
int i;
    for (i=1; i<n; i++){
        c[i] = a[i] + b[i];
    }
}


void parallel(int n, int a[n], int b[n], int c[n]){
int i, n_per_thread, tot_thread;
tot_thread = 9;
omp_set_num_threads(tot_thread);
n_per_thread = n / tot_thread;
#pragma omp parallel for shared(a,b,c) private(i) schedule (static, n_per_thread)
    for (i=1; i<n; i++){
        c[i] = a[i] + b[i];
    }
}

void print_arr(int n, int arr[n]){
int i;
for(i = 0; i < n; i++){
printf("%d \t", arr[i]);
}
}
/*guest-tbmHi0@c04l1011:~$ gcc -o vector1 -fopenmp vec.c 
guest-tbmHi0@c04l1011:~$ ./vector1
Enter array size : 100000
Serial execution time is : 0.000838 

Parallel execution time is : 0.001078
*/
