#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <cmath>


using namespace std;

template <typename T>
class Matrix {
private:
    int rows;
    int columns;
    vector<vector<T>> mat;

public:
    // Constructors
    Matrix();
    Matrix(int r, int c);
    Matrix(const vector<vector<T>>& data);

    // Display & info
    void displayVector() const;
    void noOfRows() const;
    void noOfColumns() const;

    // Getters
    int Rows() const;
    int Columns() const;
    const vector<vector<T>>& data() const;

    // Operators
    vector<T>& operator[](int index);
    const vector<T>& operator[](int index) const;

    T& operator()(int r, int c);
    const T& operator()(int r, int c) const;

    // Matrix operations
    static Matrix<double> identity(int n);
    Matrix inverseOfMatrix();
    

Matrix<double> EqnSolver(const vector<double>& b);

};

#include "matrix.cpp"   // REQUIRED for templates

#endif

