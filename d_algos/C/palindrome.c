#include<stdio.h>
#include<string.h>

#define TRUE 1;
#define FALSE 0;

int isPalindrome(char * str)
{
	int i=0;
	int n=strlen(str);
	int rst=FALSE;

	if(n>0)
	{
		rst=TRUE;
		while((rst)&&i!=(n/2))
		{
			rst=(str[i]==str[(n-1)-i]);
			i++;
		}
	}
	return rst;
}

int main(int argv,char ** args)
{
	
	printf("%d\n",isPalindrome("SASSAS"));
	return 0;
}
