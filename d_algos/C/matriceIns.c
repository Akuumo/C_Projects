#include<stdio.h>
#include <stdlib.h>

int main(void)
{
	int size=6;
	int m[size][size];
	int M[36]={36,19,27,36,7,10,2,18,3,33,2,21,26,27,4,22,30,31,29,36,7,20,6,30,30,6,14,23,15,13,22,10,10,35,15,22};
	int vMatrice=0;
	int somme=0;	

	printf("-------------------------------\n");
	for(int i=0;i<6;i++)
	{
		printf("|");
		for(int j=0;j<6;j++)
		{
			m[i][j]=M[vMatrice];
			printf("%d|",m[i][j]);
			vMatrice++;
		}
		printf("\n-------------------------------\n");
	}
	
	for(int input=0;input<23;input++)
	{
		printf("-------------------------------\n");
		for(int i=0;i<6;i++)
		{
			printf("|");
			for(int j=0;j<6;j++)
			{

				int k=m[i][j];
				m[i][j]=((11*k)+4)%37;
				printf("%d|",m[i][j]);
			}
			printf("\n-------------------------------\n");
		}
	}

	for(int i=0;i<6;i++)
        {
                for(int j=0;j<6;j++)
                {
                        somme+=m[i][j];
                }
        }
	printf("Somme : %d\n",somme);

	return 0;
}
