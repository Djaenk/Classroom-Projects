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
 * @brief Philosopher function to be run in a thread
 * 
 * @param param is the void pointer passed to the thread
 */
void* philosopher(void* param) {
  Philosopher* philosopher = param;
  time_t t;
  struct timespec sleep_request = {1, 0};
  Queue* request_queue = queue_create(philosopher->tools, philosopher->tool_count);
  Queue* held_queue = queue_create(NULL, philosopher->tool_count);
  int tool_request[state_resource_count(philosopher->state)];
  memset(tool_request, 0, state_resource_count(philosopher->state) * sizeof(int));
  int granted;
  state_set_max(philosopher->state, philosopher->table, philosopher->tools, philosopher->tool_count);

  // Wait for start of buffet
  while (!*philosopher->active);

  // Request tools while philosopher doesn't have all tools
  while (queue_size(request_queue)) {
    if (time(&t) % 2){
      ++tool_request[queue_pop(request_queue)];
    }
    else {
      int request_count = 2 + (t / 25) % (queue_size(request_queue) - 1);
      for (int i = 0; i < request_count; ++i) {
        ++tool_request[queue_pop(request_queue)];
      }
    }
    granted = Request2(philosopher->state, philosopher->table, tool_request);

    pthread_mutex_lock(philosopher->mutex); // Begin "critical" section: write to stdout
    printf("%*s requests", 20, philosopher->name);
    for (int i = 0; i < state_resource_count(philosopher->state); ++i) {
      printf(" %d", tool_request[i]);
      while (tool_request[i]) {
        --tool_request[i];
        if (granted < 1) {
          queue_push(request_queue, i);
        }
        else {
          queue_push(held_queue, i);
        }
      }
    }
    if (granted == 1) {
      printf(", granted\n");
      pthread_mutex_unlock(philosopher->mutex); // End "critical" section
    }
    else {
      printf(", denied (code %d)\n", granted);
      pthread_mutex_unlock(philosopher->mutex); // End "critical" section

      sleep_request.tv_nsec = 0;
      nanosleep(&sleep_request, NULL);

      int held = queue_pop(held_queue);
      queue_push(request_queue, held);
      ++tool_request[held];
      Release(philosopher->state, philosopher->table, tool_request);
      --tool_request[held];
    }

    sleep_request.tv_nsec = (t % 1000) * MS_TO_NS;
    nanosleep(&sleep_request, NULL);
  }

  sleep_request.tv_sec = 2;
  sleep_request.tv_nsec = 0;
  nanosleep(&sleep_request, NULL);

  memset(tool_request, 0, state_resource_count(philosopher->state) * sizeof(int));
  for (int i = 0; i < philosopher->tool_count; ++i) {
    ++tool_request[philosopher->tools[i]];
  }
  Release(philosopher->state, philosopher->table, tool_request);

  pthread_mutex_lock(philosopher->mutex); // Begin critical section: decrement philosopher counter
  printf("%*s finished, releasing", 20, philosopher->name);
  for (int i = 0; i < state_resource_count(philosopher->state); ++i) {
    printf(" %d", tool_request[i]);
  }
  printf("\n");
  pthread_mutex_unlock(philosopher->mutex); // End "critical" section

  philosopher->finished = 1;
  queue_destroy(request_queue);
  pthread_exit(NULL);
}

/**
 * @brief Main function, serves as a restaurant assigning buffet tables to philosophers
 */
int main(int argc, char* argv[]){
  pthread_mutex_t mutex;
  int k, m, n;
  State* state;
  Philosopher* philosophers;
  int active = 0;

  // Create a list of all philosophers and initialize system state
  if (argc > 1) {
    char line[1000];
    char* token;
    int length;

    pthread_mutex_init(&mutex, NULL);

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
    for (int i = 0; token != NULL && i < k; ++i) {
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

      token = strtok(NULL, " \r\n");
      for (int j = 0; token != NULL && j < p; ++j) {
        philosophers[i].tools[j] = atoi(token); 
        token = strtok(NULL, " ");
      }
    }

    fclose(file);
  }
  else {
    return -1;
  }

  // Create all threads and seat initial philosophers
  pthread_t tables[m];
  for (int i = 0; i < m; ++i) {
    philosophers[i].table = i;
    printf("%s sits down at table %d\n", philosophers[i].name, philosophers[i].table);
    pthread_create(&tables[i], NULL, philosopher, &philosophers[i]);
  }
  int next = m;

  // Start the buffet
  active = 1;

  // Reassign tables as necessary when philosophers finish and more are waiting
  while (next < n) {
    for (int i = next - m; i < next; ++i) {
      if (philosophers[i].finished) {
        int table = philosophers[i].table;
        pthread_join(tables[table], NULL);
        if (next < n) {
          philosophers[next].table = table;
          pthread_mutex_lock(&mutex);
          printf("%s sits down at table %d\n", philosophers[next].name, table);
          pthread_create(&tables[table], NULL, philosopher, &philosophers[next]);
          pthread_mutex_unlock(&mutex);
          ++next;
        }
      }
    }
  }

  // Wait for remaining philosophers to finish
  for (int i = 0; i < m; ++i) {
    pthread_join(tables[i], NULL);
  }

  // Clean up
  pthread_mutex_destroy(&mutex);
  state_destroy(state);
  for (int i = 0; i < n; ++i) {
    free(philosophers[i].name);
    free(philosophers[i].tools);
  }
  free(philosophers);
  return 0;
}