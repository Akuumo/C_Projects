#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/l2cap.h>

int main(int argv, char ** args)
{
	struct sockaddr_l2 addr = {0};
	int sock, status;
	char dest[18]={ 0 };

	strcpy(dest,args[1]);	
	
	sock = socket(AF_BLUETOOTH,SOCK_SEQPACKET,BTPROTO_L2CAP);
	
	addr.l2_family = AF_BLUETOOTH;
	addr.l2_psm = htobs(0x1001);	
	str2ba(dest, &addr.l2_bdaddr);

	status = connect(sock,(struct sockaddr*)&addr,sizeof(addr));	
	printf("%d\n",sock);
	if(status == 0){ status = write(sock,"SAHU!",5);}
	else{ perror("Error cause by :");}
	
	close(sock);
	return 0;
}
