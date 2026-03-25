#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>


int main()
{
    int socketdesc;
    struct sockaddr_in serveraddr;
    char filename[100], filedata[300];
    int n, length;

    
    memset(filename, '\0', sizeof(filename));
    memset(filedata, '\0', sizeof(filedata));

    
    socketdesc = socket(AF_INET, SOCK_STREAM, 0);
    if(socketdesc < 0)
    {
        printf("Error creating socket\n");
        return -1;
    }
    printf("Socket created\n");

    
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(8080);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    
    if(connect(socketdesc, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0)
    {
        printf("Cannot connect to server\n");
        return -1;
    }
    printf("Connected to server\n");

    
    printf("Enter file name: ");
    scanf("%s", filename);
    getchar(); 

    length = strlen(filename);

    
    write(socketdesc, filename, length);

   
    n = read(socketdesc, filedata, sizeof(filedata));
    if(n < 0)
    {
        printf("Error reading file from server\n");
        return -1;
    }
    filedata[n] = '\0';

   
    printf("Contents of file:\n%s\n", filedata);

    
    close(socketdesc);
    return 0;
}