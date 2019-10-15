#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifndef INERTIA_RIDE_H
#define INERTIA_RIDE_H

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

t_ride * new_ride();
t_ride * addSeg( t_ride * tRide, int pos_seg, char seg, int inerAV, int inerAR );
t_ride * getRide( t_ride * tRide, char ** ride, int col, int W, int H );
t_ride * tab2list( char ** circuit, int W, int H );

void free_tRide( t_ride * tRide );
void free_ride( char ** ride, int H );
void printRide(t_ride * ride);
void printRideInv(t_ride * ride);

int getPosFin( t_ride * tRide, int inertia );

#endif
