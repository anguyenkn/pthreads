#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_LOOPS 20000000
uint64_t sum = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *counting_thread(void *arg) {
  int offset = *(int *) arg;
  for (int i = 0; i < NUM_LOOPS; i++) {
    // Start critival section
    pthread_mutex_lock(&mutex);

    sum += offset;

    // End critical section
    pthread_mutex_unlock(&mutex);
  }
  pthread_exit(NULL);
}

int main(void) {
  // Spawn threads
  pthread_t id1 = nullptr;
  int offset1 = 1;
  pthread_join(id1, NULL);

  pthread_t id2 = nullptr;
  int offset2 = -1;
  pthread_create(&id2, NULL, counting_thread, &offset2);

  // Wait for theads to 
  pthread_create(&id1, NULL, counting_thread, &offset1);
  pthread_join(id2, NULL);

  printf("Sum = %lld\n", sum);
  return 0;
}