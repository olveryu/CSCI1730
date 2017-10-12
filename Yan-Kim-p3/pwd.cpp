
#include <unistd.h>
#include <stdio.h>
#include <cstdlib>


int main() {
  char cwd[1024];
  if (getcwd(cwd, sizeof(cwd)) != NULL){				//Gets the current working directory
    fprintf(stdout,"%s\n", cwd);						//Prints out the full path to the current working directory
  }else{
    perror("getcwd() error");							//Prints out error elsewise
  }
  return EXIT_SUCCESS;
}
