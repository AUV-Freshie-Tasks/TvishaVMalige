
#include <iostream>
#include <vector>
#include "matrix.h"

#include "lrucache.h"
#include "matrixOps.h"
//#include <pybind11/pybind11.h>
#include "LinearRegression.h"
//#include "eqnSolver.h"

//namespace py = pybind11;
static LRUMatrixCache luCache(3);   
int main() {

	vector<vector<double>> data = {{2,0,0}, {0,2,0}, {0,0,2}};
	vector<double> b = {1,6,4};
	Matrix<double>  m1(data);
	
	cout << "m1: " << endl;
	m1.displayVector();
	m1.noOfRows();
	m1.noOfColumns();

	Matrix<double> m2(data);

	cout << "m2: " << endl;
	m2.displayVector();

	Matrix<double> m3 = m1 + m2;
	Matrix<double> m4 = m1 * m2;
	
	cout << "m1 + m2: " << endl;
	m3.displayVector();

	cout << "m1 * m2: " << endl;
	m4.displayVector();
	
	cout << "Inverse: " << endl;
	Matrix<double> m5 = m1.inverseOfMatrix();
	m5.displayVector();

	
	Matrix<double> Inv =  m1.EqnSolver(b);
        Inv.displayVector();

cout << "\n===== LRU CACHE TEST =====\n";

vector<vector<double>> Adata = {
    {4, 3},
    {6, 3}
};

Matrix<double> A(Adata);

vector<double> b1 = {10, 12};
vector<double> b2 = {20, 24};

Matrix<double> xA1 = A.EqnSolver(b1); // MISS
Matrix<double> xA2 = A.EqnSolver(b2); // HIT

vector<vector<double>> Bdata = {
    {1, 2},
    {3, 4}
};

Matrix<double> B(Bdata);
vector<double> bB = {5, 11};

Matrix<double> xB = B.EqnSolver(bB);  // MISS

// Different matrix B






vector<double> b3 = {5, 11};

cout << "\nSolve B x = b3 (different matrix)\n";
Matrix<double> x3 = B.EqnSolver(b3);
x3.displayVector();

	
	int m = 2;
int n = 2;

vector<vector<double>> P(m, vector<double>(n));
    vector<double> Q(m);

    cout << "Enter P matrix (m x n):\n";
    for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++)
            cin >> P[i][j];

    cout << "Enter Y vector (m values):\n";
    for(int i = 0; i < m; i++)
        cin >> Q[i];

    LinearRegression lr(0.01, 5000);
    lr.fit(P, Q);

    vector<double> weights = lr.getWeights();

    cout << "\nFinal Weights:\n";
    for(double w : weights)
        cout << w << " ";
    cout << endl;
        return 0;

}

