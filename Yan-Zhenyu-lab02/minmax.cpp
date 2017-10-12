
#include<iostream>
#include<string>
#include<sstream>
#include<cstdlib>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::stringstream;
using std::getline;


//-------------------------------------------------------------------
//this function gets min
//-------------------------------------------------------------------
//@param: input which is a string of number and use space to seperate
//@return: min
//-------------------------------------------------------------------
int min(string input){
  stringstream stream(input);
  int number = 0;
  int min = 0;
  stream >> min;
  while(stream >> number){
    min = (number < min) ? number : min;
  }
  return min;
}
//-------------------------------------------------------------------
//this function gets max
//-------------------------------------------------------------------
//@param: input which is a string of number and use space to seperate
//@return: max
//-------------------------------------------------------------------
int max(string input){
  stringstream stream(input);
  int number = 0;
  int max = 0;
  stream >> max;
  while(stream >> number){
    max = (number > max) ? number : max;
  }
  return max;
}

//-------------------------------------------------------------------
//main function
//-------------------------------------------------------------------
int main(){
  string input;
  cout << "Enter integers: ";
  getline(cin,input);
  cout << "Min: " << min(input) << endl;
  cout << "max: " << max(input) << endl;
  return EXIT_SUCCESS;
}
