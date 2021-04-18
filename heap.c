#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 50

typedef struct Heap {
    int heap[MAX_SIZE+1];
    int size;
}heap_t;

void min_heapify(heap_t* heap, int index) {
    if(heap->heap[index] > heap->heap[2*index]) {
        int data = heap->heap[index];
        heap->heap[index] = heap->heap[2*index];
        heap->heap[2*index] = data;
        min_heapify(heap, 2*index);
    }
        
    if(heap->heap[index] > heap->heap[2*index+1]) {
        int data = heap->heap[index];
        heap->heap[index] = heap->heap[2*index+1];
        heap->heap[2*index+1] = data;
        min_heapify(heap, 2*index+1);
    }
}



void max_heapify(heap_t* heap, int index) {
    int temp = 0;
    if(2*index <= heap->size) {
        if(heap->heap[index]<heap->heap[2*index]) {
            int data = heap->heap[index];
            heap->heap[index] = heap->heap[2*index];
            heap->heap[2*index] = data;
            temp = 2*index;
        }
    }
    if(2*index+1 <= heap->size) {
        if(heap->heap[index]<heap->heap[2*index+1]) {
            int data = heap->heap[index];
            heap->heap[index] = heap->heap[2*index+1];
            heap->heap[2*index+1] = data;
            temp = 2*index+1;
        }
    }
    if(temp!=0) {
        max_heapify(heap, temp);
    }
}

void max_heap(heap_t* heap) {
    int index = heap->size/2;
    for(int i=index; i>0; i--) {
        max_heapify(heap, i);
    }
}

void min_heap(heap_t* heap) {
    int index = heap->size/2;
    for(int i=index; i>0; i--) {
        min_heapify(heap, index);
    }
}

void insert(heap_t* heap, int data) {
    if(heap->size <= MAX_SIZE) {
        heap->heap[++heap->size] = data;
        //max_heap(heap);
        max_heapify(heap, heap->heap[heap->size/2]);
    }
}

void delete(heap_t* heap, int data) {
    for(int i=1; i<=heap->size; i++) {
        if(heap->heap[i] == data) {
            heap->heap[i] = heap->heap[heap->size];
            heap->heap[heap->size] = 0;
            heap->size--;
            max_heap(heap);
            break;
        }
    }
}

void heapsort(heap_t* heap, int* arr) {
    heap_t temp = *heap;
    for(int i=0; i<heap->size; i++) {
        max_heap(&temp);
        arr[i] = temp.heap[1];
        delete(&temp, temp.heap[1]);
    }
}

void print(heap_t* heap) {
    for(int i=1; i<=heap->size; i++) {
        printf("%d ", heap->heap[i]);
    }
    printf("\n");
}

int main() {
    heap_t heap;
    heap.size = 0;
    for(int i=0; i<=MAX_SIZE; i++) {
        heap.heap[i] = 0;
    }
    insert(&heap, 33);
    insert(&heap, 15);
    insert(&heap, 38);
    insert(&heap, 54);
    insert(&heap, 72);
    insert(&heap, 40);
    insert(&heap, 90);
    insert(&heap, 6);
    insert(&heap, 95);
    print(&heap);
    int arr[MAX_SIZE] = {0};
    heapsort(&heap, arr);
    for(int i=0; i<heap.size; i++) {
        printf("%d ", arr[i]);
    }
}