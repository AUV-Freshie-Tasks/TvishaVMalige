#include <iostream>
#include <vector>
#include "matrix.h"
#include "matrixOps.h"
//#include <pybind11/pybind11.h>
#include "LinearRegression.h"
//#include "eqnSolver.h"

//namespace py = pybind11;

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

	Matrix<double> m5 = m1.inverseOfMatrix();
	m5.displayVector();

	Matrix Inv =  m1.EqnSolver(b);
        Inv.displayVector();

//2*2
	vector<vector<double>> dataA = {
        {4, 3},
        {6, 3}
    };
    Matrix<double> X(dataA);
    vector<double> Y = {10, 12};

    cout << "Matrix X:" << endl;
    X.displayVector();

    Matrix<double> x1 = X.EqnSolver(Y);
vector<double> X1;
for (int i = 0; i < x1.Rows(); i++) {
    // Assuming the result is a column vector (n x 1), take column 0
    X1.push_back(x1(i, 0));
}

    cout << "Solution x1: [ ";
    for(double val : X1) cout << val << " ";
    cout << "]" << endl;

    //testing if cache works
    Matrix<double> x2 = X.EqnSolver(Y);

vector<double> X2;
for (int i = 0; i < x2.Rows(); i++) {
    // Assuming the result is a column vector (n x 1), take column 0
    X2.push_back(x2(i, 0));
}

    cout << "Solution x2: [ ";
    for(double val : X2) cout << val << " ";
    cout << "]" << endl;

   //cache miss
    vector<vector<double>> dataB = {
        {1, 2},
        {3, 4}
    };
    Matrix<double> B(dataB);
    /*Matrix<double> b2({{5}, {11}});
vector<double> B2;
for (int i = 0; i < b2.Rows(); i++) {
    // Assuming the result is a column vector (n x 1), take column 0
    B2.push_back(b2(i, 0));
}

for(double val : B2) cout << val << " ";
    cout << "]" << endl;
*/
    // Explicitly create the vector type first
Matrix<double> b2(vector<vector<double>>{{5}, {11}});

vector<double> B2;
for (int i = 0; i < b2.Rows(); i++) {
    // b2(i, 0) gets the value at row i, column 0
    B2.push_back(b2(i, 0));
}

cout << "Result: [ ";
for(double val : B2) cout << val << " ";
cout << "]" << endl;

    cout << "Matrix B:" << endl;
    B.displayVector();

   // Solve (This should trigger "Computing LU..." again)
    Matrix<double> x3 = B.EqnSolver(B2);

    vector<double> X3;
for (int i = 0; i < x3.Rows(); i++) {
    // Assuming the result is a column vector (n x 1), take column 0
    X3.push_back(x3(i, 0));
}


    cout << "Solution x3: [ ";
    for(double val : X3) cout << val << " ";
    cout << "]" << endl;




	int m = 3;
int n = 3;

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
