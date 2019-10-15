#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PNT '.'
#define HOR '_'
#define ASC '/'
#define DSC '\\'
#define RTN '\n'

#define AV 0
#define AR 1

typedef struct t_seg
{
	int pos_seg;
	char seg;
	int inerAV;
	int inerAR;
	
	struct t_seg  * prev, * next;
}t_seg;

typedef struct t_ride
{
	t_seg  * first, * last;
}t_ride;

t_ride * new_ride()
{
    t_ride * new_r = (t_ride *)malloc(sizeof(t_ride));

    if ( new_r != NULL )
    {
	new_r->first = NULL;
        new_r->last = NULL;
    }
    return new_r;
}


t_ride * addSeg( t_ride * tRide, int pos_seg, char seg, int inerAV, int inerAR )
{
	t_seg * new = NULL;
	if( tRide != NULL )
	{
		new=(t_seg *)malloc(sizeof(t_seg));
	
		if( new != NULL )
		{
			new->pos_seg = pos_seg;
			new->seg = seg;
			new->next = NULL;
			new->inerAV = inerAV;
			new->inerAR = inerAR;
				
			if ( tRide -> first == NULL )
            		{
				new->prev = NULL;
				tRide->first = new;
               	 		tRide->last = new;
            		}
           		else
            		{
               			tRide->last->next = new;
				new->prev = tRide -> last;
               		 	tRide->last = new;
            		}
		}
	}
	return tRide;
}

t_ride * getRide( t_ride * tRide, char ** ride, int col, int W, int H )
{
	int inerAV = 0;
	int inerAR = 0;
	
	for( int lin=0; lin<H; lin++ )
  	{
		if( ride[lin][col] != PNT && ride[lin][col] != RTN )
		{ 
			switch( ride[lin][col] )
			{	
				case HOR:
					inerAV = inerAR = -1;
					break;
				case ASC:
					inerAV = -10;
					inerAR = 9;
					break;
				case DSC:
					inerAV = 9;
					inerAR = -10;
					break;
			}
			return addSeg( tRide, col, ride[lin][col], inerAV, inerAR );
		}
	}
	return tRide;
}

t_ride * tab2list( char ** circuit, int W, int H )
{
	t_ride * tRide = new_ride();
	for( int col=0; col<W; col++ ){ tRide = getRide( tRide, circuit, col, W, H ); }
	
	return tRide;
}

void free_tRide( t_ride * tRide )
{
	t_seg * tSeg = tRide -> first;
	t_seg * tSegD = NULL;
	
	while( tSeg != NULL )
	{
		tSegD = tSeg;
		tSeg = tSeg->next;
		free(tSegD);
	}
}


int getPosFin( t_ride * tRide, int inertia )
{
	t_seg * tSeg = tRide->first;
	int inerAV = 0; int inerAR = 0;	int inerTMP = 0;
	char seg = tSeg->seg;
	int pos = 0;
	int dir = AV;

	while(tSeg!=NULL)
	{
		inerAV = tSeg->inerAV;
		inerAR = tSeg->inerAR;
		seg = tSeg->seg;
		pos = tSeg->pos_seg;
	
		if( dir == AV ) { inerTMP = inerAV; }
		else if( dir == AR ) { inerTMP = inerAR; }
		
		if( inertia == 0 && seg == HOR )
		{
			return pos;
		}
		
 		inertia = inertia + inerTMP;

		if( inertia < 0 )
		{
			inertia = abs( inertia );
		
			if( dir == AV )	{ dir = AR; }
			else { dir = AV; }
		}
		
		if( inertia > 0 )
		{
			if( dir == AV ) { tSeg = tSeg->next; }	 
			else { tSeg = tSeg->prev; }	
		}	
	}

	return pos;	
}

void free_ride( char ** ride, int H )
{
	for( int l=0; l<H; l++ )
    	{    
        	free(ride[l]);
    	}
	free(ride); 
}

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
