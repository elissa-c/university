#include <stdint.h>
#include <stdlib.h>

#define size 200
#define prob 0.95
int mat[size][size];


void create_undirected(int mat[size][size]){
    int i;
    for (i = 0; i < size; i++){
        time_t t;
        srand(time(0));
        int j;
        for (j = i+1; j < size; j++){

            float random = (float)rand()/RAND_MAX;
            //printf("%f\n", prob);
            if (random < prob) {
                mat[i][j] = 1;
                mat[j][i] = 1;
                //printf("%d\n", i);
            }
            else {
                mat[i][j] = 0;
                mat[j][i] = 0;
            }
        }
    }
}




typedef struct AdjacencyListItem
{
    int j;
    struct AdjacencyListItem *next;
} ALI;

ALI **AdjacencyList;
int AdjacencyListCount;

void addALEdge(int i, int j);

void initAList(int n)
{
    int i, j;

    AdjacencyList = (ALI **)calloc(n, sizeof(ALI *));
    AdjacencyListCount = n;
    //printf("initialized");
}

void addALEdge(int i, int j)
{
    if (AdjacencyList == NULL)
        return;

    ALI *newEdge = (ALI *)calloc(1, sizeof(ALI));

    newEdge->j = j;

    if (AdjacencyList[i] == NULL)
    {
        AdjacencyList[i] = newEdge;
        return;
    }

    ALI *current = AdjacencyList[i];

    while (current->next != NULL)
    {
        current = current->next;
    }

    current->next = newEdge;

    return;
}

void addUDEdge(int i, int j)
{
    addALEdge(i, j);
    addALEdge(j, i);
}

void freeAdjacencyList()
{
    if (AdjacencyList == NULL)
        return;

    int i;

    for (i = 0; i < AdjacencyListCount; i++)
    {
        ALI *current = AdjacencyList[i], *prev;

        while (current != NULL)
        {
            prev = current;
            current = prev->next;
            free(prev);
        }
    }

    free(AdjacencyList);
}

uint8_t checkALEdge(int i, int j)
{
    ALI *current;

    current = AdjacencyList[i];

    while (current != NULL)
    {
        if (current->j == j)
            return 1;

        current = current->next;
    }

    return 0;
}

void removeALEdge(int i, int j)
{
    if (AdjacencyList == NULL)
        return;

    if (AdjacencyList[i] == NULL)
        return;

    ALI *current = AdjacencyList[i], *prev;

    if (current->j == j)
    {
        current->j = -1;
        return;
    }

    while (current != NULL && current->j != j)
    {
        prev = current;
        current = current->next;
    }

    if (current == NULL)
        return;
    
    current->j = -1;
    
    return;
}

void removeUDEdge(int i, int j)
{
    removeALEdge(i, j);
    removeALEdge(j, i);
}

int countEdges(int i)
{
    int count = 0;

    ALI *current = AdjacencyList[i];

    if (current == NULL) return count;

    while (current != NULL)
    {
        if (current->j != -1)
        {
            count++;
        }
        current = current->next;
    }

    return count;
    
}