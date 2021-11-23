#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <string.h>
#include "queue.h"
#include "bankers.h"

#define MS_TO_NS 1000000

typedef struct Philosopher {
  pthread_mutex_t* mutex;
  int table;
  int* active;
  char* name;
  int tool_count;
  int* tools;
  State* state;
  int finished;
} Philosopher;

/**
 * @brief player function to be run in a thread
 * @param param is the void pointer passed to the thread
 */
void* philosopher(void* param) {
  Philosopher* philosopher = param;
  time_t t;
  struct timespec sleep_request = {1, 0};
  int tool_index;
  Queue* request_queue = queue_create(philosopher-> tools, philosopher->tool_count);
  int tool_request[state_get_resource_count(philosopher->state)];
  int granted;

  // wait for start of buffet
  while (*philosopher->active == -1);
  pthread_mutex_lock(philosopher->mutex);
  ++(*philosopher->active);
  pthread_mutex_unlock(philosopher->mutex);

  while (queue_size(request_queue)) {
    ++tool_request[queue_pop(request_queue)];
    if (time(&t) % 2 == 0) {
      ++tool_request[queue_pop(request_queue)];
    }
    granted = Request(philosopher->state, philosopher->table, tool_request);
    for (int i = 0; i < state_get_resource_count(philosopher->state); ++i) {
      while (tool_request[i]) {
        --tool_request[i];
        if (!granted) {
          queue_push(request_queue, i);
        }
      }
    }
    sleep_request.tv_nsec = (t % 1000) * MS_TO_NS;
    nanosleep(&sleep_request, NULL);
  }
  sleep_request.tv_sec = 2;
  sleep_request.tv_nsec = 0;
  nanosleep(&sleep_request, NULL);
  for (int i = 0; i < philosopher->tool_count; ++i) {
    ++tool_request[philosopher->tools[i]];
  }
  Return(philosopher->state, philosopher->table, tool_request);
  queue_destroy(request_queue);
  pthread_exit(NULL);
}

/**
 * @brief main function, assigns buffet tables to philosophers
 */
int main(int argc, char* argv[]){
  pthread_mutex_t mutex;
  int k, m, n;
  State* state;
  Philosopher* philosophers;
  int active = -1;

  if (argc > 1) {
    pthread_mutex_init(&mutex, NULL);
    char line[1000];
    char* token;
    int length;

    FILE* file = fopen(argv[1], "r");
    fgets(line, 21, file);
    token = strtok(line, " ");
    k = atoi(token);
    token = strtok(NULL, " ");
    m = atoi(token);
    token = strtok(NULL, " ");
    n = atoi(token);

    int tools[k];
    fgets(line, 999, file);
    token = strtok(line, " ");
    for (int i = 0; token != NULL; ++i) {
      tools[i] = atoi(token);
      token = strtok(NULL, " ");
    }

    state = state_create(tools, m, k);

    philosophers = malloc(n * sizeof(Philosopher));
    int p;
    for (int i = 0; i < n; ++i) {
      fgets(line, 999, file);

      philosophers[i].mutex = &mutex;
      philosophers[i].active = &active;
      philosophers[i].state = state;
      philosophers[i].finished = 0;

      token = strtok(line, " ");
      length = strlen(token);
      philosophers[i].name = malloc((length + 1) * sizeof(char));
      strcpy(philosophers[i].name, token);

      token = strtok(NULL, " ");
      p = atoi(token);
      philosophers[i].tool_count = p;
      philosophers[i].tools = malloc(p * sizeof(int));

      token = strtok(NULL, " ");
      for (int j = 0; token != NULL; j++) {
        philosophers[i].tools[j] = atoi(token); 
        token = strtok(NULL, " ");
      }
    }

    fclose(file);
  }
  else {
    return -1;
  }

  // srand(time(null));

  // Create all thread and seat initial philosophers
  pthread_t tables[m];
  for (int i = 0; i < m; ++i) {
    philosophers[i].table = i;
    pthread_create(&tables[i], NULL, philosopher, &philosophers[i]);
  }
  int next = m;

  // Start the buffet and wait for philosophers to begin eating
  active = 0;
  while (active == 0);

  // Reassign tables as necessary if any philosophers have finished
  while (active > 1) {
    for (int i = next - m; i < next; ++i) {
      if (philosophers[i].finished) {
        int table = philosophers[i].table;
        pthread_join(tables[table], NULL);
        if (next < n) {
          philosophers[next].table = table;
          pthread_create(&tables[table], NULL, philosopher, &philosophers[next]);
          ++next;
        }
      }
    }
  }

  pthread_mutex_destroy(&mutex);
  state_destroy(state);
  return 0;
}