#include <iostream>
#include <cstdlib>
#include "GradeBook.h"

using std::cout;
using std::endl;

int main() {

  GradeBook gb1("cs1730");                     // automatic allocation on stack
  gb1.displayMessage();                        // use dot notation for members
  gb1.setCourseName("cs1730!!!");              // change course name
  cout << gb1.getCourseName() << endl;
  // cout << gb1.courseName << endl;           // won't work; private visibility

  const GradeBook gb2("cs2610");               // automatic allocation on stack
  gb2.displayMessage();
  // gb2.setCourseName("cs2610!!!");           // won't work! gb2 is a const object.
  cout << gb2.getCourseName() << endl;
  // cout << gb2.courseName << endl;           // won't work; private visibility

  GradeBook * gbp1 = new GradeBook("cs1302");  // explicit allocation in heap
  //gbp1.displayMessage();                     // gbp1 is a pointer to an object
  gbp1->displayMessage();                      // can use a->b instead of (*a).b 
  (*gbp1).displayMessage();                    // this way not preferred
  cout << gbp1->getCourseName() << endl;
  // cout << gb1->courseName << endl;          // won't work; private visibility
  delete gbp1;                                 // explicit deallocation

  GradeBook * gbp2 = new GradeBook("cs2720");  // explicit allocation in heap
  const GradeBook * gbp3 = gbp2;
  // gbp3->setCourseName("cs27120!!!");        // won't work; gbp3 points to const
  gbp3->displayMessage();
  delete gbp3;                                 // explicit deallocation

  return EXIT_SUCCESS;

} // main
