#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main()
{


    int socketdesc, clientsock;
    struct sockaddr_in serveraddr, clientaddr;
    socklen_t clientsize;
    char servermsg[2000], clientmsg[2000];

    int frame;
    int last_frame=-1;
    int ack=-1;

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

    bind(socketdesc,(struct sockaddr*)&serveraddr, sizeof(serveraddr));
    listen(socketdesc,1);

    clientsize=sizeof(clientaddr);
    clientsock=accept(socketdesc,(struct sockaddr*)&clientaddr,&clientsize);
    int x,y;
    while(1)
    {
        y=recv(clientsock,&frame,sizeof(frame),0);
        if (y<=0) break;
        x=recv(clientsock,clientmsg,sizeof(clientmsg),0);
        if (x<=0) break;
        clientmsg[x]='\0';
        printf("acknoledge (y) or (n) ? :  \n");
        fgets(servermsg,sizeof(servermsg), stdin);
        servermsg[strcspn(servermsg,"\n")]='\0';
        send(clientsock,servermsg,strlen(servermsg),0);

        if(strcmp(servermsg,"y")==0)
        {
            
                printf(" acceted frame %s \n",clientmsg);
                last_frame=frame;
            
        }
        else
        {
            printf("nack sent");
        }
           

    }
    close(socketdesc);
    close(clientsock);
    return 0;


}