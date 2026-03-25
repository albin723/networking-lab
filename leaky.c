#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define TOTAL_PACKETS 10


int get_random(int a)
{
    int r = rand() % a;
    if (r==0)
    {
        return 1;
    }
    return r;
}

int main()
{
    int packet_size[TOTAL_PACKETS];
    int i,t;

    int bucket_size;        
    int output_rate;        
    int bucket_content = 0; 

    int transmit_time;     
    int sent_data;          

    srand(time(NULL)); 

   
    for(i = 0; i < TOTAL_PACKETS; i++)
    {
        packet_size[i] = get_random(6) * 10;
    }

    
    printf("Generated packets:\n");
    for(i = 0; i < TOTAL_PACKETS; i++)
    {
        printf("Packet[%d] = %d bytes\n", i, packet_size[i]);
    }

    
    printf("\nEnter output rate: ");
    scanf("%d", &output_rate);

    printf("Enter bucket size: ");
    scanf("%d", &bucket_size);

    
    for(i = 0; i < TOTAL_PACKETS; i++)
    {
        printf("Packet %d arrives (%d bytes)\n", i, packet_size[i]);

       
        if(packet_size[i] + bucket_content > bucket_size)
        {
            if(packet_size[i] > bucket_size)
                printf("Packet too large → REJECTED\n");
            else
                printf("Bucket full → REJECTED\n");
        }
        else
        {
            
            bucket_content += packet_size[i];
            printf("Added to bucket. Current = %d\n", bucket_content);

            
            transmit_time = get_random(4) * 10;
            printf("Transmission time = %d\n", transmit_time);

            
            for(int t= 10; t <= transmit_time; t += 10)
            {
                sleep(1);

                if(bucket_content > 0)
                {
                    if(bucket_content <= output_rate)
                    {
                        sent_data = bucket_content;
                        bucket_content = 0;
                    }
                    else
                    {
                        sent_data = output_rate;
                        bucket_content -= output_rate;
                    }

                    printf("Sent = %d | Remaining = %d\n", sent_data, bucket_content);
                }
                else
                {
                    printf("No data to send\n");
                }
            }
        }
    }

    return 0;
}