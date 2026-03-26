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

    char clientmsg[2000], servermsg[2000];
    

    socketdesc = socket(AF_INET, SOCK_STREAM, 0);
    if(socketdesc<0)
    {
        printf("couldnt create socket");
        return -1;
    }
    printf("socket created");
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(8080);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(bind(socketdesc, (struct sockaddr*)&serveraddr, sizeof(serveraddr))<0)
    {
        printf("coudlnt bind\n");
        return -1;
    }
    printf("binding done\n");

    listen(socketdesc, 1);
    printf("listening for incoming connections...\n");

    clientsize = sizeof(clientaddr);
    clientsock = accept(socketdesc, (struct sockaddr*)&clientaddr, &clientsize);

    printf("Client connected\n");

    while(1)
    {
        
        
        
        int n2 = recv(clientsock, clientmsg, sizeof(clientmsg), 0);
        if(n2 <= 0) break;

        printf("Send ack (y) or nack (n): ");
        fgets(servermsg, sizeof(servermsg), stdin);
        servermsg[strcspn(servermsg, "\n")] = '\0';

        send(clientsock, servermsg, strlen(servermsg), 0);

        if(strcmp(servermsg, "y") == 0)
        {
    
            printf("Accepted: %s\n", clientmsg);
            
            
        }
        else
        {
            printf("NACK sent...\n");
        }
    }

    close(clientsock);
    close(socketdesc);
    return 0;
}