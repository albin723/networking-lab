#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main()
{
    int socketdesc;
    struct sockaddr_in serveraddr;
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

    // Connect
    if (connect(socketdesc, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0)
    {
        printf("Error connecting\n");
        return -1;
    }
    printf("Connected to server\n");

    // Send message
    printf("Enter the message:\n");
    fgets(clientmsg, sizeof(clientmsg), stdin);
    clientmsg[strcspn(clientmsg, "\n")] = '\0';

    if (send(socketdesc, clientmsg, strlen(clientmsg), 0) < 0)
    {
        printf("Cannot send\n");
        return -1;
    }

    // Receive reply
    if (recv(socketdesc, servermsg, sizeof(servermsg), 0) < 0)
    {
        printf("Cannot receive message\n");
        return -1;
    }

    printf("Message from server: %s\n", servermsg);

    close(socketdesc);

    return 0;
}