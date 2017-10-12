 
#include <getopt.h>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>


using namespace std;
void head(bool n, char * argv, int line);

int main(int argc, char * argv[]) {
    if (argc < 2) {				                                           // check user argc number
    fprintf(stderr, "Usage: %s (-option) <pathname>\n", argv[0]);
    exit(EXIT_FAILURE);						                                   // exit
  }
  setvbuf(stdout,NULL,_IONBF,BUFSIZ);
  cout.setf(std::ios_base::unitbuf);
  int opt= 0;
  bool n = false;							                                       // option n
  int line = 10;
  while ((opt = getopt(argc, argv, "n:")) != -1){
    switch (opt) {
    case 'n' : 
      n = true;
      optind--;
      line = atoi(argv[optind]);
      optind++;
      break;
    case '?':
      break;
    }
  }
  for(int i = optind; i < argc; i++){
    head(n,argv[i],line);
  }
  return EXIT_SUCCESS;
}                                                                   // main

    /******************************************
   head - gets and prints out the number of lines from the top of the file
    Author: Stephen Kim and Zhenyu Yan
    Date: 4/11/2017
    Parameters: n = boolean to check if user inputs a specific number
                argv = current file argument
                line = number of lines
  *******************************************/

void head(bool n, char * argv, int line){
  FILE * file;
  if((file = fopen(argv,"r")) == nullptr){
    printf("can not find :%s\n",argv);
  }else{
    setvbuf(file,NULL,_IONBF,BUFSIZ);
    int checkLine = 0;
    for(int ch = 0;(ch = getc(file)) != -1;){
      cout << (char)ch;
      if(ch =='\n'){
	checkLine++;
	if(checkLine == line){
	  break;
	}
      }
    }
    fclose(file);
  }
}
