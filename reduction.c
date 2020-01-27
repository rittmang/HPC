#include <stdlib.h>
#include <stdio.h>
int main(int argc, char *argv[])
{
    long int i, count; // count points inside unit circle
    long int samples; // number of samples
    double pi;
    unsigned short xi[3] = {1, 5, 177}; // random number seed
    double x, y;
    samples = atoi(argv[1]);
    count = 0;
    for(i = 0; i < samples; i++)
    {
        x = erand48(xi);
        y = erand48(xi);
        if(x*x + y*y <= 1.0) count++;
    }
    pi = 4.0*count/samples;
    printf("Estimate of pi: %7.5f\n", pi);
}
/*

check 1 CPU output in system monitor on:
gcc reduction.c
./a.out 100000000000000000


*/