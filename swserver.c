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
    int frame, last_frame = -1;

    socketdesc = socket(AF_INET, SOCK_STREAM, 0);

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(8080);
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(socketdesc, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    listen(socketdesc, 1);

    clientsize = sizeof(clientaddr);
    clientsock = accept(socketdesc, (struct sockaddr*)&clientaddr, &clientsize);

    printf("Client connected\n");

    while(1)
    {
        
        int n1 = recv(clientsock, &frame, sizeof(frame), 0);
        if(n1 <= 0) break;

        
        int n2 = recv(clientsock, clientmsg, sizeof(clientmsg), 0);
        if(n2 <= 0) break;

        printf("Send ack (y) or nack (n): ");
        fgets(servermsg, sizeof(servermsg), stdin);
        servermsg[strcspn(servermsg, "\n")] = '\0';

        send(clientsock, servermsg, strlen(servermsg), 0);

        if(strcmp(servermsg, "y") == 0)
        {
    
            printf("Accepted: %s\n", clientmsg);
            last_frame = frame;
            
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