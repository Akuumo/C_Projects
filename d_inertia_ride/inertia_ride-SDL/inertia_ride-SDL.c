#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

#define PNT '.'
#define HOR '_'
#define ASC '/'
#define DSC '\\'
#define RTN '\n'
#define SEG '?'

#define I_HOR 0
#define I_ASC 1
#define I_DSC 2
#define NBSEG 3

#define AV 0
#define AR 1

#define TRUE 1
#define FALSE 0

typedef struct
{
	SDL_Window* window;
	SDL_Renderer* renderer;
}t_sdl;

typedef struct t_seg
{
	int pos_seg;
	char seg;
	int inerAV;
	int inerAR;
	SDL_Point ball;	
	
	struct t_seg  * prev, * next;
}t_seg;

typedef struct t_ride
{
	t_seg  * first, * last;
}t_ride;

t_ride * new_ride()
{
    t_ride * new_r = (t_ride *)malloc(sizeof(t_ride));

    if (new_r != NULL)
    {
	new_r->first = NULL;
        new_r->last = NULL;
    }
    return new_r;
}

void printRide(t_ride * ride)
{
	t_seg * t_seg = ride -> first;
	while(t_seg!=NULL)
	{
		printf("%c",t_seg->seg);
		t_seg = t_seg->next;
	}
	printf("\n");
}

void printRideInv(t_ride * ride)
{
	t_seg * t_seg = ride -> last;
	while(t_seg!=NULL)
	{
		printf("%c",t_seg->seg);
		t_seg = t_seg->prev;
	}
	printf("\n");
}

void free_tRide(t_ride * tRide)
{
	t_seg * tSeg = tRide -> first;
	t_seg * tSegD = NULL;
	
	while(tSeg!=NULL)
	{
		tSegD = tSeg;
		tSeg = tSeg->next;
		free(tSegD);
	}
}

void free_ride(char ** ride,int H)
{
	for(int l=0;l<H;l++)
    	{    
        	free(ride[l]);
    	}
	free(ride); 
}

