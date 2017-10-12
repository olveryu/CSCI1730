
#include <cstdlib>
#include <string>

using std::string;

int main(int argc, char * argv[]) {
  setvbuf(stdout,NULL,_IONBF,BUFSIZ);                     //Empty Buffer
  if (argc > 2) {				                                  //returns error if user prints more than 2 arguments
    fprintf(stderr, "Usage: %s [+format]\n", argv[0]);
    exit(EXIT_FAILURE);			      		                    // exit
  }
  time_t rawtime;                                         //Gives the raw time
  struct tm * timeinfo;
  char buffer [80];
  
  time (&rawtime);                                        //Returns time
  timeinfo = localtime (&rawtime);
  
  
  if(argc == 1){                                          //If there is only one argument, print out the default
    strftime (buffer,80,"%a %b %d %X %Z %G",timeinfo);

  puts (buffer);                                          
  }else{
    string temp = argv[1];
    if(temp.at(0) != '+'){                                //Checks if and where the user inputs a "+" operator
      printf("date: invalid date %s\n", argv[1]);         //Exits and fails if user attempts to type in a condition without the +
      exit(EXIT_FAILURE);		       		// exit
    }
    temp = temp.substr(1);
    strftime (buffer,80,temp.c_str(),timeinfo);
    puts (buffer);
  }
}
