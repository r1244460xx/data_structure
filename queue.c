#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
}Node_t;

typedef struct Queue {
    Node_t* head;
    Node_t* tail;
}Queue_t;

void enqueue(int data, Queue_t* queue) {
    Node_t* node = (Node_t*)malloc(sizeof(Node_t));
    node->data = data;
    node->next = NULL;
    if(queue->head==NULL) {
        queue->tail = node;
        queue->head = node;
    }else {
        queue->tail->next = node;
        queue->tail = queue->tail->next;
    }
}

void dequeue(Queue_t* queue) {
    if(queue->head == NULL) {
        return;
    }else {
        Node_t* node = queue->head;
        queue->head = queue->head->next;
        free(node);
        if(queue->head == NULL) {
            queue->tail = NULL;
        }
    }
}

void print(Node_t* head) {
    while(head != NULL) {
        printf("|%d|-> ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main() {
    Queue_t queue;
    queue.head = NULL;
    queue.tail = NULL;
    enqueue(10, &queue);
    enqueue(20, &queue);
    enqueue(30, &queue);
    enqueue(40, &queue);
    enqueue(50, &queue);
    print(queue.head);
    dequeue(&queue);
    dequeue(&queue);
    dequeue(&queue);
    print(queue.head);
    return 0;
}