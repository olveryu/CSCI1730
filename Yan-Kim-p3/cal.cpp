#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <cstring>
#include <grp.h>
#include <cmath>

using namespace std;
using std::string;
using std::stringstream;
#define ANSI_COLOR_GREY     "\x1b[30;47m"
#define ANSI_COLOR_RESET      "\x1b[0m"

int startDay(int );
int daysInMonth(int); 
void monthName(int); 
void month(int, int&); 
void nextDay(int);
bool leapYearCheck(int);
int julOrGregCheck(int);
void startDayCalculatorforMonth(int, int, int, int, int);
int removeFirstDigit(int);
void date();
bool leapCheck;
int jvGCheck;
bool last3Months1752;
bool is1752September;
bool monthAndYear;
int leapCount;
int startOfMonthDay;
int yearToday;
int monthToday;
int dayToday;
bool compare;
bool monthYearCompare;
int yearOverall;
 
int main (int argc, char *argv[]) 
{
  setvbuf(stdout,NULL,_IONBF,BUFSIZ);
  cout.setf(std::ios_base::unitbuf);

    int year, firstDayOfMonth;
    int monthDay;
    int monthCount = 1;
    int numberOfDays;
    string nameOfFile = "";
    last3Months1752 = false;
    is1752September = false;
    monthAndYear = false;
    monthYearCompare = false;
    bool yearExists = false;
    string argument = "";

    if (argc >= 4){
      fprintf(stderr,"Error. Incorrect argument. Please try again.");     //Prints out error with incorrect input
      exit(EXIT_FAILURE);
    }
    
if(argc == 3){
    yearExists = true;
}

if((argc == 2) || (argc == 3)){
    for (int i = 1; (i < argc) && (i <= 1); i++){
        argument = argv[i];
    }
}

    //checks to see if a month has been input

    if((argument == "1" || argument == "2" || argument == "3" || argument == "4"
      || argument == "5" || argument == "6" || argument == "7" || argument == "8"
      || argument == "9" || argument == "10" || argument == "11" || argument == "12") && (yearExists == true)){
    monthAndYear = true;
    stringstream monthValue;
    monthValue << argument;
    int intMonthValue;
    monthValue >> intMonthValue;
    monthDay = intMonthValue;
}
else if((argument != "1" && argument != "2" && argument != "3" && argument != "4"
      && argument != "5" && argument != "6" && argument != "7" && argument != "8"
      && argument != "9" && argument != "10" && argument != "11" && argument != "12") && (yearExists == true)){
      fprintf(stderr,"Error. Incorrect argument. Please try again.");    //Prints out error with incorrect input
      exit(EXIT_FAILURE);
}
else{
    //do nothing
}

if (monthAndYear == true){                                               //gets year
        for(int i = 2; i < argc; i++)
    {
        nameOfFile = argv[i];
        stringstream strValue;
         strValue << nameOfFile;

        int intValue;
         strValue >> intValue;
         year = intValue;
    }
}
else{
    for(int i = 0; i < argc; i++)                                        //gets year
    {
        nameOfFile = argv[i];
        stringstream strValue;
         strValue << nameOfFile;

        int intValue;
         strValue >> intValue;
         year = intValue;
    }
}

    yearOverall = year;
    date();

    if((year == yearToday) && (monthDay == monthToday)){
        compare = true;
    }

    julOrGregCheck(year);

    if (leapYearCheck(year)==true){
        leapCheck = true;
    }
    else
    {
        leapCheck = false;
    }

    firstDayOfMonth=startDay(year);
    startDayCalculatorforMonth(year, monthDay, year, 1, year);
    
    //prints out only a single month
    
    if(monthAndYear == true){
        monthCount = monthDay;
        if (jvGCheck == 0){
            if (monthCount <= 8){
        firstDayOfMonth=startOfMonthDay;
        while (monthCount <= monthDay) {
        numberOfDays = daysInMonth(monthCount);
        monthName(monthCount);
        month(numberOfDays, firstDayOfMonth);
        printf("\n");
        printf("\n");
        monthCount = monthCount + 1;
    }
}
else if (monthCount == 9){
        firstDayOfMonth=startOfMonthDay;
        while (monthCount <= 9) {
        numberOfDays = 2;
        monthName(monthCount);
        month(numberOfDays, firstDayOfMonth);
        is1752September = true;
        numberOfDays = 17;
        month(numberOfDays, firstDayOfMonth);
        monthCount++;
        printf("\n");
    }
}
else if (monthCount == 10 || monthCount == 11 || monthCount == 12){
        last3Months1752 = true;
        is1752September = false;
        startDayCalculatorforMonth(year, monthDay, year, 1, year);
        firstDayOfMonth=startOfMonthDay;
        while (monthCount <= monthDay) {
        numberOfDays = daysInMonth(monthCount);
        monthName(monthCount);
        month(numberOfDays, firstDayOfMonth);
        monthCount = monthCount + 1;
        printf("\n");
        printf("\n");
    }
}
}
    else{
        is1752September = false;
    while (monthCount <= monthDay) {
        firstDayOfMonth=startOfMonthDay;
        numberOfDays = daysInMonth(monthCount);
        monthName(monthCount);
        month(numberOfDays, firstDayOfMonth);
        printf("\n");
        printf("\n");
        monthCount = monthCount + 1;
    }
}
}
else{
        firstDayOfMonth=startDay(year);
        printf("\t%d\n",year);
        if (jvGCheck == 0){                                                //starts from january
        while (monthCount <= 8) {
            monthYearCompare = false;
            if ((monthCount == monthToday) && (year == yearToday)){
              monthYearCompare = true;
            }
        numberOfDays = daysInMonth(monthCount);
        monthName(monthCount);
        month(numberOfDays, firstDayOfMonth);
        printf("\n");
        printf("\n");
        monthCount = monthCount + 1;
    }
        monthCount = 9;                                                     //september
        while (monthCount <= 9) {
            monthYearCompare = false;
             if ((monthCount == monthToday) && (year == yearToday)){
              monthYearCompare = true;
            }
        numberOfDays = 2;
        monthName(monthCount);
        month(numberOfDays, firstDayOfMonth);
        is1752September = true;
        numberOfDays = 17;
        month(numberOfDays, firstDayOfMonth);
        monthCount++;
        printf("\n");
    }
        monthCount = 10;                                                    //starts from october
        last3Months1752 = true;
        is1752September = false;
        firstDayOfMonth=startDay(year);
        while (monthCount <= 12) {
            monthYearCompare = false;
             if ((monthCount == monthToday) && (year == yearToday)){
              monthYearCompare = true;
            }
        numberOfDays = daysInMonth(monthCount);
        monthName(monthCount);
        month(numberOfDays, firstDayOfMonth);
        monthCount = monthCount + 1;
        printf("\n");
        printf("\n");
    }
}
    else{
        is1752September = false;
    while (monthCount <= 12) {                                              //prints out whole year
        monthYearCompare = false;
         if ((monthCount == monthToday) && (year == yearToday)){
              monthYearCompare = true;
            }
        numberOfDays = daysInMonth(monthCount);
        monthName(monthCount);
        month(numberOfDays, firstDayOfMonth);
        printf("\n");
        printf("\n");
        monthCount = monthCount + 1;
    }
}
}
    printf("\n");
    return EXIT_SUCCESS;
}

    /******************************************
   int julOrGregCheck - checks to see if the year is julian or gregorian
    Author: Stephen Kim and Zhenyu Yan
    Date: 4/11/2017
    Parameters: year = year to be checked
  *******************************************/

    int julOrGregCheck(int year){
        if(year <= 1751){               //julian
            jvGCheck = -1;
            return -1;
        }
        else if (year >= 1753){         //gregorian
            jvGCheck = 1;
            return 1;
        }
        else{                           //1752
            jvGCheck = 0;
            return 0; 
        }
    }

    /******************************************
   startDayCalendarForMonth - calculates the starting day of a single month
    Author: Stephen Kim and Zhenyu Yan
    Date: 4/11/2017
    Parameters: yearCode = year
                monthCode = month
                centuryCode = century
                dayCode = day
                leapCode = leap year check
  *******************************************/

    void startDayCalculatorforMonth(int yearCode, int monthCode, int centuryCode, int dayCode, int leapCode){
        int yearC;
        int monthC;
        int centuryC;
        int dayC = dayCode;
        int leapC;
        int yearCodeRemove;

        yearCodeRemove = removeFirstDigit(yearCode);
        yearCodeRemove = removeFirstDigit(yearCodeRemove);

        yearC = (yearCodeRemove + ( yearCodeRemove/4)) % 7;             //gets the year code

        if (monthCode == 1){                                            //gets the month code
            monthC = 0;
        }
        else if(monthCode == 2){
            monthC = 3;
        }
        else if(monthCode == 3){
            monthC = 3;
        }
         else if(monthCode == 4){
            monthC = 6;
        }
         else if(monthCode == 5){
            monthC = 1;
        }
         else if(monthCode == 6){
            monthC = 4;
        }
         else if(monthCode == 7){
            monthC = 6;
        }
         else if(monthCode == 8){
            monthC = 2;
        }
         else if(monthCode == 9){
            monthC = 5;
        }
         else if(monthCode == 10){
            monthC = 0;
        }
         else if(monthCode == 11){
            monthC = 3;
        }
         else{
            monthC = 5;
        }

        centuryCode /= 10;                                                //gets the first 2 digits of a year
        centuryCode /= 10;

        if((jvGCheck == 1) || (last3Months1752 == true)){

        if ((centuryCode == 17) || (centuryCode == 21) || (centuryCode == 25) || (centuryCode == 29) ||
            (centuryCode == 33) || (centuryCode == 37) || (centuryCode == 41) || (centuryCode == 45) ||
            (centuryCode == 49) || (centuryCode == 53) || (centuryCode == 57) || (centuryCode == 61) ||
            (centuryCode == 65) || (centuryCode == 69) || (centuryCode == 73) || (centuryCode == 77) ||
            (centuryCode == 81) || (centuryCode == 85) || (centuryCode == 89) || (centuryCode == 93) ||
            (centuryCode == 97)){
            centuryC = 4;
        }
        else if((centuryCode == 18) || (centuryCode == 22) || (centuryCode == 26) || (centuryCode == 30) ||
            (centuryCode == 34) || (centuryCode == 38) || (centuryCode == 42) || (centuryCode == 46) ||
            (centuryCode == 50) || (centuryCode == 54) || (centuryCode == 58) || (centuryCode == 62) ||
            (centuryCode == 66) || (centuryCode == 70) || (centuryCode == 74) || (centuryCode == 78) ||
            (centuryCode == 82) || (centuryCode == 86) || (centuryCode == 90) || (centuryCode == 94) ||
            (centuryCode == 98)){
            centuryC = 2;
        }
        else if((centuryCode == 19) || (centuryCode == 23) || (centuryCode == 27) || (centuryCode == 31) ||
            (centuryCode == 35) || (centuryCode == 39) || (centuryCode == 43) || (centuryCode == 47) ||
            (centuryCode == 51) || (centuryCode == 55) || (centuryCode == 59) || (centuryCode == 63) ||
            (centuryCode == 67) || (centuryCode == 71) || (centuryCode == 75) || (centuryCode == 79) ||
            (centuryCode == 83) || (centuryCode == 87) || (centuryCode == 91) || (centuryCode == 95) ||
            (centuryCode == 99)){
            centuryC = 0;
        }
        else if((centuryCode == 20) || (centuryCode == 24) || (centuryCode == 28) || (centuryCode == 32) ||
            (centuryCode == 36) || (centuryCode == 40) || (centuryCode == 44) || (centuryCode == 48) ||
            (centuryCode == 52) || (centuryCode == 56) || (centuryCode == 60) || (centuryCode == 64) ||
            (centuryCode == 68) || (centuryCode == 72) || (centuryCode == 76) || (centuryCode == 80) ||
            (centuryCode == 84) || (centuryCode == 88) || (centuryCode == 92) || (centuryCode == 96)){
            centuryC = 6;
        }
        else
        {
            cout << "error!" << endl;
        }
    }
    else{
        centuryC = (18 - centuryCode) % 7;
    }

        if ((leapCode % 400 == 0 || (leapCode % 4 == 0 && leapCode % 100 != 0)) && ((monthCode == 1) || (monthCode == 2))) //checks to see if a leap year
        {
            leapC = 1;
        }

     startOfMonthDay = ((yearC + monthC + centuryC + dayC - leapC) % 7);
    }


    /******************************************
   startDay - calculates the starting day if printing out all 12 months of a year
    Author: Stephen Kim and Zhenyu Yan
    Date: 4/11/2017
    Parameters: year - current year
  *******************************************/

    int startDay(int year) { 
        if (((jvGCheck == -1) || (jvGCheck == 0)) && (last3Months1752 == false))                //julian
        {
        int startingDay; 
        int x1;
        x1 = (year - 1)/ 4;
        startingDay = ((year + x1) % 7);
        if (startingDay == 1){
            startingDay = startingDay + 5;
        } 
        else if (startingDay == 0){
            startingDay = startingDay + 5;
        }
        else{
            if (monthAndYear == true){
            startingDay = startingDay - 3;
            }else{
            startingDay = startingDay - 2;
            }
        }
        return startingDay; 
        }
        else if ((jvGCheck == 0) && (last3Months1752 == true))                                   //gregorian
        {
        int startingDay; 
        int x1, x2, x3; 
        x1 = (year - 1)/ 4;
        x2 = (year - 1)/ 100; 
        x3 = (year - 1)/ 400; 
        startingDay = ((year + x1 - x2 + x3) % 7) - 6; 
        return startingDay; 
        } 
        else{
        int startingDay; 
        int x1, x2, x3; 
        x1 = (year - 1)/ 4;
        x2 = (year - 1)/ 100; 
        x3 = (year - 1)/ 400; 
        startingDay = (year + x1 - x2 + x3) % 7; 
        return startingDay; 
    }
    } 

    /******************************************
   leapYearCheck - checks to see if the year is a leap year
    Author: Stephen Kim and Zhenyu Yan
    Date: 4/11/2017
    Parameters: year - current year
  *******************************************/

    bool leapYearCheck(int year){
        if ((jvGCheck == -1) || (jvGCheck == 0)){                   
            if (year % 4 == 0){                                                                  //julain leap year
                leapCount = leapCount + 1;
                return true;
            }
            else
            {
                return false;
            }
        }
        else{
        if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))                               //gregorian leap year
        {
            leapCount = leapCount + 1;
            return true;
        }
        else
        {
            return false;
        }
    }
    }

    /******************************************
   month - prints out the days of the month (format)
    Author: Stephen Kim and Zhenyu Yan
    Date: 4/11/2017
    Parameters: numberOfDays - total number of days in a month
                &weekDay - the day of which the month starts on
  *******************************************/

    void month (int numberOfDays, int &weekDay) {
        int startDay;

        if (is1752September == true){                                                            //if its 1752 and september, start day from 14
            startDay = 14;
            numberOfDays = 30;
        }
        else{
            startDay = 1;
            nextDay(weekDay);
        }
        while (startDay <= numberOfDays) {
            if ((compare == true) && (startDay == dayToday)){                                    //if a single month is printed
                cout << setw(2) << ANSI_COLOR_GREY << startDay << ANSI_COLOR_RESET << " ";       //colors text grey
            }
            else if ((monthYearCompare == true) && (startDay == dayToday)){                      //if a whole year is printed
                cout << setw(2) << ANSI_COLOR_GREY << startDay << ANSI_COLOR_RESET << " ";       //colors text grey
            }
            else{
                cout << setw(2) << startDay << " ";
            }
            if (weekDay == 6){
                printf("\n");
                weekDay = 0;
            }
        else weekDay = weekDay + 1;
        startDay = startDay + 1; 
        }
    }

    /******************************************
   skip - places a number of spaces from one day to the next
    Author: Stephen Kim and Zhenyu Yan
    Date: 4/11/2017
    Parameters: i = current day number
  *******************************************/

    void skip (int i) {
        while (i > 0) {
            cout << " ";
            i = i - 1;
        }
    }

    /******************************************
   nextDay - writes the next day a current number of spaces from the last
    Author: Stephen Kim and Zhenyu Yan
    Date: 4/11/2017
    Parameters: i = current day number
  *******************************************/

    void nextDay (int i){
        return skip(3*i);
    }

    /******************************************
   monthName - writes the name of the month above the chart
    Author: Stephen Kim and Zhenyu Yan
    Date: 4/11/2017
    Parameters: i = month
  *******************************************/

    void monthName (int i) {
        if(monthAndYear == true){
        if (i == 1){ 
        printf("      January %d\n",yearOverall);
    }
    else if (i == 2) {
        printf("      February %d\n",yearOverall);
    }  
    else if (i == 3) {     
        printf("\tMarch %d\n",yearOverall); 
    }
    else if (i == 4) {  
        printf("        April %d\n",yearOverall);
    }
    else if (i == 5) {  
        printf("\tMay %d\n",yearOverall);
    }
    else if (i == 6) {  
        printf("\tJune %d\n",yearOverall);
    }
    else if (i == 7) {  
        printf("\tJuly %d\n",yearOverall);
    }
    else if (i == 8) { 
        printf("       August %d\n",yearOverall);
    }
    else if (i == 9) {  
        printf("      September %d\n",yearOverall);
    }
    else if (i == 10) {
        printf("       October %d\n",yearOverall);  
    }
    else if (i == 11) {
        printf("      November %d\n",yearOverall);
    }  
    else if (i == 12) {
        printf("      December %d\n",yearOverall);
    }  
}
else
{
    if (i == 1){ 
        printf("      January\n");
    }
    else if (i == 2) {
        printf("      February\n");
    }  
    else if (i == 3) {     
        printf("\tMarch\n"); 
    }
    else if (i == 4) {  
        printf("        April\n");
    }
    else if (i == 5) {  
        printf("\tMay\n");
    }
    else if (i == 6) {  
        printf("\tJune\n");
    }
    else if (i == 7) {  
        printf("\tJuly\n");
    }
    else if (i == 8) { 
        printf("       August\n");
    }
    else if (i == 9) {  
        printf("      September\n");
    }
    else if (i == 10) {
        printf("       October\n");  
    }
    else if (i == 11) {
        printf("      November\n");
    }  
    else if (i == 12) {
        printf("      December\n");
    }    
}
    
    printf("Su Mo Tu We Th Fr Sa\n");

    }

    /******************************************
   daysInMonth - returns the number of days in a month
    Author: Stephen Kim and Zhenyu Yan
    Date: 4/11/2017
    Parameters: i = month
  *******************************************/

    int daysInMonth (int i){
        if (i == 1) {                   //january
           return(31);
        }
        else if (i == 2) {              //february
            if (leapCheck == true){
             return(29);                //29 if leapyear
            }
            else
            {
                return(28);
            }
        }
        else if (i == 3) {              //march
             return(31);
        }
        else if (i == 4) {
             return(30);
        }
        else if (i == 5) {
             return(31);
        }
        else if (i == 6) {
             return(30);
        }
        else if (i == 7) { 
             return(31);
        }
        else if (i == 8) {
            return(31);
        }
        else if (i == 9) {
            return(30);
        }
        else if (i == 10) {
            return(31);
        }
        else if (i == 11) {
            return(30);
        }
        else if (i == 12) {             //december
            return(31);
        }
        else
        {
            return 0;
        }
    }

    /******************************************
   removeFirstDigit - deletes the first digit of a number
    Author: Stephen Kim and Zhenyu Yan
    Date: 4/11/2017
    Parameters: n = number to be truncated (year)
  *******************************************/

int removeFirstDigit(int n)
{
    if ( n < 100){          //returns last 2 digits of a number
        return n;
    }
    else{
    int tmp(0);
    for (int i(0);; ++i)
    {
        int m = n % 10;
        n /= 10;
        if (n != 0)
        {
            tmp += std::pow(10, i) * m;
        }
        else
        {
            break;
        }
    }
    return tmp;
    }
}

    /******************************************
   date - gets the current date from the system
    Author: Stephen Kim and Zhenyu Yan
    Date: 4/11/2017
  *******************************************/

void date(){
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
   yearToday = now->tm_year + 1900; 
   monthToday = now->tm_mon + 1;
   dayToday = now->tm_mday;
}

