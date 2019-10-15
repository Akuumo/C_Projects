#include<stdio.h>
#include <stdlib.h>

int main(int argv, char ** args)
{
	if(argv<2)
	{
		printf("---\nVeuillez entrer la valeur de \"n\" pour \"f(n)\" à la suite de : \"%s\"\n---\n",args[0]);
	}
	else
	{
		long f[atoi(args[1])+1];
		
		f[0]=2;
		f[1]=3;
		
		printf("f(%d) = %ld\n",0,f[0]);
		printf("f(%d) = %ld\n",1,f[1]);
		
		for(int n=2;n<=atoi(args[1]);n++)			
		{
			if(n%2==0)
			{
				f[n]=2*f[n-1]+f[n-2];
				
			}
			else
			{
				f[n]=f[n-1]-f[n-2];
			}				
			//printf("f(%d) = %ld\n",n,f[n]);
		}
		printf("f(%d) = %ld\n",atoi(args[1]),f[atoi(args[1])]);
	}
	return 0;
}
