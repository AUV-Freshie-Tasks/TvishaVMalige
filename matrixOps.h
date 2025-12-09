#ifndef MATRIX_OPS_H
#define MATRIX_OPS_H

#include <stdexcept>
#include "matrix.h"

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

#endif

