 
#include <getopt.h>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;

void tail(bool f, bool c, bool n, char * argv, int line, int byte);
void print(char * argv,int checkByte, int checkLine, bool n, bool c);

int main(int argc, char * argv[]) {
    if (argc < 2) {				  		                                           // check user argc number
    fprintf(stderr, "Usage: %s (-option) <pathname>\n", argv[0]);
    exit(EXIT_FAILURE);							                                       // exit
  }
  setvbuf(stdout,NULL,_IONBF,BUFSIZ);
  cout.setf(std::ios_base::unitbuf);
  int opt = 0;
  bool f = false;							                                             // option f
  bool c = false;							                                             // option c
  bool n = false;							                                             // option n
  int line = 10;
  int byte = 0;
  while ((opt = getopt(argc, argv, "f:c:n:")) != -1){
    switch (opt) {
    case 'f':
      f = true;
      optind--;
      break;
    case 'c' : 
      c = true;
      optind--;
      byte = atoi(argv[optind]);
      optind++;
      break;
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
    tail(f,c,n,argv[i],line,byte);
  }
  return EXIT_SUCCESS;
} // main

    /******************************************
   tail - gets and stores the information from the lines from the bottom of the file
    Author: Stephen Kim and Zhenyu Yan
    Date: 4/11/2017
    Parameters: f = boolean to continue FIFO
                c = boolean to choose location to copy relative to file in bytes
                n = number of lines
                argv = current file name
                line = number of lines
                byte = number of bytes
  *******************************************/

void tail(bool f, bool c, bool n, char * argv, int line, int byte){
  FILE * file;
  if((file = fopen(argv,"r")) == nullptr){
    printf("can not find :%s\n",argv);
  }else{
    setvbuf(file,NULL,_IONBF,BUFSIZ);
    int checkLine = 0;
    int checkByte = 0;
    for(int ch = 0;(ch = getc(file)) != -1;checkByte++){
      if(ch =='\n'){
	checkLine++;
      }
    }
    fclose(file);    
    checkByte -= byte;
    checkLine -= line;

    if(f){
      print(argv,checkByte,checkLine,n,c);
      int n;
      const int BUFF_SIZE = 1024;
      char buffer[BUFF_SIZE];
      int foption = open(argv,O_RDONLY);
      lseek(foption,0,SEEK_END);
      while((n = read(foption, buffer, BUFF_SIZE)) != -1){
	write(STDOUT_FILENO, buffer, n);
      }
    }else{
      print(argv,checkByte,checkLine,n,c);
    }
  }
}

    /******************************************
   print - prints out the number of lines from the bottom of the file
    Author: Stephen Kim and Zhenyu Yan
    Date: 4/11/2017
    Parameters: c = boolean to choose location to copy relative to file in bytes
                n = number of lines
                argv = current file name
                checkByte = checks the number of bytes of the File
                checkLine = tracks the number of lines to print
  *******************************************/

void print(char * argv,int checkByte, int checkLine, bool n, bool c){
  FILE * file;
  file = fopen(argv,"r");
  setvbuf(file,NULL,_IONBF,BUFSIZ);
  int lineCounter = 0;
  int byteCounter = 0;
  bool flag = true;
  for(int ch = 0;(ch = getc(file)) != -1;){
    if(n){
      if(ch =='\n'){
	lineCounter++;
      }
      if(lineCounter >= checkLine){
	if(flag){
	  flag = false;
	  continue;
	}
	cout << char(ch);
      }
    }else if(c){
      byteCounter++;
      if(byteCounter >= checkByte){
	if(flag){
	  flag = false;
	  continue;
	}
	cout << char(ch);
      }
    }else{
      if(ch =='\n'){
	lineCounter++;
      }
      if(lineCounter >= checkLine){
	if(flag){
	  flag = false;
	  continue;
	}
	cout << char(ch);
      }
    }
  }
  fclose(file);
}
