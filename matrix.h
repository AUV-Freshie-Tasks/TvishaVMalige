#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <optional>
#include <functional>
#include <cmath>
using namespace std;

template <typename T> 

class Matrix {
	private:
		int rows;
		int columns;
		vector<vector<T>> mat;

	public:
		Matrix() : rows(0), columns(0) {}

    // --- FIX 2: Add Sized Constructor ---
    // Needed to create the L, U, and Identity matrices with specific dimensions.
    Matrix(int r, int c) {
        rows = r;
        columns = c;
        // Create r rows, each with c columns, initialized to 0
        mat.resize(r, vector<T>(c));
    }
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

vector<T>& operator[](int index) {
        return mat[index];
    }

    const vector<T>& operator[](int index) const {
        return mat[index];
    }		
		
	T& operator()(int r, int c) {
        return mat[r][c];
    }
    const T& operator()(int r, int c) const {
        return mat[r][c];
    }

	static Matrix<double> identity(int n) {
        // Use the new Sized Constructor (Fix 2) to allocate memory first!
        Matrix<double> I(n, n); 
        
        for (int i = 0; i < n; i++) {
            // Now works because operator[] (Fix 3) is defined
            I[i][i] = 1.0; 
        }
        return I;
    }
   

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

Matrix EqnSolver(const vector<double>& b) {
vector<vector<double>> umat(rows, vector<double>(columns));
vector<vector<double>> lmat(rows, vector<double>(columns));
vector<vector<double>> y(rows, vector<double>(1));
vector<vector<double>> x(rows, vector<double>(1));
umat = mat;
    for (int j = 0; j < columns; j++) {

        for (int i = 0; i < rows; i++) {
            if (i == j) {
                lmat[i][j] = 1;
            }

            if (i > j) {
                double factor = umat[i][j] / umat[j][j];

                lmat[i][j] = factor;
                for (int k = 0; k < columns; k++) {
                    umat[i][k] -= factor * umat[j][k];
                }
                }
        }
    }

    for (int i = 0; i < rows; i++) {
        double sum = b[i];

        for (int j = 0; j < i; j++) {
            sum -= lmat[i][j] * y[j][0];
        }


        y[i][0] = sum;
    }

    for (int i = rows-1; i >= 0; i--) {
        double sum = y[i][0];

        for (int j = i+1; j < columns; j++) {
            sum -= umat[i][j] * x[j][0];
        }

        x[i][0] = sum/umat[i][i];
    }
        return Matrix(x);
}

};

struct LUResult {
    Matrix<double> lmat;
    Matrix<double> umat;
};

class LRUMatrixCache {
private:
    int capacity;
    std::list<std::pair<int, LUResult>> cacheList;
    std::unordered_map<int, std::list<std::pair<int, LUResult>>::iterator> cacheMap;

    // Move existing entry to front -> Most Recently Used
    void moveToFront(int key) {
        cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
    }

public:
    LRUMatrixCache(int cap) : capacity(cap) {}

    std::optional<LUResult> get(int key) {
        if (cacheMap.find(key) == cacheMap.end())
            return std::nullopt;
        moveToFront(key);
        return cacheMap[key]->second;
    }

    void put(int key, const LUResult& value) {
        if (cacheMap.find(key) != cacheMap.end()) {
            moveToFront(key);
            cacheMap[key]->second = value;
            return;
        }
        if (cacheList.size() == capacity) {
            cacheMap.erase(cacheList.back().first);
            cacheList.pop_back();
        }
        cacheList.emplace_front(key, value);
        cacheMap[key] = cacheList.begin();
    }
};

int hashMatrix(const Matrix<double>& A) {
    long long h = 0;
    for(int i = 0; i < A.Rows(); i++)
        for(int j = 0; j < A.Columns(); j++)
            h = h * 131 + std::hash<double>()(A(i,j));
    return (int)h;
}

LUResult computeLU(const Matrix<double>& A) {
	
static LRUMatrixCache luCache(10);
    int n = A.Rows();
    int key = hashMatrix(A);

    // Check cache first
    auto cached = luCache.get(key);
    if (cached.has_value())
        return cached.value();

    // Compute new LU
    Matrix<double> L = Matrix<double>::identity(n);
    Matrix<double> U(n, n);

    for(int j = 0; j < n; j++) {
        for(int i = 0; i <= j; i++) {
            double sum = 0;
            for(int k = 0; k < i; k++)
                sum += L(i,k) * U(k,j);
            U(i,j) = A(i,j) - sum;
        }
        for(int i = j+1; i < n; i++) {
            double sum = 0;
            for(int k = 0; k < j; k++)
                sum += L(i,k) * U(k,j);
            L(i,j) = (A(i,j) - sum) / U(j,j);
        }
    }

    LUResult result{L, U};
    luCache.put(key, result);
    return result;
}




#endif
