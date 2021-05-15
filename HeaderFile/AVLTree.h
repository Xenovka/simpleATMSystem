#include <stdio.h>
#include <malloc.h>

int treeIndex = 0;

typedef struct Node {
  int key, height;
  struct Node *left, *right;
} Node;

// Pengimplementasian AVL Tree
int height(struct Node *N){
  if(N == NULL)
    return 0;
  return N->height;
}

int max(int a, int b){
  return (a > b) ? a : b;
}

Node *newNode(int item){
  Node *temp = (Node *)malloc(sizeof(Node));
  temp->key = item;
  temp->left = temp->right = NULL;
  temp->height = 1;
  return temp;
}

Node *leftRotate(Node *x){
  Node *y = x->right;
  Node *T2 = y->left;

  y->left = x;
  x->right = T2;

  x->height = max(height(x->left), height(x->right))+1;
  y->height = max(height(y->left), height(y->right))+1;

  return y;
}

Node *rightRotate(Node *y){
  Node *x = y->left;
  Node *T2 = x->right;

  x->right = y;
  y->left = T2;

  y->height = max(height(y->left), height(y->right))+1;
  x->height = max(height(x->left), height(x->right))+1;

  return x;
}

int getBalance(Node *N){
  if(N == NULL)
    return 0;
  return height(N->left) - height(N->right);
}

Node *insert(Node *node, int key){
  if(node == NULL) return(newNode(key));

  if(key < node->key)
    node->left = insert(node->left, key);
  else if(key > node->key)
    node->right = insert(node->right, key);
  else
    return node;

  node->height = 1 + max(height(node->left),
                         height(node->right));

  int balance = getBalance(node);

  if(balance > 1 && key < node->left->key)
    return rightRotate(node);

  if(balance < -1 && key > node->right->key)
    return leftRotate(node);

  if(balance > 1 && key > node->left->key){
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }

  if(balance < -1 && key < node->right->key){
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  return node;
}

void printInorder(Node *node){
  if(node == NULL) return;
  printInorder(node->left);
  treeIndex++;
  printf(">> %d) Rp. %d0.000,00 ", treeIndex, node->key);
  printf("\n");
  printInorder(node->right);
}
// Akhir dari pengimplementasian AVL Tree
