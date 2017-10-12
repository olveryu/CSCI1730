
#include <unistd.h>
#include <cstdlib>
#include <iostream>

using std::cout;
using std::endl;

int main(const int argc, const char * argv[], const char * envp[]){
  for(int i = 0; envp[i] != nullptr; i++){								//Loops through each envp pointer until a null pointer is reached
    cout << envp[i] << endl;											//Prints out the values at each i index
  }
  return EXIT_SUCCESS;
}
