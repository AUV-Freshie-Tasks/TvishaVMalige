#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
using namespace std;

template <typename T> 

class Matrix {
	private:
		int rows;
		int columns;
		vector<vector<T>> mat;

	public:
		Matrix(const vector<vector<T>>& data) {
		
			mat = data;
			rows = data.size();
			columns = data[0].size();
		}

		void displayVector() {
                        for (int i = 0; i < rows; i++) {
                                for (int j = 0; j < columns; j++) {
                                        cout << mat[i][j] << " ";
                                }
                                cout << endl;
                                //cout <<"running" << endl;
                        }

		
                }

                void noOfRows() {
                cout << "No of Rows = " << rows << endl;
		
                }

                void noOfColumns() {
                cout << "No of Columns = " << columns << endl;
		
                }

		int Rows() const { return rows;}

		int Columns() const {return columns;}

		const vector<vector<T>>& data() const {return mat;}

		Matrix<T> inverseOfMatrix() const;
		
		T& operator()(int r, int c) {
        return mat[r][c];
    }
    const T& operator()(int r, int c) const {
        return mat[r][c];
    }

		static Matrix<double> identity(int n) {
        Matrix<double> I;
        for(int i=0; i<n; i++) {
		I[i][i] = 1.0;
	}
        return I;
    }


};

#include "matrixInversion.h"

#endif
