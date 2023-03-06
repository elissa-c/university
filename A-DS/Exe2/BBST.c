#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Create Node
struct Node {
  int key;
  char firstName[13];
  char lastName[13];
  struct Node *left;
  struct Node *right;
  int height;
};

int max(int a, int b);

int height(struct Node *N) {
  if (N == NULL)
    return 0;
  return N->height;
}

int max(int a, int b) {
  return (a > b) ? a : b;
}

struct Node *newNode(int key) {
  struct Node *node = (struct Node *)
    malloc(sizeof(struct Node));
  node->key = key;
  node->left = NULL;
  node->right = NULL;
  node->height = 1;
  return (node);
}

//Right rotate
struct Node *rightRotate(struct Node *y) {
  struct Node *x = y->left;
  struct Node *T2 = x->right;

  x->right = y;
  y->left = T2;

  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;

  return x;
}

//Left rotate
struct Node *leftRotate(struct Node *x) {
  struct Node *y = x->right;
  struct Node *T2 = y->left;

  y->left = x;
  x->right = T2;

  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;

  return y;
}

//Balancing
int getBalance(struct Node *N) {
  if (N == NULL)
    return 0;
  return height(N->left) - height(N->right);
}

struct Node *insertNode(struct Node *node, int key) {
  if (node == NULL)
    return (newNode(key));

  if (key < node->key)
    node->left = insertNode(node->left, key);
  else if (key > node->key)
    node->right = insertNode(node->right, key);
  else
    return node;

  //Balance
  node->height = 1 + max(height(node->left),
               height(node->right));

  int balance = getBalance(node);
  if (balance > 1 && key < node->left->key)
    return rightRotate(node);

  if (balance < -1 && key > node->right->key)
    return leftRotate(node);

  if (balance > 1 && key > node->left->key) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }

  if (balance < -1 && key < node->right->key) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  return node;
}

struct Node *minValueNode(struct Node *node) {
  struct Node *current = node;

  while (current->left != NULL)
    current = current->left;

  return current;
}


struct Node *deleteNode(struct Node *root, int key) {

  if (root == NULL)
    return root;

  if (key < root->key)
    root->left = deleteNode(root->left, key);

  else if (key > root->key)
    root->right = deleteNode(root->right, key);

  else {
    if ((root->left == NULL) || (root->right == NULL)) {
      struct Node *temp = root->left ? root->left : root->right;

      if (temp == NULL) {
        temp = root;
        root = NULL;
      } else
        *root = *temp;
      free(temp);
    } else {
      struct Node *temp = minValueNode(root->right);

      root->key = temp->key;

      root->right = deleteNode(root->right, temp->key);
    }
  }

  if (root == NULL)
    return root;

  //BAlance
  root->height = 1 + max(height(root->left),
               height(root->right));

  int balance = getBalance(root);
  if (balance > 1 && getBalance(root->left) >= 0)
    return rightRotate(root);

  if (balance > 1 && getBalance(root->left) < 0) {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }

  if (balance < -1 && getBalance(root->right) <= 0)
    return leftRotate(root);

  if (balance < -1 && getBalance(root->right) > 0) {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }

  return root;
}

//print the tree
void printPreOrder(struct Node *root) {
  if (root != NULL) {
    printf("%d ", root->key);
    printPreOrder(root->left);
    printPreOrder(root->right);
  }
}

//search

struct Node* search(struct Node *root, int x)
{
    if(root==NULL || root->key==x)
        return root;
    else if(x>root->key) 
        return search(root->right, x);
    else 
        return search(root->left,x);
}


int listed[100000000];

int main() {
    struct Node *root = NULL;
    int n, i;
    n = 20000;
    int itter = 0;

    while(itter<15){
        
        i = 0;
        int z, noReturns = 20;
        double t = 0, t2 = 0, t3 = 0;

        for (z = 0; z<noReturns;z++) {
          srand(time(0));
          clock_t start = clock();
          for (i=0; i<n; i++) {
              int a;
              a = rand()%1000;
              int id = 1000000 +itter*5000 + a;
              root = insertNode(root, id);
              listed[i] = id;
          }

          clock_t end = clock();
          t += (end-start)*1000/CLOCKS_PER_SEC;
          //printf("\n%f %d   ", t, n);

          clock_t start2 = clock();
          for (i=0; i<n; i++) {
            root = deleteNode(root, listed[i]);
          }

          clock_t end2 = clock();
          t2 += (end2-start2)*1000/CLOCKS_PER_SEC;
          //printf("%f %d\n", t2, n);



          // srand(time(0));
          // clock_t start3 = clock();
          // for (i=0; i<n*500; i++){
          //     root = search(root, listed[i%n]);

          // }

          // clock_t end3 = clock();
          // t3 += (end3-start3)*1000/CLOCKS_PER_SEC;
          // // printf("\n\n%f %d\n", t, n);
        }
        printf("%d ", n);
        printf("%f ", t/noReturns);
        printf("%f ", t2/noReturns);
        //printf("%f ", t3/noReturns/500);
        printf("\n");
        n+=20000;
        itter++;

    }    

}
