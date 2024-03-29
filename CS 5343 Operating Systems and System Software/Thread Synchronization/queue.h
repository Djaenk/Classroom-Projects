#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * @brief FIFO queue data structure
 */
typedef struct Queue Queue;

/**
 * @brief Allocates and initializes a Queue
 * @param q is a pointer to the Queue to be initialized
 * @param capacity is the capacity of the initialized Queue
 * @return Queue* pointer to newly created Queue
 */
Queue* queue_create(int* initial, int capacity);

/**
 * @brief Destroys a Queue and deallocates its buffer
 * 
 * @param q is a pointer to the Queue to be destroyed 
 */
void queue_destroy(Queue* q);

/**
 * @brief Adds a value to the end of a Queue
 * 
 * @param q is a pointer to the Queue being pushed to
 * @param value is the integer value being pushed to the Queue
 */
void queue_push(Queue* q, int value);

/**
 * @brief Removes a value from the frond of a Queue
 * 
 * @param q is a pointer to the Queue being popped from
 * @return int value removed from queue
 */
int queue_pop(Queue* q);

/**
 * @brief Gets the size of the Queue
 * 
 * @param q is a pointer to the Queue
 * @return int size of the Queue
 */
int queue_size(Queue* q);

/**
 * @brief Prints the contents of a Queue to stdout
 * 
 * @param q is a pointer to the Queue to be printed
 */
void queue_print(Queue* q);