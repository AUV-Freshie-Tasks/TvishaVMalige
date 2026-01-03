#ifndef MATRIX_OPS_H
#define MATRIX_OPS_H

#include <stdexcept>
#include "matrix.h"
#include "lrucache.h"

template <typename T>
Matrix<T> operator+(const Matrix<T>& A, const Matrix<T>& B) {
    
    if (A.Rows() != B.Rows() ||
        A.Columns() != B.Columns())
        throw runtime_error("Matrix size mismatch");

    int rows = A.Rows();
    int cols = A.Columns();

    vector<vector<T>> result(rows, vector<T>(cols));

    const auto& a = A.data();
    const auto& b = B.data();

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result[i][j] = a[i][j] + b[i][j];

    return Matrix<T>(result);
}

template <typename T>
Matrix<T> operator*(const Matrix<T>& A, const Matrix<T>& B) {
    
    if (A.Columns() != B.Rows())
        throw runtime_error("Matrix size mismatch");

    int rows = A.Rows();
    int cols = B.Columns();
    int mid = A.Columns();

    vector<vector<T>> result(rows, vector<T>(cols, 0));

    const auto& a = A.data();
    const auto& b = B.data();

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            for (int k = 0; k < mid; k++)
                result[i][j] += a[i][k] * b[k][j];

    return Matrix<T>(result);
}


template <typename T>
Matrix<double> Matrix<T>::EqnSolver(const vector<double>& b) {

    LUResult lu = computeLU(*this);
    Matrix<double>& L = lu.lmat;
    Matrix<double>& U = lu.umat;

    int n = Rows();
    vector<double> y(n), x(n);

    for (int i = 0; i < n; i++) {
        y[i] = b[i];
        for (int j = 0; j < i; j++)
            y[i] -= L(i,j) * y[j];
    }

    for (int i = n - 1; i >= 0; i--) {
        x[i] = y[i];
        for (int j = i + 1; j < n; j++)
            x[i] -= U(i,j) * x[j];
        x[i] /= U(i,i);
    }

    vector<vector<double>> res(n, vector<double>(1));
    for (int i = 0; i < n; i++)
        res[i][0] = x[i];

    return Matrix<double>(res);
}
#endif


