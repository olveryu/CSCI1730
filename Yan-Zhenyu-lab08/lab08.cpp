
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <cerrno>
#include <cstring>

using std::cout;
using std::endl;
using std::string;

int main(const int argc, const char * argv []){
  int n;							// declare n as the by it read
  const int BUFFER_SIZE = 1024;					// declare buffer size
  char buffer[BUFFER_SIZE];		       			// declare buffer as a array with a size of 1024

  if(argc == 1){						// if it does not include any name of file, it will do "-"
    while((n = read(STDIN_FILENO,buffer,BUFFER_SIZE))>0){
      write(STDOUT_FILENO,buffer,n);
    }
    cout << "(Hyphen finished)" << endl;			// print message if finished
  }

  for(int i = 1; i < argc; i++){				// read and write all the file
    int fd;							// declare fd as the file descriptor
    string fileName = argv[i];					// declare a str to check if the use input a "-"
 
    if(fileName == "-"){					// check "-"
      while((n = read(STDIN_FILENO,buffer,BUFFER_SIZE))>0){
	write(STDOUT_FILENO,buffer,n);
      }
      cout << "(Hyphen finished)" << endl;			// print message if finished
    }else if((fd = open(argv[i],O_RDONLY))>0){			// open the file and check if the file can be open or not
      while((n = read(fd,buffer,sizeof(buffer)))>0){		// check if read to the end of the file
	write(STDOUT_FILENO,buffer,n);
	cout << "(Open " << fileName << " "   			// print out when reading success
	     << strerror(errno) << ")"
	     << endl;
      }
      close(fd);						// close the file
    }else{
      cout << "(Could not open " << fileName << " "    		// print out the error
	   << strerror(errno) << ")"
	   << endl;
    }
  }
  return EXIT_SUCCESS;
} // main
