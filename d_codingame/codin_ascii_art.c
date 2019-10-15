#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *** init_ascii_art(char * T,int L,int H)
{            
    char *** ascii_art;
 
    //Alloc matrices
    ascii_art = (char ***) malloc(sizeof(char **) * 27);
    for(int k=0;k<27;k++)
    {
        ascii_art [k] = (char **) malloc(sizeof(char *) * H);    
        for(int i=0;i<H;i++)
        {
            ascii_art [k][i] = (char *) malloc(sizeof(char ) * L);
        }
    } 
    return ascii_art;
}

void free_ascii_art(char *** ascii_art,int H)
{    
    //Free matrices
    for(int k=0;k<27;k++)
    {    
        for(int i=0;i<H;i++)
        {
            free(ascii_art[k][i]);
        }
        free(ascii_art[k]);
    }
    free(ascii_art);
}

int main()
{
    int L;
    scanf("%d", &L);
    int H;
    scanf("%d", &H); fgetc(stdin);
    char T[257];
    fgets(T, 257, stdin);
    
    char *** ascii_art=init_ascii_art(T,L,H);
    //   kij 
    //  27HL   
    
    for (int i = 0; i < H; i++) 
    {
        char ROW[1025];
        fgets(ROW, 1025, stdin);
        
        for(int k=0;k<27;k++)
        {
            for(int j=0;j<L;j++)
            {
                ascii_art[k][i][j] = ROW[k*L +j];
            }
        }
    }
    
    
    for(int i=0;i<H;i++)
    {
        for (int n=0; n<strlen(T)-1; n++)
        {
            char c = T[n]; int k;
            if(c >= 'A' && c <= 'Z'){ k = (int) c - (int) 'A';}
            else if(c >= 'a' && c <= 'z'){ k = (int) c - (int) 'a';}
            else{ k=26;}
            
	    for(int j=0;j<L;j++)
            {
            	printf("%c",ascii_art[k][i][j]);
            }
        }
        printf("\n");
    }
    
    //Free matrices
    free_ascii_art(ascii_art,H);

    return 0;
}
