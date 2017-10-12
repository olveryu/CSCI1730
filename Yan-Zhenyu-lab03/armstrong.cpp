
#include<iostream>
#include<cstdlib>

using std::cout;
using std::endl;
using std::cin;

void armstrong();
/**
   main funcition
*/

int main(){
  armstrong();
  return EXIT_SUCCESS;
}

/**
   print all three digits armstrong number
*/

void armstrong(){
  for(int i=100; i<1000; i++){  //i is the range of the number
    int k = 0;                  //the first digit
    int sum = 0;
    int temp = i;               //store the number as temp
    while(temp > 0){
      k = temp % 10;            //get the first digit
      sum += k * k * k;         //cube the single digit
      temp = temp/10;           //get rid of the first diit
    }
    if(sum == i){
      cout << "Armstrong Number: " << i << endl;
    }
  }
}
