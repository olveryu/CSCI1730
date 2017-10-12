
#include<iostream>
#include<cstdlib>
#include<math.h>

using std::cout;
using std::endl;
using std::cin;

long primeSum(int input);
bool isPrime(int num);

/**
   main function
 */

int main(){
  int input;
  cout << "Enter integers: ";
  cin >> input;
  cout << "Prime sum: " << primeSum(input) << endl;
  return EXIT_SUCCESS;
}

/**
   calculate the prime sum
   
   @param: input which is how many pirme number to sum
   @return: prime sum 
 */

long primeSum(int input){
  long primesum = 0;              
  int num = 0;                   //num is the number
  int counter = 1;               //counter is how many prime you want to sum
  while(counter<=input){
    if(isPrime(num)){
      primesum += num;
      counter++;
    }
    num++;
  }
  return primesum;
}

/**
   determine is the number is a prime number
   
   @param: num which is the number
   @return; is prime which is true or false
 */
bool isPrime(int num){  
  if(num == 1)                               //1 is not a prime number
    return 0;
  if(num == 2 || num == 3 || num == 5)       //2,3,5 is a prime number
    return 1;
  if(num % 5 == 0)                           //if num % 5 is 0, it is not a prime number
    return 0;  
  if((num % 6 != 1) && (num % 6 != 5))       //if num % 6 must equal 1 or 5 because if num % 6 = 0,2,4
    return 0;                                //it can be divide by 2, and if num % 6 = 3, it can be divide by 3
  int temp =sqrt( num);  
  for(int i=6; i<=temp; i+=6)                
    if(num % (i+1) == 0 || num % (i+5) == 0) //only check the number which does not mutiple by 2,3
      return 0 ;
  return 1 ;  
}  
