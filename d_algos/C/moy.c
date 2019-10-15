#include<stdio.h>
#include<stdlib.h>
#include<math.h>

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

int reverseNb(int nbre)
{
	int chiff=0; 
	int p=0;
	int nbreR=0;
	int lenNb=log10(nbre)+1;

	for(int i=0;i<lenNb;i++)
	{
		chiff = getDigAtPos(i,nbre);
		p = pow(10,i);
		nbreR+=p*chiff;
	}
	return nbreR;
}

int main(void)
{
	int add=0;
	int moyAri=0;
	int i_moyGeo=0; 
	float f_moyGeo=0.0;

	for(int i=1000;i<=9999;i++)
	{
		for(int j=1000;j<=9999;j++)
		{	
			add=i+j;
			moyAri=add/2.0;
			
			f_moyGeo=sqrt((double)(i*j));			
			i_moyGeo=f_moyGeo;
			
			if(moyAri!=i_moyGeo&&(f_moyGeo-i_moyGeo==0)&&(moyAri==reverseNb(i_moyGeo)))
			{
				printf("I=%d|J=%d|add=%d|moyAri=%d|moyGeo=%f|reverse=%d\n\n",i,j,add,moyAri,f_moyGeo,reverseNb(i_moyGeo));
			}	
		}
	}
	return 0;
}

