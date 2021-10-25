#include <pthread.h>
#include <stdio.h>

typedef struct Queue {
  int start;
  int end;
  int empty;
  int full;
  int buffer[10];
} Queue;

Queue queue = {0, 0, 1, 0};

int main(int argc, char* argv[]){
  pthread_t tid[];
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  return 0;
}