t_sdl * sdl_init(int w,int h)
{
	t_sdl * sdl=(t_sdl *)malloc(sizeof(t_sdl));
	
	if(SDL_VideoInit(NULL)<0)
    	{
     		fprintf(stderr,"Erreur init SDL : %s",SDL_GetError());
		return NULL;
    	}   
    
    	// Création de la fenêtre
    	sdl -> window = SDL_CreateWindow("Ride !", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, 0);
    
    	if(sdl -> window == NULL)
    	{
     		fprintf(stderr,"Erreur lors de la création d’une fenêtre : %s",SDL_GetError());
		return NULL;
    	}	   
    
    	// Création du renderer
    	sdl -> renderer = SDL_CreateRenderer(sdl -> window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  	//SDL_SetRenderDrawColor(sdl -> renderer, 0, 0, 0, 255);
    	
	return sdl;
}

void sdl_free(t_sdl * sdl)
{
    // Destruction du renderer et de la fenêtre :
    SDL_DestroyRenderer(sdl -> renderer);
    SDL_DestroyWindow(sdl -> window);
    
    // On quitte la SDL
    SDL_Quit();
}

t_ride * addSeg(t_ride * tRide, int pos_seg, char seg, int x, int y, int inerAV, int inerAR)
{
	t_seg * new = NULL;
	if( tRide != NULL )
	{
		new=(t_seg *)malloc(sizeof(t_seg));
		SDL_Point new_pts={x,y};	
	
		if( new != NULL )
		{
			new->pos_seg = pos_seg;
			new->seg = seg;
			new->next = NULL;
			new->inerAV = inerAV;
			new->inerAR = inerAR;
			new->ball = new_pts;
				
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

t_ride * getRide(t_ride * tRide, char ** ride, SDL_Point * pts_segs, int * nb_segs, int col, int W, int H, int * x, int * y)
{
	int caseW=(W*10)/W;
    	int caseH=(H*10)/H;
	int pX,pY;
	int inerAV = 0;
	int inerAR = 0;
	
	for(int lin=0;lin<H;lin++)
  	{
		if( ride[lin][col]!=PNT && ride[lin][col]!=RTN )
		{ 
			*x=*x+caseW;	
			switch(ride[lin][col])
			{	
				case HOR:
					nb_segs[I_HOR]++;
					inerAV=inerAR=-1;
					break;
				case ASC:
					nb_segs[I_ASC]++;
					*y = *y-caseH;
					inerAV=-10;
					inerAR=9;
					break;
				case DSC:
					nb_segs[I_DSC]++;
					*y = *y+caseH;
					inerAV=9;
					inerAR=-10;
					break;
			}
			pts_segs[col+1].x=*x;
			pts_segs[col+1].y=*y;
			pX=*x-(caseH/4); pY=*y-(caseH/2);
			return addSeg(tRide,col,ride[lin][col],pX,pY,inerAV,inerAR);
		}
	}
	return tRide;
}

t_ride * setRide(char ** ride, SDL_Point * pts_segs, int * nb_segs, int W, int H)
{
	t_ride * tRide = new_ride();
	
	int HEIGHT=H*40;
	int x=0; int y=HEIGHT/2;
	
	for(int col=0;col<W;col++){ tRide = getRide(tRide, ride, pts_segs, nb_segs, col, W, H, &x, &y); }
	return tRide;
}

void printRow(t_sdl * sdl,SDL_Point * pts_segs,SDL_Point pt_ball,int count, int iner)
{
	int x = pt_ball.x;
	int y = pt_ball.y;
	int d = 100/iner; 
	
	SDL_SetRenderDrawColor(sdl -> renderer, 0, 0, 0, 255);
    	SDL_RenderClear(sdl-> renderer);
    	SDL_SetRenderDrawColor(sdl -> renderer, 255, 255, 255, 255);

	SDL_RenderDrawLines(sdl -> renderer,pts_segs,count);	
	SDL_RenderDrawPoint(sdl -> renderer,x,y);	
    	SDL_RenderPresent(sdl -> renderer);
	SDL_Delay(50+d); // La vitesse de la balle dépend de son inertie
}

int getPosFin(t_ride * tRide, t_sdl * tSdl, SDL_Point * pts_segs, int inertia, int count)
{
	t_seg * tSeg = tRide -> first;
	int inerAV = 0; int inerAR = 0;	int inerTMP = 0;
	char seg=tSeg->seg;
	int pos=0;
	int dir = AV;
	SDL_Point ball={0,0};

	while(tSeg!=NULL)
	{
		inerAV=tSeg->inerAV;
		inerAR=tSeg->inerAR;
		seg=tSeg->seg;
		pos=tSeg->pos_seg;
		ball=tSeg->ball;
	
		if( dir == AV ) { inerTMP = inerAV; }
		else if( dir == AR ) { inerTMP = inerAR; }
		
		printRow(tSdl,pts_segs,ball,count,inertia+1);
		
		if(inertia==0&&seg==HOR)
		{
			printf("Plus d'inertie (%d) sur un segment horizontal (%c)\n",inertia,seg);	 
			return pos;
		}
		
 		inertia=inertia+inerTMP;

		if( inertia < 0 )
		{
			inertia = abs( inertia );
		
			if( dir == AV )	{ dir = AR; }
			else { dir = AV; }
		}
		
		if( inertia != 0 )
		{
			if( dir == AV ) { tSeg=tSeg->next; }	 
			else { tSeg=tSeg->prev; }	
		}	
	}

	if( dir == AV )	{ printf("Fin du Ride (Pos : %d)\n",pos); }
	else if( dir == AR ) { printf("Retour au départ du Ride (Pos : %d)\n",pos); }

	return pos;	
}

void inertiaRide()
{
}

int main(int argv,char ** args)
{
    	int inertia;
    	scanf("%d", &inertia);
    	int W;
    	int H;
    	scanf("%d%d", &W, &H); fgetc(stdin);
    	
	int HEIGHT=H*40;
	int WIDTH=W*10;

	char ** ride = (char**)malloc(sizeof(char*)*H);
	int * nb_segs = (int*)calloc(NBSEG,sizeof(int));
	SDL_Point * pts_segs = (SDL_Point*) malloc(sizeof(SDL_Point)*W+1);
	SDL_Point new_pts={0,(HEIGHT)/2};	
	t_sdl * tSdl = sdl_init(WIDTH,HEIGHT);
	
	if(tSdl == NULL) { return EXIT_FAILURE;	} 
	
	pts_segs[0]=new_pts;
	
	printf("Inertie : %d\n",inertia);	
	printf("W=%d-H=%d\n",W,H);
	
	for (int l = 0; l < H; l++)
    	{
        	char row[256];
        	fgets(row, 256, stdin);
		
		printf("%s",row); 	
		ride[l]=(char*)malloc(sizeof(char)*W);
        	strcpy(ride[l],row);
	}
       
	t_ride * tRide = setRide(ride, pts_segs, nb_segs, W, H);
	free_ride(ride,H);	
       	
    	printf("\nHOR	ASC	DES\n");
	for(int nb=0;nb<NBSEG;nb++){ printf("%d	",nb_segs[nb]); }
    	printf("\n\n");
	
	int posFin = getPosFin(tRide,tSdl,pts_segs,inertia,W+1);
	printf("Position Finale : %d\n",posFin);
		
	SDL_Delay(2000); // Pause de 2 secondes
	
	//Free
    	free_tRide(tRide); 
    	free(pts_segs);
    	sdl_free(tSdl);
    
  	return 0;
}
