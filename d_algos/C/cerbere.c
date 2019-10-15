#include<stdio.h>
#include <stdlib.h>
#include <math.h>

void getOAndN(int distance)
{
	int N=distance-1; int O=1;
	int Nc=pow(N,2);
	int Oc=pow(O,2);
	int distanceC=pow(distance,2);
		
	while((Oc+Nc)!=(distanceC))	//Tant que la dist. obt. n'est pas égale à la dist. search
	{
		while((Oc+Nc)<(distanceC)) //Tant que la dist. obt. est inférieur ou égale à la dist. search 
		{
			O++;
			Oc=pow(O,2);
			if((Oc+Nc)==distanceC){printf("%d, %d\n",O,N);}
		}
		N--;
		Nc=pow(N,2);
	}
}

int main(int argv, char ** args)
{
	if(argv<2)
	{
		printf("---\nVeuillez entrer la distance à la suite de : \"%s\"\n---\n",args[0]);
	}
	else
	{
		getOAndN(atoi(args[1]));
	}
	return 0;
}
