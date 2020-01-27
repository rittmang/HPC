#include<iostream>
using namespace std;
#include<omp.h>
void odd(int *a,int n)
{
	int e=1,s=0,i;
	int temp;
	while(e || s)
	{
		e=0;
		#pragma omp parallel for private(temp)
		for(i=s;i<n-1;i=i+2)
		{
			if(a[i]>a[i+1])
			{
				temp = a[i];
				a[i] = a[i+1];
				a[i+1] = temp;
				e=1;
			}
		}
			if(s==0)
			s=1;
			else
			s=0;		
	}
}
int main()
{
	int a[5];
	int i;
	for(i=0;i<5;i++)
	{
		cin>>a[i];
	}
	odd(a,5);
	cout<<endl;
	for(i=0;i<5;i++)
	{
		cout<<a[i]<<" ";
	}
	
}
