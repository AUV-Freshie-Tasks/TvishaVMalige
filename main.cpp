#include <iostream>
#include <vector>
#include "matrix.h"
#include "matrixOps.h"
#include "LinearRegression.h"

int main() {

	vector<vector<double>> data = {{1,0,0}, {0,1,0}, {0,0,1}};

	Matrix<double>  m1(data);

	//m1.displayVector();
	//m1.noOfRows();
	//m1.noOfColumns();

	Matrix<double> m2(data);

	//Matrix<double> m3 = m1 + m2;
	//Matrix<double> m4 = m1 * m2;

	//m3.displayVector();
	//m4.displayVector();

	Matrix<double> m5 = m1.inverseOfMatrix();
	m5.displayVector();

	vector<vector<double>> data2 = {{1,1,1},{1,1,1},{1,1,1}};

	Matrix<double> m6(data2);
	Matrix<double> m7 = m6.inverseOfMatrix();
	m7.displayVector();


	int m = 2;
int n = 2;

vector<vector<double>> P(m, vector<double>(n));
    vector<double> Y(m);

    cout << "Enter P matrix (m x n):\n";
    for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++)
            cin >> P[i][j];

    cout << "Enter Y vector (m values):\n";
    for(int i = 0; i < m; i++)
        cin >> Y[i];

    LinearRegression lr(0.01, 5000);
    lr.fit(P, Y);

    vector<double> weights = lr.getWeights();

    cout << "\nFinal Weights:\n";
    for(double w : weights)
        cout << w << " ";
    cout << endl;


        return 0;

}
