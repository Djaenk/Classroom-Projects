#include "bankers.h"

struct State {
  /** Number of processes and distinct resources */
  int n, m;

  /** Vector of total resources available */
  int* available;

  /** n x m matrix data structures for Banker's algorithm*/
  int *max, *allocation, *need;

  /** Utility vectors for deadlock detection */
  int* work, *finish;

  /** Mutex limits modification of state to one process at a time */
  pthread_mutex_t mutex;
};

State* state_create(int* available, int processes, int resources) {
  State* state = malloc(sizeof(State));
  state->n = processes;
  state->m = resources;
  state->available = malloc(resources * sizeof(int));
  memcpy(state->available, available, resources * sizeof(int));
  state->max = calloc(processes * resources, sizeof(int));
  state->allocation = calloc(processes * resources, sizeof(int));
  state->need = calloc(processes * resources, sizeof(int));
  state->work = malloc(resources * sizeof(int));
  state->finish = malloc(processes * sizeof(int));
  pthread_mutex_init(&state->mutex, NULL);
  return state;
}

void state_destroy(State* state) {
  free(state->available);
  free(state->max);
  free(state->allocation);
  free(state->need);
  free(state->work);
  free(state->finish);
  pthread_mutex_destroy(&state->mutex);
  free(state);
}

int state_resource_count(State* state) {
  return state->m;
}

void state_set_max(State* state, int process, int* resource_list, int resource_count) {
  pthread_mutex_lock(&state->mutex); // Begin critical section: modification of max and need matrices
  memset(state->max + state->m * process, 0, state->m * sizeof(int));
  for (int i = 0; i < resource_count; ++i) {
    ++state->max[state->m * process + resource_list[i]];
  }
  for (int i = state->m * process; i < state->m * (process + 1); ++i) {
    state->need[i] = state->max[i] - state->allocation[i];
  }
  pthread_mutex_unlock(&state->mutex); // End critical section
}

void state_alloc(State* state, int process, int* resources) {
  for (int i = 0; i < state->m; ++i) {
    state->available[i] -= resources[i];
    state->allocation[state->m * process + i] += resources[i];
    state->need[state->m * process + i] -= resources[i];
  }
}

void state_dealloc(State* state, int process, int* resources) {
  for (int i = 0; i < state->m; ++i) {
    state->available[i] += resources[i];
    state->allocation[state->m * process + i] -= resources[i];
    state->need[state->m * process + i] += resources[i];
  }
}

int state_check_safety(State* state) {
  memcpy(state->work, state->available, state->m * sizeof(int));
  memset(state->finish, 0, state->n * sizeof(int));

  int i, j, satisfiable;
  find_unfinished:
  for (i = 0; i < state->n; ++i) {
    if (state->finish[i] == 0) {
      for (j = 0; j < state->m; ++j) {
        satisfiable = 1;
        if (state->need[state->m * i + j] > state->work[j]) {
          satisfiable = 0;
          break;
        }
      }
      if (satisfiable) {
        for (j = 0; j < state->m; ++j) {
          state->work[j] += state->allocation[state->m * i + j];
        }
        state->finish[i] = 1;
        goto find_unfinished;
      }
    }
  }
  for (i = 0; i < state->n; ++i) {
    if (state->finish[i] == 0) {
      return 0;
    }
  }
  return 1;
}

void state_print(State* state) {
  printf("\n");
  for (int i = 0; i < state->m; ++i) {
    printf("%*d ", 3, state->available[i]);
  }
  printf("\n\n");
  for (int i = 0; i < state->n; ++i) {
    for (int j = 0; j < state->m; ++j) {
      printf("%*d ", 3, state->max[state->m * i + j]);
    }
    printf("     ");
    for (int j = 0; j < state->m; ++j) {
      printf("%*d ", 3, state->allocation[state->m * i + j]);
    }
    printf("     ");
    for (int j = 0; j < state->m; ++j) {
      printf("%*d ", 3, state->need[state->m * i + j]);
    }
    printf("\n");
  }
  printf("\n");
}

int Request(State* state, int process, int* resources) {
  for (int i = 0; i < state->m; ++i) {
    if (resources[i] > state->need[state->m * process + i]) {
      return -2; // process has exceeded its maximum claim
    }
    if (resources[i] > state->available[i]) {
      return -1; // insufficient resources to satisfy request
    }
  }
  pthread_mutex_lock(&state->mutex); // Begin critical section: modificaton of all matrices
  state_alloc(state, process, resources);
  if (state_check_safety(state)) {
    pthread_mutex_unlock(&state->mutex); //End critical section
    return 1; // Request granted
  }
  else {
    state_dealloc(state, process, resources);
    pthread_mutex_unlock(&state->mutex); //End critical section
    return 0; // Request would result in deadlock
  }
}

int Request2(State* state, int process, int* resources) {
  return Request(state, process, resources);
}

void Release(State* state, int process, int* resources) {
  pthread_mutex_lock(&state->mutex); // Begin critical section: modification of all matrices
  state_dealloc(state, process, resources);
  pthread_mutex_unlock(&state->mutex); // Begin critical section: modification of all matrices
}