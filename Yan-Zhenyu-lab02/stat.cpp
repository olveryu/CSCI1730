
#include<iostream>
#include<cstdlib>
#include<string>
#include<sstream>
#include<stdio.h>

using std::cout;
using std::endl;
using std::cin;
using std::stringstream;
using std::string;
using std::getline;

//-------------------------------------------------------------------
//this function calculate how many number the user input
//-------------------------------------------------------------------
//@param: input which is a string of a group of number separate by space
//@return: how many numbers in this string
//-------------------------------------------------------------------
int counter(string input){
  stringstream stream(input);      //read the line
  double number = 0;               //declared the number
  int counter = 0;                 //how many numbers in it
  while(stream >> number){
    counter++;
  }
  return counter;                  //return how many number user input
}

//-------------------------------------------------------------------
//this function is to calculate the sum of the input
//-------------------------------------------------------------------
//@param: input which is a string of a group of number separate by space
//@return: the sun
//-------------------------------------------------------------------
double sum(string input){
  stringstream stream(input);      //read the line
  double sum = 0;                  //declare the sum
  double number = 0;               //declare the number
  while(stream >> number){
    sum += number;                 //calculate the sum
  };
  return sum;
}

//-------------------------------------------------------------------
//this function is to calculate the average
//-------------------------------------------------------------------
//@param: input which is a string of a group of number separate by space
//@return: the average
//-------------------------------------------------------------------
double average(string input){
  double average = 0;                  //declare the average
  average = sum(input)/counter(input); //calculate the average
  return average;
}


//-------------------------------------------------------------------
//this is the function to calculate sum of squares
//-------------------------------------------------------------------
//@param: input which is a string of a group of number separate by space
//@return: the sum of square
//-------------------------------------------------------------------
double sumOfSquare(string input){
  stringstream stream(input);
  double number = 0;               //declare the number
  double sumOfSquare = 0;          //declare the sum of square
  while(stream >> number){
    sumOfSquare += number*number;  //caculate the sum of square
  }
  return sumOfSquare;
}
//-------------------------------------------------------------------
//this is the function to calculate sum of variance
//-------------------------------------------------------------------
//@param: input which is a string of a group of number separate by space
//@return: the variance
//-------------------------------------------------------------------
double variance(string input){
  stringstream stream(input);
  double number = 0;                     //declare the number
  double variance = 0;                   //declare the variance
  double difference = 0;                 //declare the diffrence
  while(stream >> number){
    difference = number - average(input);//calculate the difference
    variance += difference*difference;   //add up the square of difference
  }
  variance = variance / counter(input);  //calculate the variance
  return variance;
}

//-------------------------------------------------------------------
//main function
//-------------------------------------------------------------------
int main(){
  string input;
  cout << "Enter integers: ";
  getline(cin,input);
  cout << "Sum: ";
  printf("%.1f \n",sum(input));
  cout << "Average: ";
  printf("%.1f \n",average(input));
  cout << "Sum Of Squares: ";
  printf("%.1f \n",sumOfSquare(input));
  cout << "Variances: ";
  printf("%.2f \n",variance(input));
  return EXIT_SUCCESS;
}
