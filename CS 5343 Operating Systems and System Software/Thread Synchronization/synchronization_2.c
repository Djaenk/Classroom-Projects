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

  pthread_mutex_lock(game->mutex); // Begin critical section: Take slot
  for (k = 0; game->scores[k] != -1; k++);
  game->scores[k] = 0;
  data->slot = k;
  pthread_mutex_unlock(game->mutex); // End critical section

  // Wait for start signal
  while(game->active == 0);

  // Play until the game is over or until player scores reaches 100 or more
  while (game->active == 1 && game->scores[k] < 100) {
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

  // Signal that player has left
  printf("===== %s (thread %d) is leaving with a score of %d =====\n\n", data->name, k, game->scores[k]);
  game->scores[k] = -2;
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
  int player_index, num;

  // Create all threads and assign first N players to their threads
  printf("Number of threads : %d   |   Number of players: %d\n\n", N, p);
  for (int i = 0; i < N; ++i) {
    currently_playing[i].game = &game;
    currently_playing[i].name = players[i];
    printf("Thread %d started\n", i);
    pthread_create(threads + i, NULL, player, (void*)(currently_playing + i));
  }
  player_index = N;

  // Wait until initial players have taken their slots before starting game
  while (!game.active) {
    for (int i = 0; i < N; ++i) {
      i = game.scores[i] < 0 ? -1 : i;
    }
    game.active = 1;
  }

  // Generate numbers indefinitely
  while (game.active < 2) {
    pthread_mutex_lock(game.mutex); // Begin critical section: Dealer push
    if (queue_size(game.queue) <= N) {
      num = (rand() % 40) + 1;
      printf("Dealer is pushing %d to the queue.\n", num);
      queue_push(game.queue, num);
      queue_print(game.queue);
    }
    pthread_mutex_unlock(game.mutex); // End critical section

    // Check if any player has left
    for (int i = 0; i < N; ++i) {
      if (game.scores[currently_playing[i].slot] == -2) {
        // Terminate player's thread
        pthread_join(threads[i], NULL);

        // Check if there are more players waiting
        if (player_index < p) {
          // Create a thread for the next player
          game.scores[currently_playing[i].slot] = -1;
          currently_playing[i].name = players[player_index++];
          pthread_create(threads + i, NULL, player, (void*)(currently_playing + i));
        }
        else {
          // End the game if there are no more players waiting
          game.active = 2;
        }
      }
    }
  }

  // Terminate all threads
  for (int i = 0; i < N; ++i) {
    pthread_join(threads[i], NULL);
  }

  game_exit(&game);
  return 0;
}