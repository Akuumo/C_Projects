#include<stdio.h>
#include <stdlib.h>

int getDigAtPos(int pos,int code)
{
	int getDig[4]={1000,100,10,1};
	int digCode=code;	
	
	digCode/=getDig[pos];
	digCode=digCode%10;
	return digCode;
}

int main(int argv, char ** args)
{
	if(argv<3)
	{
		printf("---\nVeuillez entrer la borne min et max à la suite de : \"%s\"\n---\n",args[0]);
	}
	else
	{	
		int min=atoi(args[1]);
		int max=atoi(args[2]);
		int digsOfCode[4];
		int somme=0;
			
		printf("Borne : [%d-%d]\n",min,max);
		printf("[");
				
		for(int i=min;i<=max;i++)
		{
			for(int k=0;k<4;k++)
			{	
				digsOfCode[k]=getDigAtPos(k,i);
			}
		
			for(int k=0;k<4;k++)
			{
				//printf("%d-",digsOfCode[k]);
				if(digsOfCode[k]==4||digsOfCode[k]==7)
				{
					if(i!=max)
					{
						printf("%d,",i);
					}else
					{
						printf("%d",i);
					}
					somme+=i;
					break;
				}	
			}
		}
		printf("]\nSomme : %d\n",somme);	
	}	
	return 0;
}
