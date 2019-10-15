#include<stdio.h>
#include <stdlib.h>

int main(int argv, char ** args)
{
	if(argv<2)
	{
		printf("---\nVeuillez entrer le nombre gravé sur la bombe à la suite de : \"%s\"\n---\n",args[0]);
	}
	else
	{
		int codeBomb=atoi(args[1]);
		int result=0;	
		int k=0;
			
		while(k<codeBomb)				//Tous les nombres strictement inférieurs au nombre gravé sur la bombe.
		{
			if(k%3==0||k%5==0)			//Si le nombre est multiple de 3 ou de 5,
			{
				result+=k;			//on l'ajoute à la somme de tous les nombres.
				//printf("%d -> %d\n",k,result);
			}
			k++;					//On test le nombre suivant.
		}
		printf("Resultat : %d\n",result);
	}	
	return 0;
}
