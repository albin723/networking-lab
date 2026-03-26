#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdbool.h> //dont forget to include this for the frame ack checking array


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

    int nf;
    printf("Enter number of frames: ");
    scanf("%d", &nf);
    getchar();

    bool frameack[20];
    for(int i=0; i<nf; i++)
    {
        frameack[i]=false;
    }
    int ws, s ,e;
    printf("enter window size: \n");
    scanf("%d",&ws);
    getchar();
    s=0;
    e=ws-1;

    while(e!=nf)
    {   
        for(int i=s; i<=e; i++)
        {
            if(frameack[i]==true)
            {
                continue;
            }
            printf("Enter message for frame %d: ",i);
            fgets(clientmsg, sizeof(clientmsg), stdin);
            clientmsg[strcspn(clientmsg, "\n")] = '\0';
                
            send(socketdesc, clientmsg, strlen(clientmsg), 0);

            int n = recv(socketdesc, servermsg, sizeof(servermsg), 0);
            servermsg[n] = '\0';

            if(strcmp(servermsg, "y") == 0)
            {
            printf("ACK received\n");
            frameack[i]=true;
            }
            else
            {
            printf("NACK received ->sending next frame in window\n");
            }
            
        }
        //processed all frames currently in the window once.... now checking if any frames
        //in the window were left unacknowledged... if so.. restransimitting only those frames...
        int flag=0;
        for(int j=s; j<=e; j++)
        {
            if(frameack[j]==false)
            {
                flag=1;
                break;
            }
        }
        if (flag==0)
        {
            //all frames in the window are acknowlodged.. hence sliding the window..
            printf("all frames currently in the window were transmited \n");
            s+=1;
            e+=1;
        }
        else
        {
            printf("current window has unacknoledged frames.. sending them\n");
            continue;
            // wondow had unacknowledged frames... so processing from the window start again..
            //therefore do not update s and e variables
        }
    }

    close(socketdesc);
    return 0;
}