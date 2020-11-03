#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


// The sum computed by the background thread
uint64_t sum = 0;

// Thread function to generate sum of 0 to N
void* sum_runner(void* arg) {
  uint64_t *limit_ptr = (uint64_t *) arg;
  uint64_t limit = *limit_ptr;
  free(arg);

  for (uint64_t i = 0; i <= limit; i++) {
    sum += i;
  }

  // Pass back data in dynamically allocated memory
  uint64_t *answer = malloc(sizeof(*answer));
  *answer = sum;
  pthread_exit(0);
}

int main(int argc, char **argv) {
  if(argc < 2) {
    printf("Usage: %s <num>\n", argv[0]);
    exit(-1);
  }

  uint64_t *limit = malloc(sizeof(*limit));
  *limit = atoll(argv[1]);

  // Thread ID
  pthread_t tid;

  // Create attributes
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  
  pthread_create(&tid, &attr, sum_runner, &limit);

  // Wait until thread is done its work
  uint64_t *result;

  pthread_join(tid, (void**)&result);
  printf("Sum is %lld\n", sum);
  free(result);
}