#include <stdio.h>
#include <stdlib.h>

typedef struct t_node
{
	int n;
	struct t_node * next;
}t_node;

t_node * addNode(t_node * list, int n)
{
	t_node * new;
	new=(t_node *)malloc(sizeof(t_node));
	new->n=n;
	new->next=list;
	return new;
}

t_node * F(int n, t_node * w)
{
	t_node * word;
	
	if(n==1){word=addNode(w,'1');}
	else if(n==2){word=addNode(w,'0');}
	else
	{
		t_node * word_n_2=F(n-2,w);
		word = F(n-1,word_n_2);	
	}
	return word;
}
void printlist(t_node *list)
{
	while(list!=NULL)
	{
		printf("%c",list->n);
		list=list->next;
	}
	printf("\n");
}

void freelist(t_node *list)
{
	t_node * tmp;
	while(list!=NULL)
	{
		tmp=list,
		list=list->next;
		free(tmp);
	}
}

int main(void)
{
	t_node * list=NULL;
	list=F(10,list);	
	printlist(list);	
	freelist(list);
	
	return 0;
}
