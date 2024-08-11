#include <pthread.h> /* POSIX threads library (for asynchronous thread management) */
#include <stdio.h>  /* input/output */
#include <stdlib.h> /* standard utilities */
#include <time.h>   /* time utilities */
#include <unistd.h> /* sleep functionality */

/* CLOCK_REALTIME is supposed to already be defined in time.h, but VS Code was
 * complaining about it.  I believe it's because VS Code doesn't know I'm
 * compiling with the gnu99 standard. */
#define CLOCK_REALTIME 0

/* This structure holds the email address and a pointer to an integer that
 * tracks the total cycles (time spent): */
typedef struct {
  char *address;
  int *total_cycles;
} EmailCheckArgs;

void *check_email(void *args) {
  /* Generate a random server latency between 1 and 3 seconds: */
  int random_server_latency = (rand() % 3) + 1;
  /* Generate a random unread mail count between 1 and 5: */
  int random_unread_count = (rand() % 5) + 1;

  /* Sleep for the generated server latency to simulate waiting for a server
   * response: */
  sleep(random_server_latency);

  /* Cast the function args to an instance of the EmailCheckArgs structure: */
  EmailCheckArgs *emailArgs = (EmailCheckArgs *)args;

  /* Print the results: */
  printf("%s: %d unread email(s) (%d second(s))\n", emailArgs->address,
         random_unread_count, random_server_latency);

  /* Add the server latency for this check to the total_cycles in the
   * EmailCheckArgs structure: */
  (*(emailArgs->total_cycles)) += random_server_latency;

  return NULL;
}

int main() {
  /* Seed the random number generator with the current time, ensuring different
   * random values on each run: */
  srand(time(NULL));

  /* Variables to store start, end, and elapsed times: */
  struct timespec start, end, elapsed;

  /* Get the start time: */
  clock_gettime(CLOCK_REALTIME, &start);

  /* Initialize total_cycles. We'll use this to track our total process time: */
  int total_cycles = 0;

  /* Create an array of pthread_t objects to hold thread identifiers: */
  pthread_t threads[3];

  /* Create an array of EmailCheckArgs to hold the arguments for each thread: */
  EmailCheckArgs emailArgs[3];

  /* Assign each email address to the corresponding EmailCheckArgs structure,
   * with all of them pointing to the same total_cycles variable: */
  {
    emailArgs[0].address = "john.doe@gmail.com";
    emailArgs[0].total_cycles = &total_cycles;

    emailArgs[1].address = "john.doe@outlook.com";
    emailArgs[1].total_cycles = &total_cycles;

    emailArgs[2].address = "john.doe@aol.com";
    emailArgs[2].total_cycles = &total_cycles;
  }

  /* Create three threads using pthread_create, each executing the check_email
   * function with the corresponding arguments: */
  pthread_create(&threads[0], NULL, check_email, &emailArgs[0]);
  pthread_create(&threads[1], NULL, check_email, &emailArgs[1]);
  pthread_create(&threads[2], NULL, check_email, &emailArgs[2]);

  /* Main thread waits for all created threads to finish using pthread_join: */
  pthread_join(threads[0], NULL);
  pthread_join(threads[1], NULL);
  pthread_join(threads[2], NULL);

  /* Get the end time: */
  clock_gettime(CLOCK_REALTIME, &end);

  /* Calculate the elapsed time in seconds: */
  elapsed.tv_sec = end.tv_sec - start.tv_sec;

  /* Print a summary of the results: */
  printf("\nTotal process time:  %d seconds\n", total_cycles);
  printf("Actual elapsed time: %ld seconds\n", elapsed.tv_sec);

  return (0);
}
