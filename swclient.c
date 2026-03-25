#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main()
{
    int socketdesc;
    struct sockaddr_in serveraddr;

    char clientmsg[2000], servermsg[2000];

    socketdesc = socket(AF_INET, SOCK_STREAM, 0);

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(8080);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(socketdesc, (struct sockaddr*)&serveraddr, sizeof(serveraddr));

    int frames;
    printf("Enter number of frames: ");
    scanf("%d", &frames);
    getchar();

    for(int i = 0; i < frames; i++)
    {
        printf("Enter message: ");
        fgets(clientmsg, sizeof(clientmsg), stdin);
        clientmsg[strcspn(clientmsg, "\n")] = '\0';

        int ack = 0;

        while(!ack)
        {
            
            send(socketdesc, &i, sizeof(i), 0);

             
            send(socketdesc, clientmsg, sizeof(clientmsg), 0);

            int n = recv(socketdesc, servermsg, sizeof(servermsg), 0);
            servermsg[n] = '\0';

            if(strcmp(servermsg, "y") == 0)
            {
                printf("ACK received\n");
                ack = 1;
            }
            else
            {
                printf("NACK received → resending...\n");
            }
        }
    }

    close(socketdesc);
    return 0;
}