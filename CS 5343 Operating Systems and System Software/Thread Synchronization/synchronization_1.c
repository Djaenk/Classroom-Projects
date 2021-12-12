#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <string.h>
#include "numbergame.h"
#include "queue.h"

#define MS_TO_NS 1000000

typedef struct PlayerData {
  Game* game;
  char* name;
  int slot;
} PlayerData;

/**
 * @brief Player function to be run in a thread
 * @param param is the void pointer passed to the thread
 */
void* player(void* param) {
  PlayerData* data = (PlayerData*)param;
  Game* game = data->game;
  int N = game->N;
  int k;
  struct timespec request = {1, 0};
  int x;
  int points;
  int value;

  start:

  pthread_mutex_lock(game->mutex); // Begin critical section: Take slot
  for (k = 0; game->scores[k] != -1; k++);
  game->scores[k] = 0;
  data->slot = k;
  pthread_mutex_unlock(game->mutex); // End critical section

  // Wait for start signal
  while(!game->active);

  while (game->active) {
    pthread_mutex_lock(game->mutex); // Begin critical section: Player pop
    if (queue_size(game->queue)) {
      ++game->held;
      x = queue_pop(game->queue);
      printf("Thread %d popped %d from the queue. ", k, x);
      if (x <= N) {
        printf("Player has scored. Thread %d does not need to push.\n", k);
        points = x;
        value = -1;
      }
      else if ((x % N == k) || (x % N == (k + 1) % N)) {
        printf("Player has scored. Thread %d needs to push 3 * x / 5.\n", k);
        points = 2 * x / 5;
        value = x - points;
      }
      else {
        printf("Player did not score. Thread %d needs to push x - 2.\n", k);
        points = 0;
        value = x - 2;
      }
      queue_print(game->queue);
      pthread_mutex_unlock(game->mutex); // End critical section

      request.tv_nsec = x * MS_TO_NS; 
      nanosleep(&request, NULL);

      pthread_mutex_lock(game->mutex); // Begin critical section: Player push
      game->scores[k] += points;
      if (value > -1) {
        printf("Thread %d pushing %d to the queue\n", k, value);
        queue_push(game->queue, value);
        queue_print(game->queue);
      }
      --game->held;
      pthread_mutex_unlock(game->mutex); // End critical section
    }
    else {
      pthread_mutex_unlock(game->mutex); // End critical section
    }
  }

  // Wait for scores to be reset
  while(game->scores[k] > -1);

  // If player did not win then take new slot, else terminate thread
  if (game->scores[k] == -1) {
    goto start;
  }
  pthread_exit(NULL);
}

/**
 * @brief Main function, also serves as the dealer for the game
 */
int main(int argc, char* argv[]){
  int N, T, p;
  char** players;

  // Create a list of all players
  if (argc > 1) {
    char line[22];
    char* token;
    int length;

    FILE* file = fopen(argv[1], "r");
    fgets(line, 21, file);
    token = strtok(line, " ");
    N = atoi(token);
    token = strtok(NULL, " ");
    T = atoi(token);
    token = strtok(NULL, " ");
    p = atoi(token);

    players = (char**)malloc(p * sizeof(char*));
    for (int i = 0; i < p; ++i) {
      fgets(line, 21, file);
      length = strlen(line);
      line[length - 1] = '\0';
      players[i] = (char*)malloc(length * sizeof(char));
      strcpy(players[i], line);
    }

    fclose(file);
  }
  else {
    return -1;
  }

  srand(time(NULL));
  Game game;
  game_init(&game, N);
  pthread_t threads[N];
  PlayerData currently_playing[N];

  // Create all threads and assign first N players to their threads
  printf("Number of threads : %d   |   Number of objects: %d\n\n", N, T);
  for (int i = 0; i < N; ++i) {
    currently_playing[i].game = &game;
    currently_playing[i].name = players[i];
    printf("Thread %d started\n", i);
    pthread_create(threads + i, NULL, player, (void*)(currently_playing + i));
  }

  // Loop until no players remain in the list
  for (int i = N; i < p; ++i) {
    // Print players in this game
    printf("\nGame %d players: ", i);
    for (int j = 0; j < N; ++j) {
      printf("%s, ", currently_playing[j].name);
    }
    printf("\n");

    // Start and deal a full game
    game_play(&game, T);

    // Determine the slot of the winning player
    int winner_slot = 0;
    for (int j = 0; j < N; ++j) {
      winner_slot = game.scores[j] > game.scores[winner_slot] ? j : winner_slot;
    }

    // Determine the name of the winning player and which thread they were
    char* name, *winner_name;
    int score;
    int winner_thread;
    for (int j = 0; j < N; ++j) {
      name = currently_playing[j].name;
      score = game.scores[currently_playing[j].slot];
      printf("%s scored %d points.\n", name, score);
      if (currently_playing[j].slot == winner_slot) {
        winner_name = name;
        winner_thread = j;
      }
    }
    printf("%s wins game %d.\n", winner_name, i - N);

    // Reset scores and reslot losing players
    for (int j = 0; j < N; ++j) {
      game.scores[j] = (winner_slot != j) - 2;
    }

    // Terminate thread of winning player and create thread for next player
    pthread_join(threads[winner_thread], NULL);
    currently_playing[winner_thread].name = players[i];
    game.scores[winner_slot] = -1;
    pthread_create(threads + winner_thread, NULL, player, (void*)(currently_playing + winner_thread));
  }

  // Print players in final game
  printf("\nGame %d players: ", p - N);
  for (int j = 0; j < N; ++j) {
    printf("%s, ", currently_playing[j].name);
  }
  printf("\n");

  // Play final game with last player and print result
  game_play(&game, T);
  int winner_slot = 0;
  for (int j = 0; j < N; ++j) {
    winner_slot = game.scores[j] > game.scores[winner_slot] ? j : winner_slot;
  }
  char* name, *winner_name;
  int score;
  int winner_thread;
  for (int j = 0; j < N; ++j) {
    name = currently_playing[j].name;
    score = game.scores[currently_playing[j].slot];
    printf("%s scored %d points.\n", name, score);
    if (currently_playing[j].slot == winner_slot) {
      winner_name = name;
      winner_thread = j;
    }
  }
  printf("%s wins game %d\n.", winner_name, p - N);

  // Terminate all threads
  for (int j = 0; j < N; ++j) {
    game.scores[j] = -2;
  }
  for (int i = 0; i < N; ++i) {
    pthread_join(threads[i], NULL);
  }

  game_exit(&game);
  return 0;
}