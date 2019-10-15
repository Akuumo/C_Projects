#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main(int argv, char ** args)
{
	if(argv<3)
	{
		printf("---\nVeuillez entrer x puis y à la suite de : \"%s\"\n---\n",args[0]);
	}
	else
	{
		int x=atoi(args[1]);	
		int y=atoi(args[2]);	
		int hTour=324*100; 		//Une tour de 324 mètres (1m=100cm)
		int j=0; int h=0; int i=0;
		int hNights[3]={0,0,0};		//Retiens 3 hauteurs : (-48h;-24h;now)
	
		while(h<hTour)
		{
			if(j==0){h+=x;}		//Le premier jour, il monte de x centimètres.
			else{x-=1;h+=x;}
			printf("Fin du jour %d : altitude=%d cm\n",j,h);
			if(h>hTour){break;}
			
			if((j+1)%8==0)		//Il pleut toutes les 8 nuits.(j+1 car il vient de pleuvoir la nuit dernière donc il y a 1 nuit)
			{
				h=hNights[abs(i-2)]; // Il se retrouve au même endroit que 48 heures auparavant (i-2)		
				hNights[i]=h;
			}
			else
			{
				h-=y;		//Il glisse toujours de y centimètres.	
				hNights[i]=h; 
			}
			i=(i+1)%2;
											
			printf("Fin de la nuit %d : altitude=%d cm\n",j,h);
			j++;
		}
		printf("L'escargot arrive en haut de la tour lors du jour %d\n",j); 
	}
	return 0;
}
