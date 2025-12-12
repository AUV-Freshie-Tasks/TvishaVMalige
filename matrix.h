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

		
		
		/*T& operator()(int r, int c) {
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
    */

	Matrix inverseOfMatrix() {
    if (rows != columns) {
        cout << "Inverse of matrix can't be calculated";
        return Matrix(mat);
    }

    int n = rows;

   
    vector<vector<double>> aug(n, vector<double>(2 * n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            aug[i][j] = mat[i][j];   
        }
        for (int j = n; j < 2 * n; j++) {
                if(i == (j - n)) {
                        aug[i][j] = 1;
                }
                else {
                        aug[i][j] = 0;
                }
        }
    }


    for (int i = 0; i < n; i++) {


        if (aug[i][i] == 0) {
                float temp;

            for (int r = i + 1; r < n; r++) {
                if (aug[r][i] != 0) {
                    temp = aug[i][i];
                    aug[i][i] = aug[r][i];
                    aug[r][i] = temp;
                    break;
                }
            }
        }
 if (aug[i][i] == 0) {
            cout << "Singular Matrix"<< endl;
            return Matrix(mat);
        }


        double pivot = aug[i][i];
        for (int j = 0; j < 2 * n; j++) {
            aug[i][j] /= pivot;
        }


        for (int r = 0; r < n; r++) {
            if (r != i) {
                double factor = aug[r][i];
                for (int j = 0; j < 2 * n; j++) {
                    aug[r][j] -= factor * aug[i][j];
                }
            }
        }
    }


    vector<vector<double>> inv(n, vector<double>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            inv[i][j] = aug[i][j + n];
        }
    }

    return Matrix(inv);
}



};



#endif
