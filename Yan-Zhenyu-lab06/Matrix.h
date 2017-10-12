
#ifndef MATRIX_H
#define MATRIX_H

#include <string>
#include <iostream>
#include <initializer_list>

using std::initializer_list;
using std::ostream;

typedef unsigned int uint;
typedef initializer_list<initializer_list<double>> i_list;

namespace MatrixProject{ 

  /**
   * the Matrix class stores and operates on numeric matrixs of 
   *element type double.
   */
 class Matrix{
   
   /**1st Dimenstion length of the vector*/
   uint rows;
   /**1st Dimenstion length of the vector*/
   uint cols;
   /**2 Dimenstion array*/
   double ** matrix = nullptr;
   
 public:
   
   /**
    * Constructs a new matrix object. Each element is initialized to 0.
    * @param rows: 1st dimention
    * @param cols: 2nd dimention
    */
   Matrix(uint rows, uint cols);
  
   /**
    * Constructs a new matrix object from an i_list list.
    * @param list: i_list list
    */   
   Matrix(const i_list & list); 

   /**
    * Construct a new matrix object as a copy of another matrix object.
    * @param m: matrix to copy
    */   
   Matrix(const Matrix & m);

   /**
    * Destructs the matrix object. 
    */
   ~Matrix();                   
   
   /**
    * Returns the sum of this `matrix` and some scaler `s`.
    * @param s: scaler to add
    */
   Matrix add(double s) const;  

   /**
    * Returns the sum of this `matrix` and another `matrix` of the same length.
    * @param m: matrix to add
    */
   Matrix add(const Matrix & m) const; 

   /**
    * Returns the difference of this `matrix` and some scaler `s`.
    * @param s: scaler to subtract
    */
   Matrix subtract(double s) const;             
   
   /**
    * Returns the difference of this `matrix` and another `matrix` of the same 
    * length.
    * @param m: matrix to subtract
    */
   Matrix subtract(const Matrix & m) const;     

   /**
    * Returns the product of this `matrix` and some scaler `s`.
    * @param s: scaler to multiply
    */
   Matrix multiply(double s) const;             
   
   /**
    * Returns the product of this `matrix` and another `matrix` of the same 
    * length.
    * @param m: matrix to multiply
    */
   Matrix multiply(const Matrix & m) const;     

   /**
    * Returns the quotient of this `matrix` and some scaler `s`.
    * @param s: scaler to divide
    */
   Matrix divide(double s) const;
   
   /**
    * return the transposition of the matrix
    */
   Matrix t() const;                            
   
   /**
    * return the number of rows in the matrix
    */
   const uint numRows() const;                  
   
   /**
    *return the number of cols in the martrix
    */
   const uint numCols() const;                  
   
   /**
    * return the element which you can get or set the element
    * @param m: row to the first dimension, col to the second dimention
    */
   double & at(uint row, uint col);             

   /**
    * return the element which you can get the element, This version is for const objects.
    * @param m: row to the first dimension, col to the second dimention
    */
   const double & at(uint row, uint col) const; 		
   
   /**
    * Copy assignment operator.
    * @param m: matrix to copy
    */
   Matrix & operator=(const Matrix & m);
   
   /**
    * Copy assignment operator.
    * @param list: i_list to copy
    */
   Matrix & operator=(const i_list & list);

   /**
    * Function Call at(row,col) Operator
    */
   double & operator()(uint row, uint col);

   /**
    * Function addtion Operator
    */
   Matrix operator+(const double s) const;

   /**
    * Function addtion Operator
    */

   Matrix operator+(const Matrix & m) const;
   /**
    * Function minus Operator
    */

   Matrix operator-(const double s) const;
   /**
    * Function minus Operator
    */

   Matrix operator-(const Matrix & m) const;
   /**
    * Function mulitiplication Operator
    */

   Matrix operator*(const double s) const;
   /**
    * Function multiplication Operator
    */

   Matrix operator*(const Matrix & m) const;
   /**
    * Function division Operator
    */

   Matrix operator/(const double s) const;
   
   /**
    * Function unary minus Operator: return the negation of the orginal matrix
    */
   Matrix operator-() const;
   
 };// Matrix
} // Matrix

/**
 * Non-Member Arithmetic Operators for Scalers
 */
MatrixProject::Matrix operator+(const double s, const MatrixProject::Matrix & m);
MatrixProject::Matrix operator-(const double s, const MatrixProject::Matrix & m);
MatrixProject::Matrix operator*(const double s, const MatrixProject::Matrix & m);
MatrixProject::Matrix operator/(const double s, const MatrixProject::Matrix & m);

/**
 * return the os of the matrix which print it out the whole matrix
 * @param os: cout
 * @param m : matrix
 */
ostream & operator <<(ostream & os, const MatrixProject::Matrix m);

#endif
