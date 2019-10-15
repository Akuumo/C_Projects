#include<stdio.h>
#include <stdlib.h>

int main(int argv, char ** args)
{
	if(argv<2)
	{
		printf("---\nVeuillez entrer le nombre d'étages à la suite de : \"%s\"\n---\n",args[0]);
	}
	else
	{
		int nbEtage=atoi(args[1]);
		int nbPomme=0; int nbPomTot=0;
		
		for(int k=1;k<=nbEtage;k++)
		{
			nbPomme = k*k;
			printf("Eta %d : %d pommes\n",k,nbPomme);
			
			if(nbPomme%3==0)
			{
				nbPomTot+=nbPomme;	
			}	
		}
		printf("Au total Hercule peut emporter %d pommes.\n",nbPomTot);
	}	
	return 0;
}
