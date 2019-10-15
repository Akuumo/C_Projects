#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 800

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

int main(void)
{
    t_sdl * sdl = sdl_init(WIDTH,HEIGHT);

    if(sdl != NULL)
    {
    	// Mise au noir du fond (R, G, B, ALPHA)
    	SDL_SetRenderDrawColor(sdl -> renderer, 0, 0, 0, 255);
    	SDL_RenderClear(sdl-> renderer);
    
    	// Changement de la couleur de tracé : Couleur blanche
    	SDL_SetRenderDrawColor(sdl -> renderer, 255, 255, 255, 255);
    
    	sdl_drawStar(sdl, WIDTH/2, HEIGHT/2, 100);
    
    	// Toujours penser au rendu, sinon on n'obtient rien du tout
    	SDL_RenderPresent(sdl -> renderer);
    
    	SDL_Delay(10000); // Pause de 1 seconde
    }
    else
    {
	return EXIT_FAILURE;
    }   

    sdl_free(sdl);

    return 0;
}

