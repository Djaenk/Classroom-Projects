#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include "queue.h"

#define MS_TO_NS 1000000

/**
 * @brief Game structure maintains resources to handle a single game
 */
typedef struct Game {
  Queue* queue;

  /**
   * N stores the total possible number of players in the game
   * held stores the count of numbers held by sleeping players
   * active is a boolean signaling if the game is active
   * scores is an array containing the score of each player
   */
  int N, held, active, *scores;

  /** mutex to limit game resource access to one player or dealer at a time */
  pthread_mutex_t* mutex;
} Game;

/**
 * @brief Initializes a Game struct and allocates necessary memory
 * @param g is a pointer to the Game to initialize
 * @param N is the number of players the game
 */
void game_init(Game* g, int N) {
  g->queue = queue_create(2 * N + 1);
  g->N = N;
  g->held = 0;
  g->active = 0;
  g->scores = (int*)malloc(N * sizeof(int));
  for (int i = 0; i < N; ++i) {
    g->scores[i] = -1;
  }
  g->mutex = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
  pthread_mutex_init(g->mutex, NULL);
}

/**
 * @brief Uninitializes a Game and deallocates its contents
 * @param g is a pointer to the Game to exit
 */
void game_exit(Game* g) {
  queue_destroy(g->queue);
  pthread_mutex_destroy(g->mutex);
  free(g->mutex);
}

/**
 * @brief Player function to be run in a thread
 * @param param is the void pointer passed to the thread
 */
void* player(void* param) {
  Game* game = (Game*)param;
  int N = game->N;
  int k;
  struct timespec request = {1, 0};
  int x;
  int points;
  int value;

  pthread_mutex_lock(game->mutex); // Begin critical section: Take seat
  for (k = 0; game->scores[k] >= 0; k++);
  game->scores[k]++;
  pthread_mutex_unlock(game->mutex); // End critical section

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

  pthread_exit(NULL);
}

/**
 * @brief Main function, also serves as the dealer for the game
 */
int main(int argc, char* argv[]){
  int N, T;
  if (argc > 2) {
    N = atoi(argv[1]);
    T = atoi(argv[2]);
  }
  else {
    return -1;
  }

  Game game;
  game_init(&game, N);
  pthread_t threads[N];
  int num;

  printf("Number of threads : %d   |   Number of objects: %d\n\n", N, T);
  for (int i = 0; i < N; ++i) {
    printf("Thread %d started\n", i);
    pthread_create(threads + i, NULL, player, (void*)&game);
  }

  game.active = 1;

  for (int i = 0; i < T;) {
    pthread_mutex_lock(game.mutex); // Begin critical section: Dealer push
    if (queue_size(game.queue) <= N) {
      num = (rand() % 40) + 1;
      printf("Dealer is pushing %d to the queue.\n", num);
      queue_push(game.queue, num);
      queue_print(game.queue);
      ++i;
    }
    pthread_mutex_unlock(game.mutex); // End critical section
  }

  while (game.active) {
    pthread_mutex_lock(game.mutex); // Begin critical section: Count numbers
    game.active = game.held + queue_size(game.queue);
    pthread_mutex_unlock(game.mutex); // End critical section
  }

  for (int i = 0; i < N; ++i) {
    pthread_join(threads[i], NULL);
    printf("Final score for player %d : %d\n", i, game.scores[i]);
  }

  game_exit(&game);
  return 0;
}