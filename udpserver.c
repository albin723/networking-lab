#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main()
{
	int socketdesc;
	struct sockaddr_in serveraddr,clientaddr;
	socklen_t clientsize;
	char servermsg[2000],clientmsg[2000];
	
	memset(servermsg,'\0',sizeof(servermsg));
	memset(clientmsg,'\0',sizeof(clientmsg));
	
	socketdesc = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	if (socketdesc<0)
	{
		return -1;
		printf("Error creating socket");
		
	}
	
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(2000);
	serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	if(bind(socketdesc,(struct sockaddr*)&serveraddr,sizeof(serveraddr)) < 0)
	{
		printf("Error in bingding process");
		return -1;
		
	}

	
	
	clientsize=sizeof(clientaddr);

	
	if(recvfrom(socketdesc,clientmsg, sizeof(clientmsg),0,(struct sockaddr*)&clientaddr, &clientsize) < 0)
	{
		printf("cant recive message\n");
		return -1;
	}
	printf("mesage from cliuent is %s ", clientmsg);
	
	printf("\nenter msg");
	fgets(servermsg, sizeof(servermsg), stdin);
	servermsg[strcspn(servermsg,"\n")]='\0';
	if(sendto(socketdesc,servermsg,strlen(servermsg),0,(struct sockaddr*)&clientaddr, clientsize) <0)
	{
		printf("Cant receive");
		return -1;
	}
	
	close(socketdesc);
	
	return 0;
}
	
	
	
