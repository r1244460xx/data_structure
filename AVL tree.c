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

int level(tree_t* ptr) {
    if(ptr==NULL) {
        return -1;
    }else {
        int left = level(ptr->left);
        int right = level(ptr->right);
        return 1+(left>right?left:right);
    }
}

int balance(tree_t* ptr) {
    int left, right;
    if(ptr->left != NULL) {
        left = ptr->left->height;
    }else 
        left = -1;
    if(ptr->right != NULL) {
        right = ptr->right->height;
    }else 
        right = -1;
    return left - right;
}

tree_t* left_rotation(tree_t* ptr) {
    tree_t* temp = ptr->right;
    ptr->right = ptr->right->left;
    temp->left = ptr;
    return temp;
}

tree_t* right_rotation(tree_t* ptr) {
    tree_t* temp = ptr->left;
    ptr->left = ptr->left->right;
    temp->right = ptr;
    return temp;
}

tree_t* self_balance(tree_t* ptr) {
    int bf = balance(ptr);
    if(bf > 1) {
        if(balance(ptr->left)<0) { //LR
            ptr->left =  left_rotation(ptr->left);
        }
        ptr = right_rotation(ptr);
    }else if(bf < -1) {
        if(balance(ptr->right)>0) { //RL
            ptr->right =  right_rotation(ptr->right);
        }
        ptr = left_rotation(ptr);
    }
    return ptr;
}

tree_t* insert(tree_t *ptr, int data) {
    if(ptr==NULL) {
        tree_t* tree = (tree_t*)malloc(sizeof(tree_t));
        tree->data = data;
        tree->left = NULL;
        tree->right = NULL;
        tree->height = 0;
        return tree;
    }else {
        if(ptr->data > data) {
            ptr->left = insert(ptr->left, data);
        }else {
            ptr->right = insert(ptr->right, data);
        }
    }
    ptr->height = level(ptr);
    ptr = self_balance(ptr);    
    return ptr;
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

tree_t* delete(tree_t* ptr, int data) {
    if(ptr == NULL) {
        printf("No tree\n");
        return NULL;
    }else if(ptr->data == data){
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
            ptr->left = delete(ptr->left, ptr->data);
            ptr->height = level(ptr);
            ptr = self_balance(ptr);
            return ptr;
        }   
    }else {
        if(ptr->left != NULL)
            ptr->left = delete(ptr->left, data);
        if(ptr->right != NULL)
            ptr->right = delete(ptr->right, data);
        ptr->height = level(ptr);
        ptr = self_balance(ptr);
        return ptr;
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
    if(ptr == NULL) {
        printf("No node\n");
        return;
    }
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
    printf("\n");
}   

int main() {
    tree_t* root = NULL;
    root = insert(root, 50);
    root = insert(root, 25);
    root = insert(root, 90);
    root = insert(root, 10);
    root = insert(root, 30);
    root = insert(root, 27);
    root = insert(root, 45);
    root = delete(root, 10);
    root = delete(root, 27);
    root = delete(root, 25);
    DFS(root);
    printf("\n");
    BFS(root);
    return 0;
}