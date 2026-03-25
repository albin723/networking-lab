#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main()
{
	int socketdesc;
	struct sockaddr_in serveraddr;
	socklen_t serversize;
	char servermsg[2000],clientmsg[2000];
	
	memset(servermsg,'\0',sizeof(servermsg));
	memset(clientmsg,'\0',sizeof(clientmsg));
	
	socketdesc = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	if (socketdesc<0)
	{
		return -1;
		printf("Error creating socket");
		
	}
	printf("socet created\n");
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(2000);
	serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	
	printf("enter msg");
	fgets(clientmsg, sizeof(clientmsg), stdin);
	clientmsg[strcspn(clientmsg,"\n")]='\0';
	if(sendto(socketdesc,clientmsg,strlen(clientmsg),0,(struct sockaddr*)&serveraddr, sizeof(serveraddr)) <0)
	{
		printf("\nCant receive");
		return -1;
	}
	serversize=sizeof(serveraddr);
	if(recvfrom(socketdesc,servermsg,sizeof(servermsg),0,(struct sockaddr*)&serveraddr,&serversize)<0)
	{
		printf("\n");
	}
	printf("msg from server is %s \n",servermsg);
	
	close(socketdesc);
	
	return 0;
}