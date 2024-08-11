#include <stdio.h>  /* input/output */
#include <stdlib.h> /* standard utilities */
#include <time.h>   /* time utilities */
#include <unistd.h> /* sleep functionality */

/* CLOCK_REALTIME is supposed to already be defined in time.h, but VS Code was
 * complaining about it.  I believe it's because VS Code doesn't know I'm
 * compiling with the gnu99 standard. */
#define CLOCK_REALTIME 0

int check_email(char *address) {
  /* Generate a random server latency between 1 and 3 seconds: */
  int random_server_latency = (rand() % 3) + 1;
  /* Generate a random unread mail count between 1 and 5: */
  int random_unread_count = (rand() % 5) + 1;

  /* Sleep for the generated server latency to simulate waiting for a server
   * response: */
  sleep(random_server_latency);

  /* Print the results: */
  printf("%s: %d unread emails (%d seconds)\n", address, random_unread_count,
         random_server_latency);

  return (random_server_latency);
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

  /* Call check_email three times with different email addresses, accumulating
   * the total server latency in total_cycles: */
  total_cycles += check_email("john.doe@gmail.com");
  total_cycles += check_email("john.doe@outlook.com");
  total_cycles += check_email("john.doe@aol.com");

  /* Get the end time: */
  clock_gettime(CLOCK_REALTIME, &end);

  /* Calculate the elapsed time in seconds: */
  elapsed.tv_sec = end.tv_sec - start.tv_sec;

  /* Print a summary of the results: */
  printf("\nTotal process time:  %d seconds\n", total_cycles);
  printf("Actual elapsed time: %ld seconds\n", elapsed.tv_sec);

  return (0);
}