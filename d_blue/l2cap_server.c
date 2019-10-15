#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/l2cap.h>

int main(void)
{
        struct sockaddr_l2 loc_addr = {0}, rem_addr = {0};
        char buf[1024]={0};
	int sock, client, bytes_read;
	socklen_t opt = sizeof(rem_addr);	

	int st_bind, st_listen;

        sock = socket(AF_BLUETOOTH,SOCK_SEQPACKET,BTPROTO_L2CAP);
	printf("Sock : %d\n",sock);

        loc_addr.l2_family = AF_BLUETOOTH;
	loc_addr.l2_bdaddr = *BDADDR_ANY;
	loc_addr.l2_psm = htobs(0x1001);

        st_bind = bind(sock,(struct sockaddr *)&loc_addr,sizeof(loc_addr));
	printf("Bind : %d\n",st_bind);
	
	st_listen = listen(sock,1);	
	printf("Listen : %d\n",st_listen);
	
	client = accept(sock,(struct sockaddr *)&rem_addr,&opt);
	printf("Client %d\n",client);
        
	ba2str(&rem_addr.l2_bdaddr,buf);
	fprintf(stderr,"Accepted Connection from %s\n",buf);

	memset(buf, 0, sizeof(buf));

	bytes_read = read(client, buf, sizeof(buf));
	if(bytes_read > 0 ){ printf("Received[%s]\n",buf);}

	close(client);
	close(sock);
        return 0;
}
