
#include "Vector.h"

using cs1730::Vector;

Vector::Vector(size_t dim) {
  this->dim = dim;
  this->x = new double [dim];
  for (size_t i = 0; i < dim; ++i) x[i] = 0;
} // Vector

Vector::Vector(const Vector & v) {
  this->dim = v.dim;
  this->x = new double [dim];
  for (size_t i = 0; i < dim; ++i) x[i] = v.at(i);
  // for (size_t i = 0; i < dim; ++i) *(x+i) = v.at(i);
} // Vector

Vector::Vector(const initializer_list<double> & l) {
  this->dim = l.size();
  this->x = new double [dim];
  auto list = l.begin();
  for (size_t i = 0; i < dim; ++i) x[i] = list[i];
} // Vector

Vector::~Vector() {
  delete [] this->x;
} // ~Vector

double & Vector::at(size_t i) {
  return x[i];
} // at

double Vector::at(size_t i) const {
  return x[i];
} // at

size_t Vector::size() const {
  return dim;
} // size

Vector Vector::operator+(const double s) const {
  Vector ret (*this); // copy this vector
  for (size_t i = 0; i < dim; ++i) ret.at(i) += s;
  return ret;
} // operator+

Vector Vector::operator+(const Vector & v) const {
  Vector ret (*this); // copy this vector
  for (size_t i = 0; i < dim; ++i) ret.at(i) += v.at(i);
  return ret;
} // operator+

Vector Vector::operator-(const double s) const {
  Vector ret (*this); // copy this vector
  for (size_t i = 0; i < dim; ++i) ret.at(i) -= s;
  return ret;
} // operator-

Vector Vector::operator-(const Vector & v) const {
  Vector ret (*this); // copy this vector
  for (size_t i = 0; i < dim; ++i) ret.at(i) -= v.at(i);
  return ret;
} // operator-

Vector & Vector::operator=(const Vector & v) {
  for (size_t i = 0; i < dim; ++i) x[i] = v.at(i);
  return *this;
} // operator=

Vector operator+(const double s, const Vector & v) {
  Vector ret (v); // copy this vector
  for (size_t i = 0; i < ret.size(); ++i) ret.at(i) += s;
  return ret;
} // operator+

Vector operator-(const double s, const Vector & v) {
  Vector ret (v); // copy this vector
  for (size_t i = 0; i < ret.size(); ++i) ret.at(i) = s - ret.at(i);
  return ret;
} // operator-

ostream & operator<<(ostream & os, const cs1730::Vector & v) {
  os << "Vector(";
  for (size_t i = 0; i < v.size(); ++i) {
    os << v.at(i);
    if (i != v.size() - 1) os << ", ";
  } // for
  os << ")";
  return os;
} // operator<<
