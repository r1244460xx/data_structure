#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

enum Color {
    BLACK,
    RED
};

typedef struct Tree {
    struct Tree* left;
    struct Tree* right;
    struct Tree* parent;
    int data;
    int color;
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

tree_t* left_rotate(tree_t* tree) {
    tree_t* temp = tree->right;
    tree_t* parent_temp = tree->parent;
    tree->right = temp->left;
    temp->left = tree; 
    tree->parent = temp;
    temp->parent = parent_temp;
    return temp;
}

tree_t* right_rotate(tree_t* tree) {
    tree_t* temp = tree->left;
    tree_t* parent_temp = tree->parent;
    tree->left = temp->right;
    temp->right = tree;
    tree->parent = temp; 
    temp->parent = parent_temp;
    return temp;
}

int level(tree_t* tree) {
    if(tree==NULL) {
        return -1;
    }else {
        int left = level(tree->left);
        int right = level(tree->right);
        return 1+(left>right?left:right);
    }
}

int balance(tree_t* tree) {
    int left = level(tree->left);
    int right = level(tree->right);
    return left - right;
}

void update(tree_t** root, tree_t* tree) {
    while(tree->parent != NULL && tree->parent->color==RED) {
        tree_t* parent = tree->parent;
        tree_t* grandpa = tree->parent->parent;
        if(parent == grandpa->left) {
            if(grandpa->right != NULL && grandpa->right->color==RED) {
                parent->color = BLACK;
                grandpa->right->color = BLACK;
                grandpa->color = RED;
                tree = grandpa;  //jump to parent
            }else { //uncle is BLACK
                if(tree == parent->right) { //new node is on right
                    grandpa->left = left_rotate(parent);
                    parent = grandpa->left;
                    tree = parent->left;
                }
                grandpa->color = RED;
                parent->color = BLACK;

                if(grandpa!=*root) {
                    if(grandpa->parent->left == grandpa) {
                        tree_t* temp = grandpa->parent;
                        temp->left = right_rotate(grandpa);
                    }else {
                        tree_t* temp = grandpa->parent;
                        temp->right = right_rotate(grandpa);
                    }
                }else {
                    *root = right_rotate(grandpa);
                }
            }
        }else { //parent == grandpa->right
            if(grandpa->left != NULL && grandpa->left->color==RED) {
                parent->color = BLACK;
                grandpa->left->color = BLACK;
                grandpa->color = RED;
                tree = grandpa;  //jump to parent
            }else { //uncle is BLACK
                if(tree == parent->left) { //new node is on right
                    grandpa->right = right_rotate(parent);
                    parent = grandpa->right;
                    tree = parent->right;
                }
                grandpa->color = RED;
                parent->color = BLACK;
                
                if(grandpa!=*root) {
                    if(grandpa->parent->left == grandpa) {
                        tree_t* temp = grandpa->parent;
                        temp->left = left_rotate(grandpa);
                    }else {
                        tree_t* temp = grandpa->parent;
                        temp->right = left_rotate(grandpa);
                    }
                }else { //grandpa
                    *root = left_rotate(grandpa);
                }
            }
        }
    }    
    if((*root)->color==RED) {
        (*root)->color = BLACK;
    }
}

tree_t* delete(tree_t* tree, int data) {
    if(tree->data == data) {
        if(tree->left==NULL && tree->right==NULL) {
            free(tree);
            return NULL;
        }else if(tree->left!=NULL && tree->right==NULL) {
            tree_t* temp = tree->left;
            free(tree);
            return temp;
        }else if(tree->left==NULL && tree->right!=NULL) {
            tree_t* temp = tree->right;
            free(tree);
            return temp;
        }else {
            tree_t* temp = tree->left;
            while(temp->right!=NULL) {
                temp = temp->right;
            }
            tree->data = temp->data;
            tree->left = delete(tree->left, temp->data);
            return tree;
        }
    }else {
        if(tree->data > data) {
            tree->left = delete(tree->left, data);
        }else if(tree->data < data) {
            tree->right = delete(tree->right, data);
        }
        return tree;
    }
}

tree_t* insert(tree_t* tree, tree_t* node) {
    if(tree==NULL) {
        return node;
    }else {
        if(tree->data > node->data) {
            tree->left = insert(tree->left, node);
            tree->left->parent = tree;
        }else if(tree->data < node->data) {
            tree->right = insert(tree->right, node);
            tree->right->parent = tree;
        }
        return tree;
    }
}

void RBT_insert(tree_t** root, int data) {
    tree_t* node = (tree_t*)malloc(sizeof(tree_t));
    node->color = RED;
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    *root = insert(*root, node);
    update(root, node);
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
        printf("No data\n");
        return;
    }
    queue_t queue;
    queue.front = NULL;
    queue.rear = NULL;
    enqueue(&queue, ptr);
    while(queue.front != NULL) {
        tree_t* tree = dequeue(&queue);
        printf("%d->%d ",tree->color ,tree->data); //BFS has no prefix infix postfix
        if(tree->left!=NULL)
            enqueue(&queue, tree->left);
        if(tree->right!=NULL)
            enqueue(&queue, tree->right);
    }
    printf("\n");
}   

int main() {
    tree_t* root = NULL;
    RBT_insert(&root, 3);
    RBT_insert(&root, 21);
    RBT_insert(&root, 32);
    RBT_insert(&root, 15);
    DFS(root);
    printf("\n");
    BFS(root);
    return 0;
}