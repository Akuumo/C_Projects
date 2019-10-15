#include<stdio.h>
#include <stdlib.h>

int getDigAtPos(int pos, int code)
{
	int getDig[4]={1000,100,10,1};
	int digCode=code;	
	
	digCode/=getDig[pos];
	digCode=digCode%10;
	return digCode;
}

int main(int argv, char ** args)
{
	if(argv<2)
	{
		printf("---\nVeuillez entrer le nombre gravé sur la bombe à la suite de : \"%s\"\n---\n",args[0]);
	}
	else
	{	
		int codeOnBomb=atoi(args[1]);
		int digsOfCode[4];
			
		printf("Code : %d\n",codeOnBomb);
		
		for(int k=0;k<4;k++)
		{
			digsOfCode[k]=getDigAtPos(k,codeOnBomb);
		}
		
		for(int k=0;k<4;k++)
		{
			printf("%d\n",digsOfCode[k]);	
		}
	}	
	return 0;
}
