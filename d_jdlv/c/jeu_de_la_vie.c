#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define ALIVE 1
#define DEAD 0

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

    game[37][(width/2)-1] = ALIVE; game[37][width/2] = ALIVE; game[37][(width/2)+1] = ALIVE;
}

void printGame (int ** game, int width, int height)
{
    system ("clear");
    for (int i= 0; i < height; i++)
    {
        for (int j=0; j < width; j++)
        {
            if (game[i][j] == ALIVE) { printf ("*"); }
            else { printf (" "); }
        }
        printf ("\n");
    }
    usleep (70000);
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
    int ** game_1, ** game_2;
    int WIDTH, HEIGHT;
    WIDTH=HEIGHT=50;
    
    game_1 = createGame(WIDTH, HEIGHT);
    game_2 = createGame(WIDTH, HEIGHT);
    
    int ** current_game, ** future_game;
    current_game = game_1; future_game = game_2;
    
    initGame (current_game, WIDTH, HEIGHT);
    
    int NB_RUNS=500;
    int nb_runs = 0;
    while (nb_runs < NB_RUNS)
    {
        printGame (current_game, WIDTH, HEIGHT);
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
    
    return 0;
}
