#include<stdio.h>
#include<stdlib.h>

int suite_zeros(int * tab, int n)
{
	int i,j,t,jn,tn;
	j=jn=-1; t=tn=i=0;

	while(i<n)
	{
		if(tab[i]==0)
		{
			if(j==-1){j=i;t=1;}
			else{t++;}
		}
		else
		{
			if(t>tn){jn=j;tn=t;}
			j=-1;t=0;
		}
		i++;
	}
	if(t>tn){jn=j;}
	if(n>0&&jn==-1)
	{
		jn=n;
	}
	return jn;
}

int main(int argv,char ** args)
{
	int T[14]={0,0,1,1,0,0,0,1,0,0,0,0,0,1};
	
	printf("%d\n",suite_zeros(T,14));
	return 0;
}
