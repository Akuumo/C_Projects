#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define NB 10 

int getDigAtPos(int pos,int code)
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
	if(argv<3)
	{
		printf("---\nVeuillez entrer le nombre min et le nombre max de la plage de votre liste des nombres riches à la suite de : \"%s\"\n---\n",args[0]);
	}
	else
	{
		int val_min=atoi(args[1]);			//Valeur min de la liste des nombres parfaits	
		int val_max=atoi(args[2]);			//Valeur max de la liste des nombres parfaits 
		int lenNb=0;
		int nbre=0;
		int chif=0;
		int result=1;
		int * nb_pers = (int *) calloc(NB,sizeof(int));		

		for(int i=val_min;i<=val_max;i++)
		{
			nbre=i;
			lenNb=log10(nbre)+1;
			printf("%d ->",nbre);
					
			while(lenNb>1)
			{
				for(int j=0;j<lenNb;j++)
				{
					chif=getDigAtPos(j,nbre);
					result*=chif;
				}
				nbre=result;
				lenNb=log10(nbre)+1;

				if(lenNb>1){ printf(" %d ->",nbre); }
				else{ printf(" %d\n",nbre); }
				
				result=1;
			}
			if(lenNb<=1)
			{
				nb_pers[nbre]++;
			}
		}
		
		printf("\n");

		for(int j=1;j<NB-1;j++)
		{
			printf("%d,",nb_pers[j]);
		}
		printf("%d\n",nb_pers[NB-1]);
	
		free(nb_pers);
		printf("\n");
	}
	return 0;
}
