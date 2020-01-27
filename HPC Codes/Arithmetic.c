#include<stdio.h>
#include<omp.h>

void add(int a,int b,int id)
{
	int c=a+b;
	printf("%d%5d\n",c,id);
}

void sub(int a,int b,int id)
{
	int c=a-b;
	printf("%d%5d\n",c,id);
}
void mul(int a,int b,int id)
{
	int c=a*b;
	printf("%d%5d\n",c,id);
}
void div(int a,int b,int id)
{
	float c=a/b;
	printf("%f%5d\n",c,id);
}
int main()
{
	int i,id,d,a,b;
		char ch;
		//float c;

	
		
		
			printf("input first number\n");
			scanf("%d",&a);
			printf("input second number\n");
			scanf("%d",&b);
			#pragma omp parallel num_threads(8)
			{
					id = omp_get_thread_num();
				#pragma omp sections nowait
				{
					#pragma omp section
					add(a,b,id);
					
					
				}
				#pragma omp sections nowait
				{
					#pragma omp section
					sub(a,b,id);
					
					
				}
				#pragma omp sections nowait
				{
					#pragma omp section
					mul(a,b,id);
					
					
				}
				#pragma omp sections nowait
				{
					#pragma omp section
					div(a,b,id);
					
					
				}
				
					
				
			}
}
