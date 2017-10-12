
#include<iostream>
#include<string>
#include<iomanip>
#include<cstdlib>

using std::cout;
using std::cin;
using std::endl;
using std::string;

//--------------------------------------------------------------
//function to regonize what kind of string will print
//--------------------------------------------------------------
//@param: number
//@return: get the message
//--------------------------------------------------------------
string message(int number){
  string message = "";                      //declare the string
  if(number % 3 == 0 || number % 5 == 0){
    message = (number % 3 == 0)? message += "Go":message;
    message = (number % 5 == 0)? message += "dawgs":message;
  }else{
    message = "Sic'Em";
  }
  return message;                           //return the string
}

//--------------------------------------------------------------
//function to print the number in binary format
//--------------------------------------------------------------
//@param: number
//--------------------------------------------------------------
void binary(short number){
  short shift = (1<<4)-1;                  //use to shift the mask 
  short mask = 1 << shift;                 //mask for comparing
  cout << "0b";
  for (int i = 0; i < shift+1; i++){
    cout << ((number & mask)? "1" : "0");
    number <<= 1;
    if((i+1)%4 == 0 && i != shift){       //add a "'" every 4bit
      cout << "'";
    }
  }
}

//--------------------------------------------------------------
//main function
//--------------------------------------------------------------
int main(){
  int range = (1<<16);
  for(int i=0; i<range; i++){
    binary(i);
    cout << " "
	 << std::oct << i << " "
	 << std::dec << i << " "
	 << std::showbase << std:: hex << i << " "
	 << message(i)
	 << endl;
  }
  return EXIT_SUCCESS;
}
