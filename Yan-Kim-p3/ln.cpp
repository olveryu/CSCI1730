
#include <getopt.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <unistd.h>


using namespace std;

void linkFile(bool s, const char * file1 , const char * file2);

int main(int argc, char * argv[]) {
  setvbuf(stdout,NULL,_IONBF,BUFSIZ);
  if (argc < 3 || argc > 4) {				                                                      // check user argc number
    fprintf(stderr, "Usage: %s (-option) <pathname> <pathname>\n", argv[0]);
    exit(EXIT_FAILURE);						                                                        // exit
  }

  int opt= 0;
  bool s = false;						                                                             	// option a
  char * file1;
  char * file2;
  while ((opt = getopt(argc, argv, "s:")) != -1){
    switch (opt) {
    case 's' : 
      s = true;
      optind--;
      file1 = argv[optind];
      optind++;
      break;
    case '?':
      break;
    }
  }
  if(!s){
    file1 = argv[optind];
    optind++;

  }
  file2 = argv[optind];
  linkFile(s,file1,file2);
  return EXIT_SUCCESS;
} // main


    /******************************************
   linkFile - creates a symbolic/hardlink to the specified file
    Author: Stephen Kim and Zhenyu Yan
    Date: 4/11/2017
    Params: s = boolean to check if a symbolic link has been specified
            file1 = file to be linked
            file2 = file to be linked to
  *******************************************/

void linkFile(bool s, const char *  file1, const char * file2){
  if(s){
    if(symlink(file1, file2) != 0) perror("symlink");                                     //symbolic link
  }else{
    if(link(file1, file2) != 0) perror("link");                                           //hard link
  }
}
