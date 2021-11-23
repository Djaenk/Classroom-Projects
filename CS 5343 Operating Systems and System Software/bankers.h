#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>

/**
 * @brief Data structure to track resource allocation of a multi process system 
 */
typedef struct State State;

/**
 * @brief Allocates and initializes a State
 * 
 * @param available is an array of how of each resource is available
 * @param processes is the number of processes in the system
 * @param resources is the number of distinct resources in the system
 * @return State* pointer to newly created State
 */
State* state_create(int* available, int processes, int resources);

/**
 * @brief Deallocates a State's vectors and matrices then destroys it
 * 
 * @param state pointer to the State to be destroyed
 */
void state_destroy(State* state);

/**
 * @brief Retrieves the number of distinct resources tracked by a state
 * 
 * @param state is a pointer to the State to query
 * @return int number of distinct resources (m)
 */
int state_resource_count(State* state);

/**
 * @brief Sets the maximum allocation of a process in a given State
 * 
 * @param state is a pointer to State to set
 * @param process is the identifier for some process to set
 * @param resource_list is an array of all resources the process may request
 * @param resource_count the total number of resources the process may request
 */
void state_set_max(State* state, int process, int* resource_list, int resource_count);

/**
 * @brief Writes state information to stdout
 * 
 * @param state is a pointer to the State to print
 */
void state_print(State* state);

/**
 * @brief Requests for resources to be allocated to a process
 * 
 * @param state is a pointer to the State tracking the system
 * @param process is the identier of the requesting process
 * @param resources is an array containing counts of each resource being requested
 * @return int 0 if request denied, 1 if request granted
 */
int Request(State* state, int process, int* resources);

/**
 * @brief Clone of Request()
 */
int Request2(State* state, int process, int* resources);

/**
 * @brief Releases resources allocated to a process
 * 
 * @param state is a pointer to the State tracking the system
 * @param process is the identifier of the releasing process
 * @param resources is an array counting how many of each resource to release
 */
void Release(State* state, int process, int* resources);