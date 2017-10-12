
#include "Matrix.h"
#include <iostream>

using MatrixProject::Matrix;

Matrix::Matrix(uint rows, uint cols){
  this->rows = rows;
  this->cols = cols;
  matrix = new double * [rows];					// allocate 1st dimension
  for(uint i = 0; i < rows; i++){				// allocate 2nd dimension
    matrix[i] = new double [cols];
    for(uint j = 0; j < cols; j++){
      matrix[i][j] = 0;						// all elements initialized to 0
    }
  }
} // Matrix

Matrix::Matrix(const i_list & list){
  rows = list.size();
  cols = list.begin()->size();
  auto row = list.begin();
  matrix = new double *[rows];					// allocate 1st dimension
  for (uint i = 0; i < rows; i++) {
    auto col = row[i].begin();
    matrix[i] = new double [cols];				// allocate 2nd dimension
    for (uint j = 0; j < cols; ++j) {
      matrix[i][j] = col[j];					// copy elements to this matrix 
    }
  }
} // Matrix

Matrix::Matrix(const Matrix & m) {
  rows = m.rows;
  cols = m.cols;
  matrix = new double * [rows];					// allocate 1st dimention
  for (uint i = 0; i < rows; i++) {				// allocate 2nd dimention
    matrix[i] = new double[cols];
    for (uint j = 0; j < cols; j++) {
      matrix[i][j] = m.matrix[i][j];				// copy elements to this matrix
    }
  }
} // Matrix

Matrix::~Matrix() {
  for (uint i = 0; i < rows; ++i) {				// deallocate 2nd dimension
    delete[] matrix[i];
  }
  delete[] matrix;					      	// deallocate 1st dimension
} // ~Matrix

Matrix Matrix::add(double s) const {
  Matrix temp(*this);			       			// copy this matrix
  for (uint i = 0; i < rows; i++) {	
    for (uint j = 0; j < cols; j++) {
      temp.matrix[i][j] += s;					// all elements add s
    }
  }
  return temp;
} // add

Matrix Matrix::add(const Matrix & m) const {
  Matrix temp(*this);		       				// copy this matrix
  for (uint i = 0; i < rows; i++) {
    for (uint j = 0; j < cols; j++) {
      temp.matrix[i][j] += m.matrix[i][j];			// all elements add other matrix m
    }
  }
  return temp;
} // add

Matrix Matrix::subtract(double s) const {
  Matrix temp(*this);					      	// copy this matrix
  for (uint i = 0; i < rows; i++) {
    for (uint j = 0; j < cols; j++) {
      temp.matrix[i][j] -= s;					// all elements subtract s
    }
  }
  return temp;
} // subtract

Matrix Matrix::subtract(const Matrix & m) const {
  Matrix temp(*this);				      		// copy this matrix
  for (uint i = 0; i < rows; i++) {
    for (uint j = 0; j < cols; j++) {
      temp.matrix[i][j] -= m.matrix[i][j];			// all elements subtract other matrix m
    }
  }
  return temp;
} // subtract

Matrix Matrix::multiply(double s) const {
  Matrix temp(*this);					       	// copy this matrix
  for (uint i = 0; i < rows; i++) {
    for (uint j = 0; j < cols; j++) {
      temp.matrix[i][j] *= s;					// all elements multiply s
    }
  }
  return temp;
} // multiply

Matrix Matrix::multiply(const Matrix & m) const {
  Matrix temp(rows,m.cols);		       			// Create a new Matrix of the dot product
  for (uint i = 0; i < rows; i++) {
    for (uint j = 0; j < m.cols; j++) {
      for (int k = 0; k < cols; k++) {
	temp.matrix[i][j] += matrix[i][k] * m.matrix[k][j];	// multiply the matrix with another matrix 
      }
    }
  }
  return temp;
} // multiply

Matrix Matrix::divide(double s) const {
  Matrix temp(*this);	       				   	// copy this matrix
  for (uint i = 0; i < rows; i++) {
    for (uint j = 0; j < cols; j++) {
      temp.matrix[i][j] /= s;					// all elements divide s
    }
  }
  return temp;
} // divide

Matrix Matrix::t() const{
  Matrix temp(cols,rows);					// create a transpose matrix
  for (uint i = 0; i < cols; i++) {
    for (uint j = 0; j < rows; j++) {
      temp.matrix[i][j] = matrix[j][i];				// transpose the element
    }
  }
  return temp;
} // t

