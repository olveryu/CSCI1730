
#include<iostream>
#include<cstdlib>

using std::cout;
using std::endl;
using std::cin;

int endtime(int start, int duration);

/**
   main function
*/

int main(){
  int start,duration;
  cout << "Enter in a start time: ";
  cin >> start;
  cout << "Enter in a duration:  ";
  cin >> duration;
  cout << "End time is: " << endtime(start,duration) << endl;
  return EXIT_SUCCESS;
}

/**
   calculate the end time

   @param: start which is the start time, duration which is the duration time you need to add
   @return: the endtime
*/

int endtime(int start, int duration){
  int hour = 0;
  int minute = 0;
  int hourCounter = 0;
  hour = start/100 + duration/100;                 //add up the hour
  minute = start%100 + duration%100;               //add up the minute
  while(minute / 60 > 0){                          //convert the minute and add too hour
    minute -= 60;
    hourCounter ++;
  }
  hour += hourCounter;
  while(hour / 24 > 0){                            //convert hour
    hour -= 24;
  }
  return hour * 100 + minute;
}
