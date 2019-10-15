#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

#define ALIVE 1
#define DEAD 0
#define WIDTH 720
#define HEIGHT 580

typedef struct
{
	SDL_Window* window;
	SDL_Renderer* renderer;
}t_sdl;

t_sdl * sdl_init(int w,int h)
{
    t_sdl * sdl=(t_sdl *)malloc(sizeof(t_sdl));
    
    if(SDL_VideoInit(NULL)<0)
    {
     	fprintf(stderr,"Erreur init SDL : %s",SDL_GetError());
	return NULL;
    }   
    
    // Création de la fenêtre
    sdl -> window = SDL_CreateWindow("Une fenetre SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, 0);
    
    if(sdl -> window == NULL)
    {
     	fprintf(stderr,"Erreur lors de la création d’une fenêtre : %s",SDL_GetError());
	return NULL;
    }   
    
    // Création du renderer
    sdl -> renderer = SDL_CreateRenderer(sdl -> window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(sdl -> renderer == NULL)
    {
     	fprintf(stderr,"Erreur lors de la création d’un renderer : %s",SDL_GetError());
	return NULL;
    }

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

void sdl_drawStar(t_sdl * sdl, int x_c, int y_c, int r)
{
	for(int i=0;i<360; i+=10)
	{
		int x= (int)(x_c+r*cos(i*(M_PI/180)));
		int y= (int)(y_c+r*sin(i*(M_PI/180)));
    		
		SDL_RenderDrawLine(sdl -> renderer, x_c, y_c, x, y);
	}
}

int ** createGame (int width, int height)
{
    int ** game;
    
    game = (int **) malloc (sizeof(int *) * height);
    for (int i=0; i < height; i++)
    {
        game[i] = (int *) malloc (sizeof(int) * width);
    }
    
    return game;
}

void freeGame (int ** game, int height)
{
    for (int i=0; i < height; i++)
    {
        free (game[i]);
    }
    free(game);
}

void initGame (int ** game, int width, int height)
{
    for (int i= 0; i < height; i++)
    {
        for (int j=0; j < width; j++)
        {
            game[i][j] =DEAD;
        }
    }
    game[height-3][1+8] = ALIVE; game[height-3][2+8] = ALIVE; game[height-3][3+8] = ALIVE;
    game[height-2][3+8] = ALIVE;
    game[height-1][2+8] = ALIVE;

    game[height-3][width-1-8] = ALIVE; game[height-3][width-2-8] = ALIVE; game[height-3][width-3-8] = ALIVE;
    game[height-2][width-3-8] = ALIVE;
    game[height-1][width-2-8] = ALIVE;

    game[50][(width/2)-1] = ALIVE; game[50][width/2] = ALIVE; game[50][(width/2)+1] = ALIVE;
}

void printGame (t_sdl * sdl,int ** game, int width, int height)
{
    SDL_RenderClear(sdl-> renderer);
    for (int i= 0; i < height; i++)
    {
        for (int j=0; j < width; j++)
        {
            if (game[i][j] == ALIVE) 
	    { 
    		//sdl_drawStar(sdl,i,j,1);
    		SDL_RenderDrawPoint(sdl->renderer,j,i);
		SDL_SetRenderDrawColor(sdl -> renderer, 255, 255, 255, 255);
            }
	    else
	    {
    		SDL_SetRenderDrawColor(sdl -> renderer, 0, 0, 0, 255);
	    }
        }
    }
    SDL_Delay(50); // Pause de 1 seconde
    SDL_RenderPresent(sdl -> renderer);
}

int countNeighbors(int ** game, int i, int j, int width, int height)
{
    int nb_neighbors = 0;
    
    if (i>0)
    {
        if ((j>0) && (game[i-1][j-1] == ALIVE)) { nb_neighbors++; }
        if (game[i-1][j] == ALIVE) { nb_neighbors++; }
        if ((j+1< width) && (game[i-1][j+1] == ALIVE)) { nb_neighbors++; }
    }
    if (i+1<height)
    {
        if ((j>0) && (game[i+1][j-1] == ALIVE)) { nb_neighbors++; }
        if (game[i+1][j] == ALIVE) { nb_neighbors++; }
        if ((j+1< width) && (game[i+1][j+1] == ALIVE)) { nb_neighbors++; }
    }
    if ((j>0) && (game[i][j-1] == ALIVE)){ nb_neighbors++; }
    if ((j+1<width) && (game[i][j+1] == ALIVE)){ nb_neighbors++; }
    
    return nb_neighbors;
}

void updateGame (int ** game, int ** past, int width, int height)
{
    for (int i= 0; i < height; i++)
    {
        for (int j=0; j < width; j++)
        {
            int nb_neighbors = countNeighbors (past, i,j, width, height);
            if ((past[i][j] == DEAD) && (nb_neighbors == 3))
            {
                game[i][j] = ALIVE;
            }
            else
            {
                if ((past[i][j] == ALIVE) &&
                    ((nb_neighbors == 2) || (nb_neighbors == 3)))
                {
                    game[i][j] = ALIVE;
                }
                else { game[i][j] = DEAD; }
            }
        }
    }
}

int main (int argc, char * argv[])
{
    t_sdl * sdl = sdl_init(WIDTH,HEIGHT);
    
    if(sdl != NULL)
    {
    	int ** game_1, ** game_2;
    
    	game_1 = createGame(WIDTH, HEIGHT);
    	game_2 = createGame(WIDTH, HEIGHT);
    
    	int ** current_game, ** future_game;
    	current_game = game_1; future_game = game_2;
    
    	int NB_RUNS=50;
    	int nb_runs=0;
    	
	initGame (current_game, WIDTH, HEIGHT);
    
        while (nb_runs < NB_RUNS)
    	{
        	printGame (sdl,current_game, WIDTH, HEIGHT);
        	updateGame (future_game, current_game, WIDTH, HEIGHT);
        
        	nb_runs++;
        
        	if (current_game == game_1)
        	{
            		current_game = game_2;
            		future_game = game_1;
       	 	}
        	else
        	{
            		current_game = game_1;
            		future_game = game_2;
        	}
    	}
    
    	freeGame(game_1, HEIGHT);
    	freeGame(game_2, HEIGHT);
    	sdl_free(sdl);
    }
    else
    {
	return EXIT_FAILURE;
    }   
    return 0;
}
