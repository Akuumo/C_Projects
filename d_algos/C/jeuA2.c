#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define	MAX 10000
#define MIN 1000

int getRand()
{
	srand(time(NULL)); // initialisation de rand
  	return (rand()%(MAX - MIN + 1) + MIN);			
}

int getDigAtPos(int pos, int code)
{
	int tCode=log10(code);	
	
	if(pos<=tCode)
	{
		code/=pow(10,(tCode-pos));	
		return code=code%10;
	}
	return code;
}

int main(int argv, char ** args)
{
	if(argv<2)
	{
		printf("---\nVeuillez entrer le premier nombre à la suite de : \"%s\"\n---\n",args[0]);
	}
	else
	{
		int capitalJ1=100; int capitalJ2=100;
		int lenghNb=0; int Jn=0; int n=0; int tour=0;
		
		//int nbCour=getRand();			//un nombre est choisi aléatoirement entre 1000 et 10000 au début du jeu
		int nbCour=atoi(args[1]);	
		
		printf("NbCou : %d\n",nbCour);	

		while(capitalJ1>0&&capitalJ2>0)	//le jeu continue tant que les deux joueurs ont un capital positif
		{
			lenghNb=log10(nbCour)+1;
			for(int i=0;i<lenghNb;i++){ n+=getDigAtPos(i,nbCour); } // soit 'n' = la somme des chiffres du nombre courant
			
			if(Jn==0)	 		//le joueur1 débute le jeu et ensuite, les joueurs vont s'alterner	
			{
				capitalJ1-=n;		//le joueur courant retire 'n' de son capital
				Jn=1;
			}
			else
			{
				capitalJ2-=n;		//le joueur courant retire 'n' de son capital
				Jn=0;	
			}
			nbCour-=n;			//'n' est retiré du nombre courant				
			tour++;
				
			printf("Tour : %d - NbCou : %d (%d) (J1:%d|J2:%d)\n",tour,nbCour,n,capitalJ1,capitalJ2);	
			n=0;
		}
		if(capitalJ1<=0){printf("Le J2 gagne avec un capital de %d pts au tour n°%d\n",capitalJ2,tour);}
		else{printf("Le J1 gagne avec un capital de %d pts au tour n°%d\n",capitalJ1,tour);}
	}
	return 0;
}
