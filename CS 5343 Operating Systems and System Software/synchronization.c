#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>

#define MS_TO_NS 1000000

// Start of Queue data structure implementation

typedef struct Queue {
  // Queue is implemented using a circular buffer
  int* buffer;

  // capacity contains maximum number of elements storable in queue
  // empty is a boolean signaling if queue contains no elements
  // begin holds index of first element in queue
  // end holds index past last element in queue
  int capacity, empty, begin, end;
} Queue;

void queue_init(Queue* q, int size) {
  q->capacity = size;
  q->empty = 1;
  q->begin = 0;
  q->end = 0;
  q->buffer = (int*)malloc(size * sizeof(int));
}

void queue_destroy(Queue* q) {
  free(q->buffer);
}

void queue_push(Queue* q, int value) {
  q->buffer[q->end] = value;
  q->end = (q->end + 1) % q->capacity;
  q->empty = 0;
}

int queue_pop(Queue* q) {
  int retval = q->buffer[q->begin];
  q->begin = (q->begin + 1) % q->capacity;
  q->empty = q->begin == q->end;
  return retval;
}

void queue_print(Queue* q) {
  int end = q->end > q->begin || q->empty ? q->end : q->end + q->capacity;
  printf("\n( ");
  for (int i = q->begin; i < end; ++i) {
    printf("%d ", q->buffer[i % q->capacity]);
  }
  printf(")\n\n");
}

// End of Queue data structure implementation

// Start of Game implementation

typedef struct Game {
  Queue* queue;

  // N stores the total possible number of players in the game
  // held stores the count of numbers held by sleeping players
  // active is a boolean signaling if the game is active
  // scores is an array containing the score of each player
  int N, held, active, *scores;

  // mutex to limit queue access to one player at a time
  pthread_mutex_t* mutex;
} Game;

void game_init(Game* g, int N) {
  g->queue = (Queue*)malloc(sizeof(Queue));
  queue_init(g->queue, N + 1);
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

void game_destroy(Game* g) {
  queue_destroy(g->queue);
  pthread_mutex_destroy(g->mutex);
  free(g->mutex);
}

// End of Game implementation

void* player(void* param) {
  // preprocessing
  Game* game = (Game*)param;
  int N = game->N;
  int k;
  pthread_mutex_lock(game->mutex);
  for (k = 0; game->scores[k] >= 0; k++);
  game->scores[k]++;
  pthread_mutex_unlock(game->mutex);
  struct timespec request = {1, 0};
  int x;
  int points;
  int value;

  // wait for game start signal
  while(!game->active);

  // repeat until game ends
  while (game->active) {
    // acquire mutex before accessing queue
    pthread_mutex_lock(game->mutex);

    // check if queue is empty
    if (!game->queue->empty) {
      // get the next number
      game->held++;
      x = queue_pop(game->queue);
      printf("Thread %d popped %d from the queue. ", k, x);

      // release mutex after grabbing from queue
      pthread_mutex_unlock(game->mutex);

      // determine what value thread needs to push, if any
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

      // sleep for 1000 + x milliseconds
      request.tv_nsec = x * MS_TO_NS; 
      nanosleep(&request, NULL);

      // process scoring
      game->scores[k] += points;

      if (value > -1) {
        // acquire mutex to push value into queue
        pthread_mutex_lock(game->mutex);
        printf("Thread %d pushing %d to the queue\n", k, value);
        queue_push(game->queue, value);
        queue_print(game->queue);
      }
      game->held--;
    }
    // release mutex after completing queue interaction
    pthread_mutex_unlock(game->mutex);
  }

  pthread_exit(NULL);
}

int main(int argc, char* argv[]){
  if (argc > 2) {
    // preprocessing
    int N = atoi(argv[1]);
    int T = atoi(argv[2]);
    pthread_t threads[N];
    Game game;
    game_init(&game, N); // queue capacity is the same as the player count
    int num;
    printf("Number of threads : %d   |   Number of objects: %d\n\n", N, T);

    // create all threads
    for (int i = 0; i < N; ++i) {
      printf("Thread %d started\n", i);
      pthread_create(threads + i, NULL, player, (void*)&game);
    }

    // signal the game to start
    game.active = 1;

    // loop until T numbers have been generated
    for (int i = 0; i < T;) {
      // acquire mutex before accessing queue
      pthread_mutex_lock(game.mutex);

      // check if queue is full
      if (game.queue->begin != game.queue->end || game.queue->empty) {
        num = (rand() % 40) + 1;
        printf("Dealer is pushing %d to the queue.\n", num);
        queue_push(game.queue, num);
        queue_print(game.queue);
        ++i;
      }

      // release mutex after completing queue interaction
      pthread_mutex_unlock(game.mutex);
    }

    // signal end of game
    while (1) {
      pthread_mutex_lock(game.mutex);
      if (game.held == 0 && game.queue->empty) {
        break;
      }
      pthread_mutex_unlock(game.mutex);
    }
    pthread_mutex_unlock(game.mutex);
    game.active = 0;

    // wait for all threads to finish
    for (int i = 0; i < N; ++i) {
      pthread_join(threads[i], NULL);
    }

    // print final score for each player
    for (int i = 0; i < N; ++i) {
      printf("Final score for player %d : %d\n", i, game.scores[i]);
    }

    game_destroy(&game);
    return 0;
  }
  return -1;
}