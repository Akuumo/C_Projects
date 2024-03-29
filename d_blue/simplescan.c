#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

int main(void)
{
	inquiry_info *ii = NULL;
	int max_rsp, num_rsp;
	int dev_id, sock, len, flags;
	int i;
	char addr[19]={ 0 };
	char name[248]={ 0 };

	dev_id = hci_get_route(NULL);		printf("Id Device : %d\n",dev_id);
	sock = hci_open_dev( dev_id );		printf("Socket : %d\n",sock);	
	
	if( dev_id < 0 || sock < 0 )
	{
		perror("Opening Socket Error");
		exit(1);
	}

	len = 8;
	max_rsp = 255;
	flags = IREQ_CACHE_FLUSH;
	
	ii = (inquiry_info*) malloc(sizeof(inquiry_info) * max_rsp);
	
	num_rsp = hci_inquiry(dev_id, len, max_rsp, NULL, &ii, flags);	printf("Nomber Device detected : %d\n",num_rsp);	

	if( num_rsp < 0 ) perror("Requête HCI Fail");

	for( i=0;i<num_rsp;i++ )
	{
		ba2str(&(ii+i)->bdaddr,addr);
		memset(name,0,sizeof(name));
		if(hci_read_remote_name(sock,&(ii+i)->bdaddr,sizeof(name),name,0)<0){ strcpy(name,"[unknow]"); }
		printf("%d : %s %s\n",i,addr,name);
	}

	free( ii );
	close( sock );
	return 0;
}
