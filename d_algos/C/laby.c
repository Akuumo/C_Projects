#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>

#define GROUND 0
#define TOP 1
#define RIGHT 2
#define PLAYER 3
#define TRACE 4

int ** createMap (int width, int height)
{
    int ** map;
    
    map = (int **) malloc (sizeof(int *) * height);
    for (int i=0; i < height; i++)
    {
        map[i] = (int *) malloc (sizeof(int) * width);
    }
    
    return map;
}

void freeMap (int ** map, int height)
{
    for (int i=0; i < height; i++)
    {
        free (map[i]);
    }
    free(map);
}

void initMap (int ** map, int width, int height)
{
    for (int i= 0; i < height; i++)
    {
        for (int j=0; j < width; j++)
        {
	    	if(i==(height-1)||i==0)
		{
			map[i][j]=TOP;
		}
		else if(j==(width-1))
		{
			map[i][j]=RIGHT;
		}
		else
		{
			map[i][j]=GROUND;
		}	
        }
    }
    int * posBase=&map[height-1][0];
    *posBase=PLAYER;
}
void updatePos(char dir,int * x, int * y,int * xLast, int * yLast,int ** map,int h,int w)
{
	switch(dir)
        {
        	case 'N' :
                	*y+=1;
                        break;
                case 'E' :
                        *x+=1;
                        break;
                case 'S' :
	              	*y-=1;
                       	break;
                case 'O' :
                      	*x-=1;
		        break;
               	default :
                	*x=-1;*y=-1;
                        printf("Erreur : Direction différente de N, S, E ou O\n");
                        printf("Position case d'arrivée : (%d,%d)\n",*x,*y);
                       	exit(0);
	}
	if(*x<0||*y<0)
	{
        	*x=-1;*y=-1;
        	printf("Erreur : Coordonnées négatives !\n");
       		printf("Position case d'arrivée : (%d,%d)\n",*x,*y);
        	exit(0);
	}

	int *pos=&map[(h-1)-(*y)][*x];
	*pos=PLAYER;

	int *posLast=&map[(h-1)-(*yLast)][*xLast];
	*posLast=TRACE;
	
	*xLast=*x;
	*yLast=*y;
}

void printMap (int ** map, int width, int height)
{
    system ("clear");
    for (int i= 0; i < height; i++)
    {
        for (int j=0; j < width; j++)
        {
            	if (map[i][j] == PLAYER) { printf("A"); }
           	else if(map[i][j] == TOP){ printf("_"); }
           	else if(map[i][j] == RIGHT){ printf("|"); }
           	else if(map[i][j] == TRACE){ printf("-"); }
		else{printf(" ");}
        }
        printf ("\n");
    }
    //usleep(70000);
}


int main(int argv,char ** args)
{
	char * dir = args[1];
	int x,y,xLast,yLast;
	x=y=xLast=yLast=0;
	
	int ** map; 
    	int WIDTH, HEIGHT;
    	WIDTH=HEIGHT=100;
    	
	map = createMap(WIDTH, HEIGHT);
   	
    	initMap(map,WIDTH, HEIGHT);
	
	for(int i=0;i<strlen(dir);i++)
    	{
		updatePos(dir[i],&x,&y,&xLast,&yLast,map,WIDTH,HEIGHT);
        	printMap (map, WIDTH, HEIGHT);
		printf("(%d,%d)\n",x,y);
	}	
	
   	freeMap(map, HEIGHT);
	
	return 0;
}
