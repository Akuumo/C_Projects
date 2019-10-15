#include<stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
	printf("Liste de tous les nombres entiers positifs inférieurs à 1000 qui plaisent à la fois à Ossatueur et Mewtwo :\n");

	int nbre=0;
	int unit=0;
	int tot=0;
	
	for(int i=0;i<1000;i++)	
	{
		nbre=i; 		//nbre=812
	
		while(nbre>0)
		{ 
			unit=nbre%10;	//-> 812%10 = 2	  |-> 81%10 = 1	 |-> 8%10 = 8	
			tot+=unit; 	//-> 0+2 = 2	  |-> 2+1   = 3  |-> 3+8  = 11
			nbre=nbre-unit;	//-> 812-2  = 810 |-> 81-1  = 80 |-> 8-8  = 0	
			nbre/=10;	//-> 810/10 = 81  |-> 80/10 = 8  |-> 0/10 = 0 <-Donc Fin While 
		}
					
		if(i%7==0&&tot==11){ printf("%d ",i); } //Si ce nombre div par 7 (Ossa) et si le total = 11 (MewTwo) -> print	
		tot=0;	
	}
	printf("\n");	
	return 0;
}
