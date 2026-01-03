#ifndef MATRIX_CPP
#define MATRIX_CPP

#include "matrix.h"
#include "lrucache.h"
/* Constructors */
template<typename T>
Matrix<T>::Matrix() : rows(0), columns(0) {}

template<typename T>
Matrix<T>::Matrix(int r, int c) : rows(r), columns(c) {
    mat.resize(r, vector<T>(c, 0));
}

template<typename T>
Matrix<T>::Matrix(const vector<vector<T>>& data) {
    mat = data;
    rows = data.size();
    columns = data[0].size();
}

/* Display */
template<typename T>
void Matrix<T>::displayVector() const {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++)
            cout << mat[i][j] << " ";
        cout << endl;
    }
}

template<typename T>
void Matrix<T>::noOfRows() const {
    cout << "No of Rows = " << rows << endl;
}

template<typename T>
void Matrix<T>::noOfColumns() const {
    cout << "No of Columns = " << columns << endl;
}

/* Getters */
template<typename T>
int Matrix<T>::Rows() const { return rows; }

template<typename T>
int Matrix<T>::Columns() const { return columns; }

template<typename T>
const vector<vector<T>>& Matrix<T>::data() const { return mat; }

/* Operators */
template<typename T>
vector<T>& Matrix<T>::operator[](int index) { return mat[index]; }

template<typename T>
const vector<T>& Matrix<T>::operator[](int index) const { return mat[index]; }

template<typename T>
T& Matrix<T>::operator()(int r, int c) { return mat[r][c]; }

template<typename T>
const T& Matrix<T>::operator()(int r, int c) const { return mat[r][c]; }

/* Identity */
template<typename T>
Matrix<double> Matrix<T>::identity(int n) {
    Matrix<double> I(n, n);
    for (int i = 0; i < n; i++)
        I[i][i] = 1.0;
    return I;
}

/* Inverse (Gauss-Jordan) */
template<typename T>
Matrix<T> Matrix<T>::inverseOfMatrix() {
    if (rows != columns) {
        cout << "Inverse not possible\n";
        return *this;
    }

    int n = rows;
    vector<vector<double>> aug(n, vector<double>(2 * n, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            aug[i][j] = mat[i][j];
        aug[i][i + n] = 1;
    }

    for (int i = 0; i < n; i++) {
        if (aug[i][i] == 0) {
            cout << "Singular Matrix\n";
            return *this;
        }

        double pivot = aug[i][i];
        for (int j = 0; j < 2 * n; j++)
            aug[i][j] /= pivot;

        for (int r = 0; r < n; r++) {
            if (r != i) {
                double factor = aug[r][i];
                for (int j = 0; j < 2 * n; j++)
                    aug[r][j] -= factor * aug[i][j];
            }
        }
    }

    vector<vector<double>> inv(n, vector<double>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            inv[i][j] = aug[i][j + n];

    return Matrix(inv);
}


#endif

