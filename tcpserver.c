#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main()
{
    int socketdesc, clientsock;
    socklen_t clientsize;
    struct sockaddr_in serveraddr, clientaddr;
    char servermsg[2000], clientmsg[2000];

    memset(servermsg, '\0', sizeof(servermsg));
    memset(clientmsg, '\0', sizeof(clientmsg));

    // Create socket
    socketdesc = socket(AF_INET, SOCK_STREAM, 0);
    if (socketdesc < 0)
    {
        printf("Error creating socket\n");
        return -1;
    }
    printf("Socket created\n");

    // Server details
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(8080);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Bind
    if (bind(socketdesc, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0)
    {
        printf("Error in binding\n");
        return -1;
    }
    printf("Binding done\n");

    // Listen
    if (listen(socketdesc, 1) < 0)
    {
        printf("Error listening\n");
        return -1;
    }
    printf("Listening for connections...\n");

    // Accept
    clientsize = sizeof(clientaddr);
    clientsock = accept(socketdesc, (struct sockaddr*)&clientaddr, &clientsize);

    if (clientsock < 0)
    {
        printf("Cannot connect\n");
        return -1;
    }
    printf("Client connected\n");

    // Receive
    if (recv(clientsock, clientmsg, sizeof(clientmsg), 0) < 0)
    {
        printf("Cannot receive message\n");
        return -1;
    }
    printf("Message from client: %s\n", clientmsg);

    // Send
    printf("Enter message: ");
    fgets(servermsg, sizeof(servermsg), stdin);
    servermsg[strcspn(servermsg, "\n")] = '\0';

    if (send(clientsock, servermsg, strlen(servermsg), 0) < 0)
    {
        printf("Cannot send\n");
        return -1;
    }

    // Close
    close(clientsock);
    close(socketdesc);

    return 0;
}