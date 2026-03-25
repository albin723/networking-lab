#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<fcntl.h>

int main()
{
    int socketdesc, clientsock;
    struct sockaddr_in serveraddr, clientaddr;
    socklen_t clientsize;
    char filename[100], filedata[300];
    int n, f;

    
    memset(filename, '\0', sizeof(filename));
    memset(filedata, '\0', sizeof(filedata));

    
    socketdesc = socket(AF_INET, SOCK_STREAM, 0);
    if (socketdesc < 0)
    {
        printf("Error creating socket\n");
        return -1;
    }
    printf("Socket created\n");

    
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(8080);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    
    if (bind(socketdesc, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0)
    {
        printf("Error in binding\n");
        return -1;
    }
    printf("Bind done\n");

    
    listen(socketdesc, 5);
    printf("Server listening...\n");

    while (1)
    {
        clientsize = sizeof(clientaddr);
        clientsock = accept(socketdesc, (struct sockaddr*)&clientaddr, &clientsize);
        if (clientsock < 0)
        {
            printf("Error accepting client\n");
            return -1;
        }
        printf("Client connected\n");

        
        n = read(clientsock, filename, sizeof(filename));
        if (n <= 0)
        {
            printf("Error reading filename\n");
            close(clientsock);
            return -1;
        }
        filename[n] = '\0';
        printf("Requested file: %s\n", filename);

        
        f = open(filename, O_RDWR);
        if (f < 0)
        {
            printf("File not found: %s\n", filename);
            close(f);
            close(clientsock);
            return -1;
        }

        
        n = read(f, filedata, sizeof(filedata));
        if (n < 0)
        {
            printf("Error reading file\n");
            close(f);
            close(clientsock);
            return -1;
        }
        filedata[n] = '\0';
        printf("File content:\n%s\n", filedata);

        
        write(clientsock, filedata, n);

        
        close(f);
        close(clientsock);
        printf("Client disconnected\n\n");
    }

    close(socketdesc);
    return 0;
}