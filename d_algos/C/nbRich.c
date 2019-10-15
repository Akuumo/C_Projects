#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define TRUE 1
#define FALSE 0

int getDigAtPos(int pos, long int code)
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
		
		long int car,cub;
		int chif[10];
		int thisChif;int lenghNb;
		int nbValid=TRUE;

		thisChif=lenghNb=0;

		for(int i=val_min;i<=val_max;i++)
		{
			car=pow(i,2);
			cub=pow(i,3);
			nbValid=TRUE;
			
			for(int j=0;j<10;j++){chif[j]=0;}
			
			lenghNb=log10(car)+1;
			for(int k=0;k<lenghNb;k++)
			{
				thisChif=getDigAtPos(k,car);
				if(chif[thisChif]==0){chif[thisChif]=1;}
			}
			
			lenghNb=log10(cub)+1;
			for(int l=0;l<lenghNb;l++)
			{
				thisChif=getDigAtPos(l,cub);
				if(chif[thisChif]==0){chif[thisChif]=1;}
			}
			
			for(int m=0;m<10;m++){if(chif[m]==0){nbValid=FALSE;}}
			//printf("Nb : %d - Carré : %ld - Cube : %ld\n",i,car,cub);
		
			if(nbValid==TRUE)
			{
				//printf("Nb : %d - Carré : %d - Cube : %d\n",i,car,cub);
				printf("%d,",i);
			}	
		}
		printf("\n");
	}
	return 0;
}
