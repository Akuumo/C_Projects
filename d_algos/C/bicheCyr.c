#include<stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argv, char ** args)
{
	if(argv<2)
	{
		printf("---\nVeuillez entrer coordonnées à la suite de : \"%s\"\n---\n",args[0]);
	}
	else
	{
		char* ch_coords=args[1];			//On récupère la ligne de coords
    		char* ch_thisCoord = strtok(ch_coords,", ");	//On découpe et on récup la 1ere coord
		int i;						//Pointeur this coord
		int c;						//This coord int
		int xOld,yOld;					//Pour comparer avec la new coord
		int res;					//Resultat trajet parcouru en KM	
	
		i=c=xOld=yOld=res=0;
		
		printf("\n");
		while(ch_thisCoord!=NULL)			//Tant que la coord n'est pas null  
		{
			c = atoi(ch_thisCoord);			//Coord en int
			
			if(i<=1)				//Si ce sonts les 2 prem coords
			{
								
				if(i%2==0){xOld=c;}		//Si pair -> x 
				else{yOld=c;}			//Si imp  -> y
			}	
			else
			{
				if(i%2==0)			//Si pair -> x 
				{
					if(xOld!=c)		//Si old!= new
					{
						res+=abs(xOld-c); //On calcul la différence entre les 2
					}
					xOld=c;			//MaJ old
				}
				else				//Si imp  -> y
				{
					if(yOld!=c)
					{
						res+=abs(yOld-c);
					}
					yOld=c;
				}
			}	
			ch_thisCoord=strtok(NULL,", "); 		//Coord suivante
			i++;
		}
		printf("Hercule devra parcourir %d kilomètres\n",res);
		printf("\n");
	}
	return 0;
}
