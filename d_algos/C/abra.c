#include<stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argv, char ** args)
{
	if(argv<3)
	{
		printf("---\nVeuillez entrer la valeur initiale du générateur et le temps en minute de la position voulu à la suite de : \"%s\"\n---\n",args[0]);
	}
	else
	{
		int val_ini=atoi(args[1]);			//Valeur initiale du générateur
		int t_min_fin=atoi(args[2]);			//Temps en minute	
		int deplaN=0, deplaE=0, deplaP;			//Déplacement vers le nord, vers l'est et précédent en mètre
		int val=0;					//Nombre aléatoire
		int unit=0;					//Chiffre des unités		
		int t_sec_fin=t_min_fin*60;			//Temps en seconde de la position voulu
		
		printf("T	Dépl N.		Dépl E.		Aléa\n");
		 
		val=val_ini;
		for(int t=0;t<t_sec_fin;t+=3)
		{
			printf("%d	%d		%d		%d\n",t,deplaN,deplaE,val);
			
			unit=val;
			unit/=1;
			unit=unit%10;
			val=((137*val)+187)%256;
			
			if(unit==0){deplaN++;deplaP=0;}
			else if(unit==1){deplaE++;deplaP=1;}
			else
			{
				if(deplaP==0)
				{
					deplaN++;			
				}
				else
				{
					deplaE++;	
				}
			}
		}
		printf("\nSi la valeur initiale était %d, au bout de %d minutes, Abra se serait globalement déplacé de %d m vers le nord et %d m vers l'est.\n",val_ini,t_min_fin,deplaN,deplaE);
		printf("%d,%d\n",deplaN,deplaE);
	}
	return 0;
}
