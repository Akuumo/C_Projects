#include "inertia_ride.h"
int main()
{
    	int inertia;
    	scanf("%d", &inertia);
    	int W;
    	int H;
    	scanf("%d%d", &W, &H); fgetc(stdin);
    	
	char ** ride = (char**)malloc(sizeof(char*)*H);
	
	for (int l = 0; l < H; l++)			//Pour chacune des lignes du Ride. ( H lignes )
    	{
        	char row[256];				//On créé un tableau pour chaque caractère de la ligne.
        	fgets(row, 256, stdin);			/* On récupère le flux d'entrée de la ligne envoyé dans notre programme C.
							   (cat ride01.txt | ./codingame_Inertia-ride) et on l'insère dans ''row'' */
	
		ride[l] = (char*)malloc(sizeof(char)*W);//On alloue un espace mémoire de la largeur du ride.
        	strcpy(ride[l],row);			//On copie cette ligne dans un tableau.
	}
	
	t_ride * tRide = tab2list( ride, W, H );	//On convertie notre tableau contenant le Ride en chaîne doublement chainée.
	free_ride(ride,H);				//On peut maintenant libérer l'espace mémoire de notre tableau contenant le Ride.

	printf("%d\n",getPosFin( tRide, inertia ));	//On récupère la position du segment du circuit où le wagon terminera sa course.
    	free_tRide(tRide);				//On libère l'espace mémoire de notre chaîne doublement chainée. 
  	
	return 0;
}
