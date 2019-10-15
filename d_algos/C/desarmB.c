#include<stdio.h>
#include <stdlib.h>

int main(int argv, char ** args)
{
	if(argv<2)
	{
		printf("---\nVeuillez entrer le numéros de série de la bombe à la suite de : \"%s\"\n---\n",args[0]);
	}
	else
	{	
		int nSerie=atoi(args[1]);
		int U,U13,U3last,N;
		U=N=U13=U3last=0;

		int cut3Dig=1000;

		U3last=nSerie/cut3Dig;
		N=nSerie%cut3Dig;
	
		for(int k=0;k<N;k++)
		{
			U=U3last;
			U13=U*13;
			U3last=U13%cut3Dig;
			//printf("%d -> %d -> %d\n",U,U13,U3last);
		}
		printf("---\nNuméro de série : %d, il faut couper le fil %d\n---\n",nSerie,U3last);
		
	}
	return 0;
}
