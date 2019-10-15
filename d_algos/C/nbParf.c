#include<stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argv, char ** args)
{
	if(argv<2)
	{
		printf("---\nVeuillez entrer le nombre max de votre liste des nombres parfaits à la suite de : \"%s\"\n---\n",args[0]);
	}
	else
	{
		int val_max=atoi(args[1]);			//Valeur max de la liste des nombres parfaits 
		int add=0;
		int j=1;

		for(int i=1;i<=val_max;i++)
		{
			while(j<i)	
			{
				if((i%j)==0)
				{
					add+=j;	
				}
				j++;
			}
			if(add==i)
			{
				printf("%d,",i);
			}
			j=1;
			add=0;
		}
		printf("\n");
	}
	return 0;
}
