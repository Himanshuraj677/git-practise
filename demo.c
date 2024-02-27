#include <stdio.h>
#include <stdlib.h>

#define PQ_SIZE 100

typedef struct {
    int *arr;
    int size;
    int capacity;
} PriorityQueue;

PriorityQueue* pq_create() {
    PriorityQueue *pq = (PriorityQueue *)malloc(sizeof(PriorityQueue));
    pq->arr = (int *)malloc(PQ_SIZE * sizeof(int));
    pq->size = 0;
    pq->capacity = PQ_SIZE;
    return pq;
}

void pq_enqueue(PriorityQueue *pq, int value) {
    if (pq->size == pq->capacity) {
        pq->capacity *= 2;
        pq->arr = (int *)realloc(pq->arr, pq->capacity * sizeof(int));
    }
    pq->arr[pq->size++] = value;
    int i = pq->size - 1;
    while (i > 0 && pq->arr[i] > pq->arr[(i - 1) / 2]) {
        int temp = pq->arr[i];
        pq->arr[i] = pq->arr[(i - 1) / 2];
        pq->arr[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

int pq_dequeue(PriorityQueue *pq) {
    if (pq->size == 0) {
        printf("Priority queue is empty.\n");
        return -1;
    }
    int max = pq->arr[0];
    pq->arr[0] = pq->arr[pq->size - 1];
    pq->size--;
    int i = 0;
    while (2 * i + 1 < pq->size) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int maxIndex = left;
        if (right < pq->size && pq->arr[right] > pq->arr[left]) {
            maxIndex = right;
        }
        if (pq->arr[i] < pq->arr[maxIndex]) {
            int temp = pq->arr[i];
            pq->arr[i] = pq->arr[maxIndex];
            pq->arr[maxIndex] = temp;
            i = maxIndex;
        } else {
            break;
        }
    }
    return max;
}

int pq_peek(PriorityQueue *pq) {
    if (pq->size == 0) {
        printf("Priority queue is empty.\n");
        return -1;
    }
    return pq->arr[0];
}

int pq_is_empty(PriorityQueue *pq) {
    return pq->size == 0;
}

void pq_destroy(PriorityQueue *pq) {
    free(pq->arr);
    free(pq);
}

int main() {
    PriorityQueue *pq = pq_create();
    pq_enqueue(pq, 3);
    pq_enqueue(pq, 2);
    pq_enqueue(pq, 4);
    pq_enqueue(pq, 1);
    while (!pq_is_empty(pq)) {
        printf("%d ", pq_dequeue(pq));
    }
    printf("\n");
    pq_destroy(pq);
    return 0;
}
