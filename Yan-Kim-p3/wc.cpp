
#include <getopt.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <clocale>
#include <cwchar>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


using namespace std;

void standardInput(bool c, bool l, bool m, bool w);
void wordCount(bool c, bool l, bool m, bool w, const char * argv);
int characterCount(const char * argv);

int main(int argc, char * argv[]) {
  setvbuf(stdout,NULL,_IONBF,BUFSIZ);
  cout.setf(std::ios_base::unitbuf);
  int opt= 0;
  bool c = false;							                              // option c (byte)
  bool l = false;						                               	// option l (line)
  bool m = false;						                               	// option m (character)
  bool w = false;						                               	// option w (word)
  while ((opt = getopt(argc, argv, "clmw")) != -1){         //Checks to see what arguments user inputs
    switch (opt) {
    case 'c' :
      c = true;
      break;
    case 'l' : 
      l = true;
      break;
    case 'm' : 
      m = true;
      break;
    case 'w' : 
      w = true;
      break;
    case '?':
      break;
    }
  }
  
  if(optind == argc){                                            
    standardInput(c,l,m,w);
  }
  for(int i = optind; i < argc ; i++){
    if(strcmp(argv[i],"-")){
      standardInput(c,l,m,w);
    }else{
      wordCount(c,l,m,w,argv[i]);
    }
  }
    
  return EXIT_SUCCESS;
} // main

    /******************************************
  standardInput - sets the default output
    Author: Stephen Kim and Zhenyu Yan
    Date: 4/11/2017
    Params: c = bytes
            l = lines
            m = characters
            w = words
  *******************************************/

void standardInput(bool c, bool l, bool m, bool w){
  int fd;
  int n;
  const int BUFF_SIZE = 1024;
  char buffer[BUFF_SIZE];
  fd = creat(" ", 0644);
  while((n = read(STDIN_FILENO,buffer,BUFF_SIZE))>0){                   //Reads and writes to standard output
    write(fd, buffer, n);
  }
  wordCount(c,l,m,w," ");
  unlink(" ");            
}

    /******************************************
   wordCount - counts the total amount of words in a file
    Author: Stephen Kim and Zhenyu Yan
    Date: 4/11/2017
    Params: argv = Pointer to the array of arguments
            c = bytes
            l = lines
            m = characters
            w = words
  *******************************************/

void wordCount(bool c, bool l, bool m, bool w, const char * argv){
  //order is lwmc
  setlocale(LC_ALL, "en_US.utf8");
  int byte = 0;
  int line = 0;
  int characters = 0;
  int word = 0;
  const char * fileName = argv;
  FILE * file;
  if((file = fopen(argv,"r")) == nullptr){                                //Returns an error if file was unable to be found
    printf("can not find :%s\n",argv);
  }else{
    setvbuf(file,NULL,_IONBF,BUFSIZ);
    for(int ch = 0;(ch = getc(file)) != -1; byte++){
      if(ch =='\n'){
	line++;
      }
      if(ch == ' '||ch == '\t' || ch == '\n'){
	word++;
      }
    }
    characters = characterCount(argv);
    if(c && l && m && w){                                                   //Lists out all possible combinations of what the user could type in
      printf("%d %d %d %d %s\n",line,word,characters,byte,fileName);
    }else if(c && l && m){
      printf("%d %d %d\n %s",line,characters,byte,fileName);
    }else if(c && l && w){
      printf("%d %d %d %s\n",line,word,byte,fileName);
    }else if(c && m && w){
      printf("%d %d %d %s\n",word,characters,byte,fileName);
    }else if(l && m && w){
      printf("%d %d %d %s\n",line,word,characters,fileName);
    }else if(c && l){
      printf("%d %d %s\n",line,byte,fileName);
    }else if(c && m){
      printf("%d %d %s\n",characters,byte,fileName);
    }else if(c && w){
      printf("%d %d %s\n",word,byte,fileName);
    }else if(l && m){
      printf("%d %d %s\n",line,characters,fileName);
    }else if(l && w){
      printf("%d %d %s\n",line,word,fileName);
    }else if(m && w){
      printf("%d %d%s\n",word,characters,fileName);
    }else if(c){
      printf("%d %s\n",byte,fileName);
    }else if(l){
      printf("%d %s\n",line,fileName);
    }else if(m){
      printf("%d %s\n",characters,fileName);
    }else if(w){
      printf("%d %s\n",word,fileName);
    }else{
      printf("%d %d %d %s\n",line,word,byte,fileName);
    }
    fclose(file);
  }
}

    /******************************************
   characterCount - counts the total amount of characters in a file
    Author: Stephen Kim and Zhenyu Yan
    Date: 4/11/2017
    Params: argv = Pointer to the array of arguments
  *******************************************/

int characterCount(const char * argv){                                      //Opens the file for reading
  FILE * file = fopen(argv, "r");
  setvbuf(file,NULL,_IONBF,BUFSIZ);
  string temp = "";
  int ch;
  int characterCount = 0;
  while((ch = getc(file)) != -1){                                           //Counts how many times a character is found
    temp += ch;
  }
  const char * ptr = temp.c_str();
  mbstate_t state = mbstate_t(); 
  const char * end = ptr + strlen(ptr);
  int len;
  wchar_t wc;
  while((len = mbrtowc(&wc, ptr, end-ptr, &state)) > 0){
    ptr += len;
    characterCount ++;
  }
  return characterCount;                                                    //Returns characterCount
}
