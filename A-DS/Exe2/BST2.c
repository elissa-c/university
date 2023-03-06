#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node
{
    int ID; 
    char firstName[13];
    char lastName[13];
    struct node *right_child;
    struct node *left_child; 
};

struct node* search(struct node *root, int x)
{
    if(root==NULL || root->ID==x) 
        return root;
    else if(x>root->ID) 
        return search(root->right_child, x);
    else 
        return search(root->left_child,x);
}

//minimum value in a tree
struct node* minimum(struct node *root)
{
    if(root == NULL)
        return NULL;
    else if(root->left_child != NULL)
        return minimum(root->left_child); 
    return root;
}


struct node* new_node(int x)
{
    struct node *p;
    p = malloc(sizeof(struct node));
    p->ID = x;
    p->left_child = NULL;
    p->right_child = NULL;

    return p;
}

struct node* insert(struct node *root, int x)
{
    //searching for the place to insert
    if(root==NULL)
        return new_node(x);
    else if(x>root->ID) 
        root->right_child = insert(root->right_child, x);
    else 
        root->left_child = insert(root->left_child,x);
    return root;
}


struct node* delete(struct node *root, int x)
{
    //searching for the item to be deleted
    if(root==NULL)
        return NULL;
    if (x>root->ID)
        root->right_child = delete(root->right_child, x);
    else if(x<root->ID)
        root->left_child = delete(root->left_child, x);
    else
    {
        //No Children
        if(root->left_child==NULL && root->right_child==NULL)
        {
            free(root);
            return NULL;
        }

        //One Child
        else if(root->left_child==NULL || root->right_child==NULL)
        {
            struct node *temp;
            if(root->left_child==NULL)
                temp = root->right_child;
            else
                temp = root->left_child;
            free(root);
            return temp;
        }

        //Two Children
        else
        {
            struct node *temp = minimum(root->right_child);
            root->ID = temp->ID;
            root->right_child = delete(root->right_child, temp->ID);
        }
    }
    return root;
}
//print
void inorder(struct node *root)
{
    if(root!=NULL) // checking if the root is not null
    {
        inorder(root->left_child); // visiting left child
        printf(" %d ", root->ID); // printing ID at root
        inorder(root->right_child);// visiting right child
    }
}

int listed[100000000];
int main()
{
    struct node *root = NULL;
    
    int n;
    n = 20000;
    int itter = 0;
    //ID(n);
    int i = 0;



    while(itter<15){
        
        i = 0;
        
        int z, noReturns = 10;
        float t = 0, t2 = 0, t3 = 0;

        for (z = 0; z<noReturns;z++) {
            srand(time(0));
           clock_t start = clock();
          for (i=0; i<n; i++) {
              //int id = 1000000 + i;
              int a;
              a = rand()%1000;
              int id = 1000000 +itter*5000 + a;
              root = insert(root, id);
              listed[i] = id;
          }

          clock_t end = clock();
          //float t;
          t += (end-start)*1000/CLOCKS_PER_SEC;
          //printf("\n\n%f %d   ", t, n)

          clock_t start2 = clock();
          for (i=0; i<n; i++) {
            root = delete(root, listed[i]);
          }

          clock_t end2 = clock();
          //float t2;
          t2 += (end2-start2)*1000/CLOCKS_PER_SEC;
          //printf("%f %d\n", t2, n);



        //   srand(time(0));
        //   clock_t start3 = clock();
        //   for (i=0; i<n*200; i++){
        //       int chosen = rand()%n+1;
        //       //root = deleteNode(root, listed[i]);
        //       //printf("%d  ", listed[chosen]);
        //       root = search(root, listed[chosen]);

        //   }

        //   clock_t end3 = clock();
        //   float t;
        //   t3 += (end3-start3)*1000/CLOCKS_PER_SEC;
        //   //printf("%f %d\n", t3, n);
        }
        printf("%d ", n);
        printf("%f ", t/noReturns);
        printf("%f ", t2/noReturns);
        //printf("%f ", t3/noReturns/200);
        printf("\n");
        n+=20000;
        itter++;
        //printf("%d  ", itter);

        }    
    }
