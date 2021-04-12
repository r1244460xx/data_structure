#include<stdio.h>
#include<stdlib.h>

typedef struct Tree {
    struct Tree* left;
    struct Tree* right;
    int data;
}tree_t;

typedef struct Node {
    tree_t* data;
    struct Node* next;
}node_t;

typedef struct Queue {
    node_t* front;
    node_t* rear;
}queue_t;

void enqueue(queue_t* ptr, tree_t* tree) {
    node_t* node = (node_t*)malloc(sizeof(node_t));
        node->data = tree;
        node->next = NULL;
    if(ptr->rear == NULL) {
        ptr->front = node;
        ptr->rear = node;
    }else {
        ptr->rear->next = node;
        ptr->rear = ptr->rear->next;
    }
}

tree_t* dequeue(queue_t* ptr) {
    if(ptr->front == NULL) {
        return NULL;
    }else {
        tree_t* temp = ptr->front->data;
        node_t* temp2 = ptr->front;
        ptr->front = ptr->front->next;
        free(temp2);
        if(ptr->front == NULL) {
            ptr->rear = NULL;
        } 
        return temp;
    }
}

void insert(tree_t **ptr, int data) {
    tree_t* tree = (tree_t*)malloc(sizeof(tree_t));
    tree->data = data;
    tree->left = NULL;
    tree->right = NULL;
    if(*ptr==NULL) {
        *ptr = tree;
    }else {
        queue_t queue;
        queue.front = NULL;
        queue.rear = NULL;
        enqueue(&queue, *ptr);
        while(queue.front != NULL) {
            tree_t* temp = dequeue(&queue);
            if(temp->left == NULL) {
                temp->left = tree;
                return;
            }else {
                enqueue(&queue, temp->left);
            }
            if(temp->right == NULL) {
                temp->right = tree;
                return;
            }else {
                enqueue(&queue, temp->right);
            }

        }
    }
}

void DFS(tree_t* ptr) {
    if(ptr==NULL) {
        return;
    }
        
    else {
        DFS(ptr->left);
        DFS(ptr->right);
        printf("%d ", ptr->data); //postfix order
    }
}

void BFS(tree_t* ptr) {
    if(ptr == NULL)
        return;
    queue_t queue;
    queue.front = NULL;
    queue.rear = NULL;
    enqueue(&queue, ptr);
    while(queue.front != NULL) {
        tree_t* tree = dequeue(&queue);
        printf("%d ", tree->data); //BFS has no prefix infix postfix
        if(tree->left!=NULL)
            enqueue(&queue, tree->left);
        if(tree->right!=NULL)
            enqueue(&queue, tree->right);
    }
    
}

int level(tree_t* ptr) {
    if(ptr==NULL) {
        return 0;
    }else {
        int left = level(ptr->left);
        int right = level(ptr->right);
        return 1+(left>right?left:right);
    }
}

int main() {
    tree_t* root = NULL;
    insert(&root, 100);
    insert(&root, 90);
    insert(&root, 80);
    insert(&root, 70);
    insert(&root, 60);
    insert(&root, 50);
    insert(&root, 40);
    insert(&root, 30);
    insert(&root, 20);
    insert(&root, 10);
    DFS(root);
    printf("\n");
    BFS(root);
    return 0;
}