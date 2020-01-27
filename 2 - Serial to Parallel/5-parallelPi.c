#include<stdio.h>
#include<omp.h>
int main()
{
	static long num_steps = 10000000;
	double step;
	int i;
	double x,pi,sum=0.0;
	step = 1.0/(double) num_steps;
	#pragma omp parallel private(i,x)//Data that is declared private with the private directive is put on a separate stack per thread .
	{
		#pragma omp parallel for reduction(+:sum) schedule(static)//reduce function like a o b, operator o is + here, variable being reduced is sum
		for(i=0;i<num_steps;i++)
		{
			x = (i+0.5) * step;
			sum = sum + 4.0 /(1.0 + x*x);
		}
	}
	pi = step*sum;
	printf("\nPI = %f",pi);
	return 0;
}
// The second way to parallelize this code is by using the reduction clause. 
// This is a clause provided by the OpenMP standard which abstracts the problem of a reduction. 
// For this clause is only necessary to annotate the reduction variable and the type of reduction, in this case ‘reduction(+:sum)’.