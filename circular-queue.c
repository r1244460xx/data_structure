#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 4

void enqueue(int data, int* cqueue, int* front, int* rear) {
    if(*front == -1 && *rear == -1) {
        (*front)++;
        (*rear)++;
        cqueue[*rear] = data;
    }else if((*rear+1)%MAX_SIZE == *front) {
        //return;
    }else {
        *rear = (*rear+1)%MAX_SIZE;
        cqueue[*rear] = data;
    }
} 

void dequeue(int* cqueue, int* front, int* rear) {
    if(*front == -1 && *rear == -1)
        return;
    else if(*front == *rear) {
        cqueue[*front] = 0;
        *front = -1;
        *rear = -1;
    }
    else {
        cqueue[*front] = 0;
        *front = (*front+1)%MAX_SIZE; 
    }
}

void print(int* cqueue, int front, int rear) {
    if(front==-1 && rear==-1)
        return;
    while(1) {
        printf("%d -> ", cqueue[front]);
        if(front == rear)
            break;
        front = (front+1)%MAX_SIZE;
    }
    printf("\n");
}

int main() {
    int cqueue[MAX_SIZE]={0};
    int front = -1, rear = -1;
    enqueue(10, cqueue, &front, &rear);
    enqueue(20, cqueue, &front, &rear);
    enqueue(30, cqueue, &front, &rear);
    enqueue(40, cqueue, &front, &rear);
    print(cqueue, front, rear);
    dequeue(cqueue, &front, &rear);
    print(cqueue, front, rear);
    dequeue(cqueue, &front, &rear);
    print(cqueue, front, rear);
    dequeue(cqueue, &front, &rear);
    print(cqueue, front, rear);
    return 0;
}