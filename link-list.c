#include<stdio.h>
#include<stdlib.h>
typedef struct Node{
    int data;
    struct Node* next;
}Node_t;

int insert(int data, Node_t **ptr) {
    if(*ptr != NULL) {
        Node_t* node = (Node_t*)malloc(sizeof(Node_t));
        if(node != NULL) {
            node->data = data;
            node->next = NULL;
            Node_t* temp_ptr = *ptr;
            while(temp_ptr->next != NULL) {
                temp_ptr = temp_ptr->next;
            }
            temp_ptr->next = node;
            return 0;
        }else {
            return -1;
        }
        

    }else {
        Node_t* node = (Node_t*)malloc(sizeof(Node_t));
        if(node != NULL) {
            node->data = data;
            node->next = NULL;
            *ptr = node;
            return 0;
        }else
            return -1;
    }
}

void print(Node_t* head) {
    while(head != NULL) {
        printf("%d-> ", head->data);
        head = head->next;
    }
    printf("\n");
}

void delete(Node_t **ptr) {
    if((*ptr)->next == NULL) {
        free(*ptr);
        *ptr = NULL;
    }else {
        Node_t* temp_ptr = *ptr;
        while(temp_ptr->next->next != NULL) {
            temp_ptr = temp_ptr->next;
        }
        free(temp_ptr->next);
        temp_ptr->next = NULL;
    }
}

int main() {
    Node_t *head = NULL;
    insert(50, &head);
    insert(40, &head);
    insert(30, &head);
    insert(20, &head);
    insert(10, &head);
    print(head);
    delete(&head);
    print(head);
    delete(&head);
    print(head);
    delete(&head);
    print(head);
}