
#include <iostream>
#include <cstdlib>
#include "Vector.h"

using cs1730::Vector;
using std::cout;
using std::endl;

int main() {

  Vector v1 = {1, 2, 3};
  Vector v2 = {4, 5, 6,3,4,5,6,7,8,9};

  cout << v1 << endl;
  cout << v2 << endl;
  
  v1 = v2;

  cout << v1 << endl;

  /*
  v1.at(0) = 7;

  cout << v1 << endl;
  cout << (v1 + 2) << endl;
  cout << (2 + v1) << endl;
  cout << (v1 - 2) << endl;
  cout << (2 - v1) << endl;
  cout << (v1 - v2) << endl;

  cout << v2 << endl;
  cout << (v2 + 2) << endl;
  cout << (2 + v2) << endl;
  cout << (v2 - 2) << endl;
  cout << (2 - v2) << endl;
  cout << (v2 - v1) << endl;
  */

  return EXIT_SUCCESS;
} // main