const uint Matrix::numRows() const {
  return rows;						       	// return rows
} // numRows

const uint Matrix::numCols() const {
  return cols;							// returns cols
} // numCols

double & Matrix::at(uint row, uint col) {
  return matrix[row][col];					// return the elements
} // at

const double & Matrix::at(uint row, uint col) const{
  return matrix[row][col];					// return the elements
} // at

Matrix & Matrix::operator=(const Matrix & m) {
  for (uint i = 0; i < rows; i++) {				// allocate 2nd dimention
    for (uint j = 0; j < cols; j++) {
      matrix[i][j] = m.matrix[i][j];				// copy elements to this matrix
    }
  }
  return *this;
} // operator =

Matrix & Matrix::operator=(const i_list & list) {
  auto row = list.begin();
  for (uint i = 0; i < rows; i++) {
    auto col = row[i].begin();
    for (uint j = 0; j < cols; ++j) {
      matrix[i][j] = col[j];					// copy elements to this matrix 
    }
  }
  return *this;
} // operator =

double & Matrix::operator()(uint row, uint col) {
  return Matrix::at(row, col);					// return function at
} // operator ()

Matrix Matrix::operator+(const double s) const{
  return Matrix::add(s);					// return function add double
} // operator +

Matrix Matrix::operator+(const Matrix & m) const{
  return Matrix::add(m);					// return function add matrix
} // operator +

Matrix Matrix::operator-(const double s) const{
  return Matrix::subtract(s);					// return function subtract double
} // operator -

Matrix Matrix::operator-(const Matrix & m) const{
  return Matrix::subtract(m);					// return function subtract matrix
} // operator -

Matrix Matrix::operator*(const double s) const{
  return Matrix::multiply(s);					// return function multiply double
} // operator *

Matrix Matrix::operator*(const Matrix & m) const{
  return Matrix::multiply(m);					// return function multiply matrix
} // operator *

Matrix Matrix::operator/(const double s) const{
  return Matrix::divide(s);					// return function divide double
} // operator /

Matrix Matrix::operator-() const {
  Matrix temp(*this);
  for (uint i = 0; i < temp.rows; i++) {
    for (uint j = 0; j < temp.cols; j++) {
      temp.matrix[i][j] *= -1;					// negate the element in the matrix
    }
  }
  return temp;
} // operator -(negate)

Matrix operator+(const double s, const Matrix & m) {
  Matrix temp(m);			       			// copy this matrix
  for (uint i = 0; i < m.numRows(); i++) {
    for (uint j = 0; j < m.numCols(); j++) {
		temp.at(i, j) += s;				// all elements add s
    }
  }
  return temp;
} // operator +

Matrix operator-(const double s, const Matrix & m) {
  Matrix temp(m);			       			// copy this matrix
  for (uint i = 0; i < m.numRows(); i++) {
    for (uint j = 0; j < m.numCols(); j++) {
      temp.at(i,j) = s - temp.at(i, j);	      			// all elements add s
    }
  }
  return temp;
} // operator -

Matrix operator*(const double s, const Matrix & m) {
  Matrix temp(m);			       			// copy this matrix
  for (uint i = 0; i < m.numRows(); i++) {
    for (uint j = 0; j < m.numCols(); j++) {
		temp.at(i, j) *= s;				// all elements add s
    }
  }
  return temp;
} // operator *

Matrix operator/(const double s, const Matrix & m) {
  Matrix temp(m);			       			// copy this matrix
  for (uint i = 0; i < m.numRows(); i++) {
    for (uint j = 0; j < m.numCols(); j++) {
		temp.at(i, j) = s/ temp.at(i, j);	 	// all elements add s
    }
  }
  return temp;
} // operator /

ostream & operator <<(ostream & os, const MatrixProject::Matrix m){
  for (uint i = 0; i < m.numRows(); i++) {
    os << "[";							
    for (uint j = 0; j < m.numCols(); j++) {
      os << m.at(i,j);						// print out the element
      if (j != m.numCols() - 1) {
	os << ",";	      	 				// example of the format:
      }								// [1,2,3]
    }								// [4,5,6]
    os << "]";
    if (i != m.numRows() - 1) {
      os << "\n";
    }
  }
  return os;
} // operator <<
