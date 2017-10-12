
#include <getopt.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <algorithm>
#include <pwd.h>
#include <grp.h>

using namespace std;

void mkdir(bool m, bool p,string argv, mode_t mode);
void pmkdir(string argv, mode_t mode);

int main(int argc, char * argv[]) {
  setvbuf(stdout,NULL,_IONBF,BUFSIZ);                     //Empties the buffer
  int opt= 0;
  bool p = false;							                            // option p (intermediate directories)
  bool m = false;							                            // option m (mode)
  mode_t mode = 0755;
  while ((opt = getopt(argc, argv, "p:m:")) != -1){
    switch (opt) {
    case 'p' :                                            //Argument for creading intermediate directories
      p = true;
      optind--;
      break;
    case 'm' :                                            //Specifies mode
      m = true;
      optind--;
      mode = strtol(argv[optind], NULL, 8);
      optind++;
      break;
    case '?':
      break;
    }
  }
  for(int i = optind; i < argc; i++){                     //Creates as many directories as needed (specified by arguments)
    string temp = argv[i];
    mkdir(m, p, temp, mode);
  }  
  return EXIT_SUCCESS;
} // main

    /******************************************
   mkdir - makes a directory if argument is specified
    Author: Stephen Kim and Zhenyu Yan
    Date: 4/11/2017
    Params: m =     mode
            p =     intermediate directories
            argv =  the current argument
            mode = the mode of the dir
  *******************************************/

void mkdir(bool m, bool p, string argv, mode_t mode){
  if(m && p){
    pmkdir(argv,mode);                                    //Makes a directory is mode and intermediate directories have been specified
  }else if(p){
    pmkdir(argv,mode);                                    //Makes a directory is mode and intermediate directories have been specified
  }else if(m){
    if((mkdir(argv.c_str(),mode)) == -1){               
      printf("mkdir:can not create directory ");          //Returns an error if a directory was unable to be made
      perror(argv.c_str());
    }
  }else{
    if((mkdir(argv.c_str(),mode)) == -1){
      printf("mkdir:can not create directory ");          //Returns an error if a directory was unable to be made
      perror(argv.c_str());
    }
  }
}

    /******************************************
   pmkdir - creates intermediate directories as needed
    Author: Stephen Kim and Zhenyu Yan
    Date: 4/11/2017
    Params: argv =  the current argument
            mode = the mode of the dir
  *******************************************/

void pmkdir(string argv, mode_t mode){
  char *temp = strdup(argv.c_str());
  char *pos = temp;

  if (strncmp(temp, "/", 1) == 0) {                       //Recursively creates directories as needed
    pos += 1;
  } else if (strncmp(temp, "./", 2) == 0) {
    pos += 2;
  }
  for ( ; *pos != '\0'; ++ pos) {
    if (*pos == '/') {
      *pos = '\0';
      mkdir(temp, 0755);
      *pos = '/';
    }
    mkdir(temp, mode);
  }
  free(temp);
}
