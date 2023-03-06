#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct Student
{
    char name[13];
    char surname[13];
    int ID;
} Student;


typedef struct ListNode
{
    Student student;
    struct ListNode *next;
} ListNode;

typedef struct List
{
    ListNode *first;
} List;

Student *arr;

void insert(List *list, Student *newStudent);
Student *search(List *list, int ID);
void delete(List *list, int ID);

void insert(List *list, Student *newStudent)
{
    ListNode *newNode = (ListNode *)calloc(1, sizeof(ListNode));

    newNode->student = *newStudent;

    if (list->first == NULL)
    {
        list->first = newNode;
        return;
    }

    if (list->first->student.ID > newStudent->ID)
    {
        newNode->next = list->first;
        list->first = newNode;
        return;
    }
    

    ListNode *previous = list->first;

    while (previous->next != NULL && previous->next->student.ID < newStudent->ID) previous = previous->next;

    newNode->next = previous->next;
    previous->next = newNode;

    return;
}

Student *search(List *list, int ID)
{
    if(list->first == NULL)
    {
        return NULL;
    }

    ListNode *current = list->first;

    while(1)
    {
        if (current->student.ID == ID)
        {
            return &current->student;
        }

        if(current->next == NULL){
            break;
        }

        current = current->next;        
    }
       

    return NULL;
}

void delete(List *list, int ID)
{
    if (list->first == NULL)
    {
        return;
    }

    ListNode *current = list->first, *previous;

    if (current->student.ID == ID)
    {
        list->first = current->next;
        free(current);
        return;
    }
    
    while (current != NULL && current->student.ID != ID)
    {
        previous = current;
        current = current->next;
    }

    if (current == NULL) return;

    previous->next = current->next;

    free(current);

    return;
}



void create(List *list, int n)
{
    int i = 0;

    if (list->first != NULL)
    {
        ListNode *current = list->first;
        do
        {
            i++;
            current = current->next;
        } while (current != NULL);
    }

    for(; i < n; i++){
        insert(list, arr + i);
    }
}



int main()
{
    int i, itter = 15;


    arr = (Student *)malloc(sizeof(Student) * 1000000);
    for (int i =0; i<1000000; i++){
        int number = 1000000 + rand()%1000;
        arr[i].ID = number;
        //arr[i].name
        //arr[i].surname
        //printf("%d,  %d\n", i, number);
    }



    List *list = calloc(1, sizeof(List));

    ListNode *current, *next;
    
    int n = 1000;
    int noReturns = 10;

    for (int j = 0; j < itter; j++) {
        double time = 0, time2 = 0, time3 = 0;

        for (int z=0; z<noReturns; z++) {
            clock_t start = clock();

            create(list, n);

            clock_t end = clock();
            
            time += (end - start)*1000 / CLOCKS_PER_SEC;
            //printf("%d  %f ", n, time);


            clock_t start2 = clock();

            for (i = 0; i < n; i++)
            {
                search(list, arr[i].ID);
            }

            clock_t end2 = clock();
            
            time2 += (end2 - start2)*1000 / CLOCKS_PER_SEC;
            //printf("%f ", time2);


            int toDelete[n];
            int i;

            for (i = 0; i < n; i++) {
                toDelete[i] = i;
            }

            int temp, random;

            for (i = 0; i < n; i++) {
                random = rand() % (n);
                temp = toDelete[random];
                toDelete[random] = toDelete[i];
                toDelete[i] = temp;
            }

            clock_t start3 = clock();

            for (i = 0; i < n; i++) {
                delete(list, arr[toDelete[i]].ID);
            }

            clock_t end3 = clock();
            
            time3 += (end3 - start3)*1000 / CLOCKS_PER_SEC;
            //printf("%f\n", time3);


            current = list->first, *next;

            while (current != NULL)
            {
                next = current->next;
                free(current);
                current = next;
            }

        }
        printf("%d ", n);
        printf("%f ", time/noReturns);
        printf("%f ", time2/noReturns);
        printf("%f\n", time3/noReturns);


        n +=1000;

    }

    free(list);
    free(arr);

    return 0;
}