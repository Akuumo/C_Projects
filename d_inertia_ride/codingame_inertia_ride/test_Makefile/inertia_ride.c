#include "inertia_ride.h"

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


t_ride * addSeg(t_ride * tRide, int pos_seg, char seg, int inerAV, int inerAR)
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

t_ride * getRide(t_ride * tRide, char ** ride, int col, int W, int H)
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
			return addSeg(tRide, col, ride[lin][col], inerAV, inerAR);
		}
	}
	return tRide;
}

t_ride * tab2list(char ** circuit, int W, int H)
{
	t_ride * tRide = new_ride();
	for( int col=0; col<W; col++ ){ tRide = getRide(tRide, circuit, col, W, H); }
	
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

void free_ride(char ** ride, int H)
{
	for( int l=0; l<H; l++ )
    	{    
        	free(ride[l]);
    	}
	free(ride); 
}	

void printRide(t_ride * ride)
{
	t_seg * t_seg = ride -> first;
	while(t_seg!=NULL)
	{
		printf("%c",t_seg->seg);
		t_seg=t_seg->next;
	}
	printf("\n");
}

void printRideInv(t_ride * ride)
{
	t_seg * t_seg = ride -> last;
	while(t_seg!=NULL)
	{
		printf("%c",t_seg->seg);
		t_seg=t_seg->prev;
	}
	printf("\n");
}

int getPosFin(t_ride * tRide, int inertia)
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
