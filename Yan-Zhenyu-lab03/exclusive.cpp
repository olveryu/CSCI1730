
#include<iostream>
#include<cstdlib>
#include<string>
#include<sstream>

using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::stringstream;

int exclusive(string input);
int compare(string input, int number);

/**
   main function
 */

int main(){
  string input;
  cout << "Enter integers: ";
  std::getline(cin,input);
  cout << "Exclusive: " << exclusive(input) << endl;
  return EXIT_SUCCESS;
}

/**
   get the exclusive number from a string

   @param: input which is a string a number seperate by space
   @return: exclusiveNumber
 */

int exclusive(string input){
  stringstream stream(input);
  int number = 0;
  int result = 0;
  while(stream >> number){
    result = result^number;   //check exclusive use xOR
  }
  return result;
}
