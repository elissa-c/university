#include <windows.h>
#include<stdio.h>
#include<stdlib.h>
#include <time.h>


#define MAX 16000
#define prob 0.3
#define size 15000
int mat[size][size];


int queue[MAX], front = -1,rear = -1, n;


void create_directed(int mat[size][size]){
    for (int i = 0; i < size; i++){
        srand(time(0));
        for (int j = 0; j < size; j++){          
            float random = (float)rand()/RAND_MAX;
            if (random < prob) {
                mat[i][j] = 1;
            }
            else {
                mat[i][j] = 0;
            }
        }
    }
}

void insert_queue(int vertex)
{
        if (rear == MAX-1)
                printf("Too much in a queue\n");
        else
        {
                if (front == -1)  // empty queue
                        front = 0;
                rear = rear+1;
                queue[rear] = vertex ;
        }
}

int isEmpty_queue()
{
        if(front == -1 || front > rear )
                return 1;
        else
                return 0;
}

int delete_queue()
{
        int del_item;
        if (front == -1 || front > rear)
        {
                exit(1);
        }
        else
        {
                del_item = queue[front];
                front = front+1;
                return del_item;
        }
}

int indegree(int v)
{
        int i,in_deg = 0;
        for(i=0; i<n; i++)
                if(mat[i][v] == 1)
                        in_deg++;
        return in_deg;
}


int main()
{
        int i,v,count,topo_order[MAX],indeg[MAX];
        n = size;

        create_directed(mat);
        
        clock_t start = clock();

        for(i=0;i<n;i++)
        {
                indeg[i] = indegree(i);
                if( indeg[i] == 0 )
                        insert_queue(i);
        }

        count = 0;

        while(  !isEmpty_queue( ) && count < n )
        {
                v = delete_queue();
                topo_order[count] = v;   //adding to order
                count++;
        
                for(i=0; i<n; i++)
                {
                        if(mat[v][i] == 1)
                        {
                                mat[v][i] = 0;
                                indeg[i] = indeg[i]-1;
                                if(indeg[i] == 0)
                                        insert_queue(i);
                        }
                }
        }

        clock_t end = clock();
        float t;
        t += (end-start)*1000/CLOCKS_PER_SEC;
        printf("%d %f", size, t);





        return 0;
}

