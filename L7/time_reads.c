#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <signal.h>
#include <sys/time.h>


// Message to print in the signal handling function. 
#define MESSAGE "%ld reads were done in %ld seconds.\n"


/* Global variables to store number of read operations and seconds elapsed.
 * These have to be global so that signal handler to be written will have
 * access.
 */
long num_reads = 0, seconds;
void timeout(int signal){
  printf(MESSAGE, num_reads, seconds);
  exit(0);
}


int main(int argc, char ** argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: time_reads s filename\n");
        exit(1);
    }
    seconds = strtol(argv[1], NULL, 10);

    FILE *fp;
    if ((fp = fopen(argv[2], "r+")) == NULL) {    // Read+Write for later ...
      perror("fopen");
      exit(1);
    }

    struct sigaction sa;
    sa.sa_handler = timeout;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGPROF, &sa, NULL);

    struct itimerval value;
    value.it_interval.tv_sec = 0;
    value.it_interval.tv_usec = 0;
    value.it_value.tv_sec = 0;
    value.it_value.tv_usec = 0;
    setitimer(ITIMER_PROF, &value, NULL);

    sigset_t sigset;
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGPROF);

    int buf;

    /* In an infinite loop, read an int from a random location in the file
     * and print it to stderr.
     */
    for (;;) {
      int rnd = (random() % 10);
      if(sigprocmask(SIG_BLOCK, &sigset, NULL) == -1){
        perror("sigprocmask");
      }
      printf("run for %ld seconds look at %d\n", seconds, rnd);
      if(sigprocmask(SIG_UNBLOCK, &sigset, NULL) == -1){
        perror("sigprocmask");
      }
      if(fseek(fp, rnd * sizeof(int), SEEK_SET) != 0){
        perror("seek");
        exit(1);
      }
      if(fread(&buf, sizeof(int), 1, fp) <= 0){
        perror("fread");
        exit(1);
      }
      num_reads++;

    }

    return 1;  //something is wrong if we ever get here!
}

