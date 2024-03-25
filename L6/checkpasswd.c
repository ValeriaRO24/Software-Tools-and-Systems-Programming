#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXLINE 256
#define MAX_PASSWORD 10

#define SUCCESS "Password verified\n"
#define INVALID "Invalid password\n"
#define NO_USER "No such user\n"

int main(void) {
  char user_id[MAXLINE];
  char password[MAXLINE];

  if(fgets(user_id, MAXLINE, stdin) == NULL) {
      perror("fgets");
      exit(1);
  }
  if(fgets(password, MAXLINE, stdin) == NULL) {
      perror("fgets");
      exit(1);
  }
  int val[2];
  if(pipe(val)== -1){
    perror("Pipe");
    exit(1);
  }

  //forking
  pid_t pid = fork();
  if(pid > 0){
    //parent
    close(val[0]);
    if(write(val[1], user_id, MAX_PASSWORD) != MAX_PASSWORD){
      perror("write");
      exit(1);
    }
    if(write(val[1], password, MAX_PASSWORD) != MAX_PASSWORD){
      perror("write");
      exit(1);
    }
    close(val[1]);

    int wstat;
    if(wait(&wstat) == -1){
      perror("waitpid");
      exit(1);
    }

    if(!WIFEXITED(wstat)){
      return -1;
    }

    int exitstat = WEXITSTATUS(wstat);
    if(exitstat == 0){
      printf(SUCCESS);
    } else if(exitstat == 2){
      printf(INVALID);
    } else if(exitstat == 3){
      printf(NO_USER);
    }
    return 0;


  } else if(pid == 0){
    //child
    close(val[1]);
    dup2(val[0], STDIN_FILENO);
    close(val[0]);
    execlp("./validate", "validate", (char*) NULL);
    fprintf(stderr, "calling exec failed\n");
    return 1;

  } else{
    perror("fork");
    return 1;
  }

  return 0;
}
