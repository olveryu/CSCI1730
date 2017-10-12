
#include <iostream>
#include <bitset>
#include <cstdlib>
#include <math.h>

using std::cout;
using std::cin;
using std::endl;

unsigned int var = 0;

//--------------------------------------------------------
//This function takes in our storage variable by reference
//--------------------------------------------------------
void setValue(unsigned int & var, unsigned int k, unsigned int i, unsigned int val){
  unsigned int front;         // the value in front of the index
  unsigned int rear;          // the value before the index
  front = rear = var;

  // clear the value in that position
  if(i==k-1){                 // save the front
    front = 0;
  }else{
    front = front >> (32/k*(i+1)) << (32/k*(i+1));
  }
  if(i==0){                   // save the rear
    rear = 0;
  }else{
    rear = rear << (32/k*(k-i)) >> (32/k*(k-i));
  }
  var = front | rear;         // save the front and rear

  //set the value
  val = val << (32/k*i);      // left shift the value to the position
  var = val | var;            // store the value
}

//----------------------------------------------------
//This function takes in our storage variable by value
//----------------------------------------------------
unsigned int getValue(unsigned int var, unsigned int k, unsigned int i){
  unsigned int temp = var;
  temp = temp << (32/k)*(k-i-1);     // clear number on the left
  temp = temp >> (32/k)*(k-1);       // clear number on the right
  return temp;
}

//----------------------------------------------------
//The entry-point to the program, should prompt the
//user for a value ofk, then prompt the user
//forkvalues.
//----------------------------------------------------  
int main(){
  unsigned int k;                   // is how many number we want to enter
  unsigned int val;                 // is the number
  unsigned int index;               // is the index you want to store
  unsigned int range;               // is the range that the user can input
  cout << "How many number do you want to store(1,2,4,8,16,32)?" << endl;
  cin >> k;                         // store the k
  range = pow(2.0,(32/k))-1;        // calculate the range
  cout << "please enter a number in range of(0-" << range << ")" << endl;
  for(int i=0; i<k; i++){
    cout << "which position do you want to store?(0-" << k-1 << ")" << endl;
    cin >> index;                   // ask for index
    cout << "please enter the number you want to store." << endl;
    cin >> val;                     // ask the value
    setValue(var,k,index,val);      // set the value
  }
  for(int i=0; i<k; i++){
    int result = getValue(var,k,i); // get the value
    cout << "the number in " << i << " position is: " << result << endl;
  }
  return EXIT_SUCCESS;
}
