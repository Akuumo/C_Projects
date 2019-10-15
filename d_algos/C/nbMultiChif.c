#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define TRUE 1
#define FALSE 0

int getDigAtPos(int pos, int code)
{
	int tCode=log10(code);	
	
	if(pos<=tCode)
	{
		code/=pow(10,(tCode-pos));	
		return code=code%10;
	}
	return code;
}

int main(void)
{
	int nbMax=100000;

	int chif[10];
	int numNb;int sommeNb;int lenghNb;
	numNb=sommeNb=lenghNb=0;

	for(int nb=1;nb<=nbMax;nb++)
	{	
		for(int k=0;k<=9;k++){chif[k]=0;}
		
		lenghNb=log10(nb)+1;
		int nbValid=TRUE;

		for(int i=0;i<lenghNb;i++)
		{
			int thisChif=getDigAtPos(i,nb);
			if(chif[thisChif]==0)
			{
				chif[thisChif]=1;
			}
			else
			{
				nbValid=FALSE;
			}
		}
		
		if(nbValid==TRUE)
		{
			numNb++;
			sommeNb+=nb;
			printf("Nb n°%d - Nb : %d - Somme : %d\n",numNb,nb,sommeNb);
		}	
	}
	return 0;
}
