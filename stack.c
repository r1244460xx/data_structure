#include<stdio.h>
#include<stdlib.h>
typedef struct Node{
    int data;
    struct Node* next;
}Node_t;

void push(int data, Node_t **ptr) {
    Node_t* node = (Node_t*)malloc(sizeof(Node_t));
    if(node == NULL) {
        return;
    }
    node->data = data;
    node->next = *ptr;
    *ptr = node;
}

void pop(Node_t **ptr) {
    if(*ptr==NULL) {
        return;
    }else {
        Node_t* node = *ptr;
        *ptr = (*ptr)->next;
        free(node);
    }
}

void print(Node_t* head) {
    while(head != NULL) {
        printf("|%d|\n", head->data);
        printf("--\n");
        head = head->next;
    }
    printf("\n");
}

int main() {
    Node_t *head = NULL;
    push(50, &head);
    push(40, &head);
    push(30, &head);
    push(20, &head);
    push(10, &head);
    pop(&head);
    print(head);
    pop(&head);
    pop(&head);
    print(head);
    return 0;
}