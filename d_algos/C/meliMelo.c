#include<stdio.h>
#include <stdlib.h>

int main(int argv, char ** args)
{
	if(argv<3)
	{
		printf("---\nVeuillez entrer le nombre à la suite de : \"%s\"\n---\n",args[0]);
	}
	else
	{	
		int u =atoi(args[1]);
		int n = atoi(args[2]);
		int first2=0; int last2=0; //2premiers chiffres; 2derniers chiffres;

		for(int k=0;k<n;k++)
		{
			//printf("%d\n",u);
			if(u<100)		//Si le nombre est <100
			{			//Ex: 89 
				first2=u/10;	//8
				last2=u%10;	//9
			}
			else			//Sinon
			{			//Ex: 142
				first2=u/100;	//1
				last2=u%100;	//42
			}
				
			int add=first2+last2;	
			int mul=(add*195)+117;
			int resul=mul%9973;
			u=resul;
			//printf("%d-%d\n",first2,last2);
		}
		printf("%d\n\nRésultat : %d\n",u,u);
	}	
	return 0;
}
