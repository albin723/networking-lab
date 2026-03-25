#include<stdio.h>

struct node{
    int dist[20];
    int from[20];
}rt[10];
int main()
{
    int n, i, j, k;
    printf("enter no of nodes");
    scanf("%d",&n);
    int cost[n][n];

    printf("enter the cost matrix \n");

    for (int i =1; i<=n; i++)
    {
        for ( int j=1; j<=n; j++)
        {
            scanf("%d",&cost[i][j]);
            if(i==j)
            {
                cost[i][j]=0;
            }
            rt[i].dist[j]=cost[i][j];
            rt[i].from[j]=j;
        }
    }
    printf("the cost matrix is :\n");
    for (int i =1; i<=n; i++)
    {
        for ( int j =1; j<=n; j++)
        {
            printf("%d ",cost[i][j]);
        }
        printf("\n");
    }
    for(int i=1; i<=n; i++)
    {
        for (int j =1; j<=n; j++)
        {
            for(int k=1; k<=n; k++)
            {
                if (rt[i].dist[j] > rt[i].dist[k] + rt[k].dist[j])
                {
                    rt[i].dist[j]=rt[i].dist[k] + rt[k].dist[j];
                    rt[i].from[j]=k;
                }
            }
        }
    }
    for ( int i=1; i<=n  ; i++)
    {
        printf("for router %d \n",i);
        for(int j=1; j<=n; j++)
        {
            printf("distance from node %d is %d via %d \n", j, rt[i].dist[j], rt[i].from[j]);
        }
        printf("\n");
    }

    return 0;


}