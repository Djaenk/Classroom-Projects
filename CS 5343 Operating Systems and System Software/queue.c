#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

struct Queue {
  /** Queue is implemented as a circular buffer */
  int* buffer;

  /**
   * capacity contains maximum number of elements storable in queue
   * size tracks the number of elements in the queue
   * begin holds index of first element in queue
   * end holds index past last element in queue
   */
  int capacity, size, begin, end;
};

Queue* queue_create(int capacity) {
  Queue* q = (Queue*)malloc(sizeof(Queue));
  q->buffer = (int*)malloc(capacity * sizeof(int));
  q->capacity = capacity;
  q->size = 0;
  q->begin = 0;
  q->end = 0;
  return q;
}

void queue_destroy(Queue* q) {
  free(q->buffer);
  free(q);
}

void queue_push(Queue* q, int value) {
  q->buffer[q->end] = value;
  q->end = (q->end + 1) % q->capacity;
  ++q->size;
}

int queue_pop(Queue* q) {
  int retval = q->buffer[q->begin];
  q->begin = (q->begin + 1) % q->capacity;
  --q->size;
  return retval;
}

int queue_size(Queue* q) {
  return q->size;
}

void queue_print(Queue* q) {
  printf("\n( ");
  for (int i = 0; i < q->size; ++i) {
    printf("%d ", q->buffer[(i + q->begin) % q->capacity]);
  }
  printf(")\n\n");
}