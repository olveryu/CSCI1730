
#include<iostream>
#include<cstdlib>
#include<stdio.h>

using std::cout;
using std::cin;
using std::endl;

//-------------------------------------------------------
//function to calculate how many hour
//-------------------------------------------------------
//@param: input which is second
//@return: hour
//-------------------------------------------------------
int hour(int input){
  return (input/3600);
}

//-------------------------------------------------------
//function to calculate how many minute left after convert
//to hour
//-------------------------------------------------------
//@param: input which is second
//@return: minute
//-------------------------------------------------------
int minute(int input){
  return ((input - hour(input)*3600)/60);
}

//-------------------------------------------------------
//function to calculate how many second after convert to 
//hour and minute
//-------------------------------------------------------
//@param: input which is second
//@return: second
//-------------------------------------------------------
int second(int input){
  return (input - (hour(input)*3600 + minute(input)*60));
}

int main(){
  double input;
  cout << "Enter in a number of second as an integer: ";
  cin >> input;
  cout << input
       << " seconds is equivalent to "
       << hour(input)
       << " hours "
       << minute(input)
       << " minutes "
       << second(input)
       << " seconds."
       << endl;  
  return EXIT_SUCCESS;
}
