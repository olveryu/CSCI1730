 
#include "GradeBook.h"
#include <iostream>

using std::cout;
using std::endl;

// do not include "static" here
unsigned int GradeBook::numGradeBooks = 0;

GradeBook::GradeBook(const string & name) {
  courseName = name;
  numGradeBooks += 1;
} // GradeBook

GradeBook::~GradeBook() {
  numGradeBooks -= 1;
} // ~GradeBook

const string & GradeBook::getCourseName() const {
  return courseName;
} // getCourseName

void GradeBook::setCourseName(const string & name) {
  courseName = name;
  // this->courseName = name;
  // (*this).courseName = name;
  // NOTE: "this" is a pointer to the current object
} // setCourseName

void GradeBook::displayMessage() const {
  cout << "message from "
       << courseName
       << "!"
       << endl;
} // displayMessage
