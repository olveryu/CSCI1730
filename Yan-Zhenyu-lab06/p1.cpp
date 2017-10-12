
#include <iostream>
#include <cstdlib>
#include "Matrix.h"

using std::cout;
using std::endl;
using MatrixProject::Matrix;

int main() {
	cout << "Example Usage 1" << endl;
	Matrix a(2, 2); 
	a.at(0, 0) = 1; // [ 1, 2 ]
	a.at(0, 1) = 2; // [ 1, 3 ]
	a.at(1, 0) = 1;
	a.at(1, 1) = 3;
	Matrix b(2, 1);
	b.at(0, 0) = 3; // [ 3 ]
	b.at(1, 0) = 2; // [ 2 ]
	Matrix c = a.multiply(b);
	cout << "[ " << c.at(0, 0) << " ]" << endl  // [ 7 ]
		<< "[ " << c.at(1, 0) << " ]" << endl; // [ 9 ]
	Matrix d = {{1, 2},  // this will implicitly call the overloaded constructor
				{3, 4}}; // that takes an initializer list

	cout << "operator overloading" << endl;
	Matrix c0 = a + 5.2;
	Matrix c1 = a + a;   // NOTE: these examples actually end up calling the copy constructor
	Matrix c2 = a - 3.5; // e.g., this line is the same as Matrix c2(a - 3.5);
	Matrix c3 = b - b;
	Matrix c4 = a * 2.1;
	Matrix c5 = a * b;
	Matrix c6 = a / 2.0;
	cout << "a: " << endl << a << endl; // example output: [ 1, 2 ]
										//                 [ 1, 3 ]
	cout << "c0: " << endl << c0 << endl
		<< "c1: " << endl << c1 << endl
		<< "c2: " << endl << c2 << endl
		<< "c3: " << endl << c3 << endl
		<< "c4: " << endl << c4 << endl
		<< "c5: " << endl << c5 << endl
		<< "c6: " << endl << c6 << endl;

	cout << "support matrix assignment" << endl;
	Matrix d1(2, 2); 
	d1 = { { 1, 2 },
	       { 3, 4 } };
	cout << d1 << endl;

	cout << "Overloaded Function Call Operator" << endl;
	Matrix a1(1, 1);
	a1(0, 0) = 5; 
	cout << a1(0, 0) << endl;

	cout << "Overloaded Copy Assignment Operator" << endl;
	Matrix a2(1, 1); 
	a2(0, 0) = 5; 
	Matrix b2(1, 1); 
	b2 = a2; // copy assignment
	cout << b2 << endl;

	cout << "Overloaded Unary Minus Operator" << endl;
	Matrix a4 = { { 1, 2 } }; 
	cout << -a4 << endl;// [ -1, -2 ]

	cout << "transpose" << endl;
	cout << a4.t() << endl;

	cout << "Overloaded Non-Member Arithmetic Operators for Scalers:" << endl;
	Matrix m = { { 1, 2 },{ 3, 4 } };
	Matrix m1 = 4.0 + m; // [ 5, 6 ]
						// [ 7, 8 ]
	Matrix m2 = 4.0 - m; // [ 3, 2 ]
						// [ 1, 0 ]
	Matrix m3 = 2.0 * m; // [ 2, 4 ]
						// [ 6, 8 ]
	Matrix m4 = 12.0 / m; // [ 12, 6 ]
						 //[  4, 3 ]

	cout << "m:" << endl << m << endl;
	cout << "m1:" << endl << m1 << endl;
	cout << "m2:" << endl << m2 << endl;
	cout << "m3:" << endl << m3 << endl;
	cout << "m4:" << endl << m4 << endl;


  getchar();
  return EXIT_SUCCESS;
}
