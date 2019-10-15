#include<stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argv, char ** args)
{
	if(argv<3)
	{
		printf("---\nVeuillez entrer les points d'énergie et les positions des objets à la suite de : \"%s\"\n---\n",args[0]);
	}
	else
	{
		int ptn=atoi(args[1]);				//On récupère l'énergie
		char* ch_pos=args[2];				//On récupère les pos des objets
    		char* ch_thisPos = strtok(ch_pos,", ");		//On découpe et on récup la 1ere pos
		int pos=0;					//This pos int
		int obj=0;					//Objet à l'arrivé	
	
		printf("\n");
		while(ch_thisPos!=NULL&&ptn!=0)			//Tant que la coord n'est pas null  
		{
			pos = abs(atoi(ch_thisPos));		//Pos Absolu en int
			obj++;

			printf("-> ");
				
			if(pos<=ptn)
			{
				ptn--;
				printf("Il fera valser l'objet %d situé en %s et il lui restera %d points d'énergie\n",obj,ch_thisPos,ptn);
			}
			else
			{
				printf("Il ne fera pas valser l'objet %d situé en %s (trop loin)\n",obj,ch_thisPos);
			}
	
			ch_thisPos=strtok(NULL,", "); 		//Pos obj suivante
		}
		printf("\nEn conséquence, arrivé à l'objet %d, il n'aura plus de pouvoirs psychiques.\n\n",obj);
	}
	return 0;
}
