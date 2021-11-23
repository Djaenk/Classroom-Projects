#include <stdlib.h>
#include <string.h>
#include <pthread.h>

typedef struct State State;

State* state_create(int* available, int threads, int resources);

void state_destroy(State* state);

int state_get_resource_count(State* state);

void state_set_max(State* state, int thread, int* resource_list, int resource_count);

int Request(State* state, int thread, int* resources);

void Return(State* state, int thread, int* resources);