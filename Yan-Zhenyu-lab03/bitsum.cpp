
#include<iostream>
#include<cstdlib>

using std::cout;
using std::endl;
using std::cin;

int bitsum(unsigned long  number);

/**
   main function
*/

int main(){
  unsigned long number;
  cout << "Enter integer: ";
  cin >> number;
  cout << "Bit sum: " << bitsum(number) << endl;
  return EXIT_SUCCESS;
}

/**
   caculate the bit sum

   @param: number whitch is the number you want to get the bit sum
   @return: counter which is the bitsum
*/

int bitsum(unsigned long number){
  int shift = 8*sizeof(number)-1;            //determine how many bit I can shift
  unsigned long compare = 1;
  unsigned long mask = 0u;                   //mask of all 0
  int counter = 0;
  for(int i=1; i<=shift+1; i++){
    if((number & compare) != mask){
      counter++;
    }
    compare <<= 1;
  }
  return counter;
}

