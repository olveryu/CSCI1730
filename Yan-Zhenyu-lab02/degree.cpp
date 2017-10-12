
#include<iostream>
#include<cstdlib>
#include<stdio.h>

using std::cout;
using std::cin;
using std::endl;

//-----------------------------------------
//function to convert celsius to fahrenheit
//-----------------------------------------
//@param: temperature, which is celsius
//@return: result which is in faherenheit
//-----------------------------------------
float celsiusToFahrenheit(float input){
  return (input*1.8)+32;
}


int main(){
  float input;
  cout << "Enter in a temperature in celsius: ";
  cin >> input;
  printf("%.2f",input);
  cout << " degress celsius converts to ";
  printf("%.2f",celsiusToFahrenheit(input));
  cout << " degree Fahrenheit." << endl;;
  return EXIT_SUCCESS;
}
