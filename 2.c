#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main()
{


    int socketdesc;   
    struct sockaddr_in serveraddr, clientaddr;
    char servermsg[2000], clientmsg[2000];


    int n, ack;
    memset(clientmsg,'\0',sizeof(clientmsg));
    memset(servermsg,'\0',sizeof(servermsg));

    socketdesc=socket(AF_INET,SOCK_STREAM,0);
    if(socketdesc<0)
    {
        printf("erro binding");
        return -1;
    }
    printf("socket created");
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(8080);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    connect(socketdesc,(struct sockaddr*)&serveraddr, sizeof(serveraddr));

    printf("enter no of frames \n");
    scanf("%d",&n);
    getchar();

    for(int i=0; i<n; i++)
    {
        printf("enter msg : \n");
        fgets(clientmsg,sizeof(clientmsg),stdin);
        clientmsg[strcspn(clientmsg,"\n")]='\0';

        ack=0;
        int x;
        while(ack==0)
        {
            send(socketdesc, &i, sizeof(i),0);
            send(socketdesc,clientmsg,strlen(clientmsg),0);

            int x=recv(socketdesc,servermsg,sizeof(servermsg),0);
            servermsg[x]='\0';
            if(strcmp(servermsg,"y")==0)
            {
                printf("acknlodgemnt recieved... \n");
                ack=1;
            }
            else
            {
                printf("nack recivere -> resending frame %d\n",i);
            }
        }
    }
    close(socketdesc);
    
    return 0;


}