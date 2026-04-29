#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void lsh_loop(void){
  char *line;
  char **args;
  char status;
  do {
    printf("> ");
    line = lsh_read_line();
    args = lsh_split_line(line);
    status = lsh_execute(args);

    free(line);
    free(args);
  }while (status)
}

int main(int argc, char **argv){
  
  return EXIT_SUCCESS ;
}
