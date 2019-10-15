#include<stdio.h>

int main(void)
{
	int a,b,c,k,n;
	a=1;b=2;c=5;k=1;n=0;
	
	while(k<(1000-n))
	{
		a=b;
		b=c+a;
		c=(3*c) + (4*a) - b;
		n=a+b;
		k++;
	}

	printf("%d,%d,%d\n",a,b,c);	
	return 0;
}
