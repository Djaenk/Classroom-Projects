#include "bankers.h"

struct State {
  int n, m;
  int* available, *max, *allocation, *need;
  int* work, *finish;
  pthread_mutex_t mutex;
};

State* state_create(int* available, int threads, int resources) {
  State* state = malloc(sizeof(State));
  state->n = threads;
  state->m = resources;
  state->available = malloc(resources * sizeof(int));
  memcpy(state->available, available, resources);
  state->max = calloc(threads * resources, sizeof(int));
  state->allocation = calloc(threads * resources, sizeof(int));
  state->need = calloc(threads * resources, sizeof(int));
  state->work = malloc(resources * sizeof(int));
  state->finish = malloc(threads * sizeof(int));
  pthread_mutex_init(&state->mutex, NULL);
  return state;
}

void state_destroy(State* state) {
  free(state->available);
  free(state->max);
  free(state->allocation);
  free(state->need);
  pthread_mutex_destroy(&state->mutex);
  free(state);
}

int state_get_resource_count(State* state) {
  return state->m;
}

void state_set_max(State* state, int thread, int* resource_list, int resource_count) {
  pthread_mutex_lock(&state->mutex);
  memset(state->max, 0, state->m);
  for (int i = 0; i < resource_count; ++i) {
    ++state->max[state->m * thread + resource_list[i]];
  }
  for (int i = state->m * thread; i < state->m * (thread + 1); ++i) {
    state->need[i] = state->max[i] - state->allocation[i];
  }
  pthread_mutex_unlock(&state->mutex);
}

void state_alloc(State* state, int thread, int* resources) {
  for (int i = 0; i < state->m; ++i) {
    state->available[i] -= resources[i];
    state->allocation[state->m * thread + i] += resources[i];
    state->need[state->m * thread + i] -= resources[i];
  }
}

void state_dealloc(State* state, int thread, int* resources) {
  for (int i = 0; i < state->m; ++i) {
    state->available[i] += resources[i];
    state->allocation[state->m * thread + i] -= resources[i];
    state->need[state->m * thread + i] += resources[i];
  }
}

int state_check_safety(State* state) {
  memcpy(state->work, state->available, state->m);
  memset(state->finish, 0, state->n);

  int i, j, satisfiable;
  find_unfinished:
  for (i = 0; i < state->n; ++i) {
    if (state->finish[i] == 0) {
      for (j = 0; j < state->m; ++j) {
        satisfiable = 1;
        if (state->need[state->m * i + j] > state->work[j]) {
          satisfiable = 0;
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

int Request(State* state, int thread, int* resources) {
  for (int i = 0; i < state->m; ++i) {
    if (resources[i] > state->need[state->m * thread + i]) {
      return -1; //thread has exceeded its maximum claim
    }
    if (resources[i] > state->available[state->m * thread + i]) {
      return 0; //insufficient resources to satisfy request
    }
  }
  pthread_mutex_lock(&state->mutex);
  state_alloc(state, thread, resources);
  if (state_check_safety(state)) {
    pthread_mutex_unlock(&state->mutex);
    return 1;
  }
  else {
    state_dealloc(state, thread, resources);
    pthread_mutex_unlock(&state->mutex);
    return 0;
  }
}

void Return(State* state, int thread, int* resources) {
  pthread_mutex_lock(&state->mutex);
  state_dealloc(state, thread, resources);
  pthread_mutex_unlock(&state->mutex);
}