#include<stdio.h>
#include <stdlib.h>

int main(int argv, char ** args)
{
	if(argv<2)
	{
		printf("---\nVeuillez entrer le nombre de tête de l'Hydre à la suite de : \"%s\"\n---\n",args[0]);
	}
	else
	{	
		int nbHead=atoi(args[1]);
		int nbSwordHit=0;

		while(nbHead!=0)
		{
			nbSwordHit++;
			nbHead=nbHead/2;
			
			if(nbHead%2!=0)
			{
				if(nbHead==1)
				{
					printf("-> Au %d e coup d'épée, Hercule coupe une tête. Il n'en reste plus qu'une.\n",nbSwordHit);
					nbSwordHit++;
					nbHead=0;
				}else if(nbHead>1)
				{
					printf("-> Hercule en coupe la moitié au coup d'épée : %d. Il en reste %d.\n",nbSwordHit,nbHead);
					nbHead=(nbHead*3)+1;
					printf("Instantanément, le nombre de têtes triple et il en pousse une autre. Il y a maintenant %d têtes.\n",nbHead);
				}	
			}
			else
			{
				printf("-> Coup d'épée : %d, Hercule coupe %d tête(s). Il en reste %d. Rien ne repousse.\n",nbSwordHit,nbHead,nbHead);
			}
		}
		printf("-> Le %d e et dernier coup d'épée permet d'achever l'Hydre.\n",nbSwordHit);
	}	
	return 0;
}
