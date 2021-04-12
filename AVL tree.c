#include<stdio.h>
#include<stdlib.h>

typedef struct Tree {
    struct Tree* left;
    struct Tree* right;
    int data;
    int height;
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

void binary_insert(tree_t *node, tree_t *tree) {
    if(node->data > tree->data) {
        if(node->left == NULL) {
            node->left = tree;
            tree->height = level(tree);
        }else {
            binary_insert(node->left, tree);
        }
    }else {
        if(node->right == NULL) {
            node->right = tree;
            tree->height = level(tree);
        }else {
            binary_insert(node->right, tree);
        }
    } 
}

void insert(tree_t **ptr, int data) {
    tree_t* tree = (tree_t*)malloc(sizeof(tree_t));
    tree->data = data;
    tree->left = NULL;
    tree->right = NULL;
    tree->height = 0;
    if(*ptr==NULL) {
        *ptr = tree;
    }else {
        binary_insert(*ptr, tree);
    }
    
}

tree_t* find_min(tree_t* root) {
    while(root->left!=NULL) {
        root = root->left;
    }
    return root;
}

tree_t* find_max(tree_t* root) {
    while(root->right!=NULL) {
        root = root->right;
    }
    return root;
}

tree_t* binary_delete(tree_t* ptr, int data) {
    if(ptr->data == data) {
        if(ptr->left == NULL && ptr->right==NULL) {
            free(ptr);
            return NULL;
        }else if(ptr->left!=NULL && ptr->right==NULL) {
            tree_t* new = ptr->left;
            free(ptr);
            return new;
        }else if(ptr->left==NULL && ptr->right!=NULL) {
            tree_t* new = ptr->right;
            free(ptr);
            return new;
        }else {
            tree_t* new = find_max(ptr->left);
            ptr->data = new->data;
            ptr->left = binary_delete(ptr->left, ptr->data);
            return ptr;
        }   
    }else {
        if(ptr->left != NULL)
            ptr->left = binary_delete(ptr->left, data);
        if(ptr->right != NULL)
            ptr->right = binary_delete(ptr->right, data);
        return ptr;
    } 
}

void delete(tree_t** ptr, int data) {
    if((*ptr)==NULL)
        return;
    else {
        *ptr = binary_delete(*ptr, data);
    }
}

void DFS(tree_t* ptr) {
    if(ptr==NULL) {
        return;
    }else {
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
        printf("%d:%d ", tree->height, tree->data); //BFS has no prefix infix postfix
        if(tree->left!=NULL)
            enqueue(&queue, tree->left);
        if(tree->right!=NULL)
            enqueue(&queue, tree->right);
    }
    printf("\n");
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
    insert(&root, 67);
    insert(&root, 23);
    insert(&root, 73);
    insert(&root, 11);
    insert(&root, 47);
    insert(&root, 91);
    insert(&root, 33);
    insert(&root, 44);
    DFS(root);
    printf("\n");
    BFS(root);
    return 0;
}