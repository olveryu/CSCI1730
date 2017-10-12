
#ifndef CS1730_VECTOR_H
#define CS1730_VECTOR_H

#include <iostream>
#include <initializer_list>
#include <cstdlib>

using std::ostream;
using std::initializer_list;

namespace cs1730 {

  /**
   * The `Vector` class stores and operates on numeric vectors of element type 
   * `double`.
   */
  class Vector {
    
    /** Dimension / length of the vector. */
    size_t dim;

    /** Pointer to internal array for vector. */
    double * x = nullptr;

  public:
    
    /**
     * Constructs a new `Vector` object. Each element is initialized to 0.
     * @param dim  length of vector
     */
    Vector(size_t dim);

    /**
     * Construct a new `Vector` object as a copy of another `Vector` object.
     * @param v  vector to copy
     */
     Vector(const Vector & v);

    /**
     * Constructs a new `Vector` object from an initializer list.
     * @param l  initializer list
     */
    Vector(const initializer_list<double> & l);

    /**
     * Destructs the `Vector` object. 
     */
    ~Vector();

    /**
     * Returns the element at index `i`.
     * @param i  desired index
     */
    double & at(size_t i);

    /**
     * Returns the element at index `i`. This version is for const objects.
     * @param i  desired index
     */
    double at(size_t i) const;

    /**
     * Returns the size (dimension or length) of this `Vector`.
     */
    size_t size() const;

    /**
     * Returns the sum of this `Vector` and some scaler `s`.
     * @param s  scaler to add
     */
    Vector operator+(const double s) const;

    /**
     * Returns the sum of this `Vector` and another `Vector` of the same length.
     * @param v  vector to add
     */
    Vector operator+(const Vector & v) const;

    /**
     * Returns the difference of this `Vector` and some scaler `s`.
     * @param s  scaler to subtract
     */
    Vector operator-(const double s) const;

    /**
     * Returns the difference of this `Vector` and another `Vector` of the same 
     * length.
     * @param v  vector to subtract
     */
    Vector operator-(const Vector & v) const;

    /**
     * Copy assignment operator.
     * @param v  vector to copy
     */
    Vector & operator=(const Vector & v);

  }; // Vector

} // cs1730

cs1730::Vector operator+(double s, const cs1730::Vector & v);
cs1730::Vector operator-(double s, const cs1730::Vector & v);
ostream & operator<<(ostream & os, const cs1730::Vector & v);

#endif

