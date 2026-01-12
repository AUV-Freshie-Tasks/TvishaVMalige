#include "LinearRegression.h"
#include <iostream>

using namespace std;

LinearRegression::LinearRegression(double lr, int iters) {
    alpha = lr;
    iterations = iters;
}

void LinearRegression::fit(const vector<vector<double>>& Xdata,
                           const vector<double>& Ydata) {
    X = Xdata;
    Y = Ydata;

    m = X.size();
    n = X[0].size();

    W = vector<double>(n, 0.0); 

    b = 0.0;
   
   

    for(int it = 0; it < iterations; it++) {
  	double totalError = 0.0;

        vector<double> pred(m, 0.0);
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                pred[i] += X[i][j] * W[j];
		}
	    pred[i] += b;

            double diff = pred[i] - Ydata[i];
            totalError += diff * diff;
	    //cout << "Error: " << totalError/(2*m) << endl;

	}
		


        vector<double> grad(n, 0.0);
	double error = 0.0;
	double gradB = 0.0;

        for(int j = 0; j < n; j++) {
            for(int i = 0; i < m; i++) {
                grad[j] += (pred[i] - Y[i]) * X[i][j];
	    }
            grad[j] /= m;   
        }

	for(int i = 0; i < m; i++) {
		error = pred[i] - Y[i];
		gradB += error;
	}


        for(int j = 0; j < n; j++)
            W[j] -= alpha * (grad[j]);
	
	b -= alpha * (gradB /m);
    	cout << "B Error: " << b << endl;
    }
}

vector<double> LinearRegression::predict(const vector<vector<double>>& Xtest) {
    int mtest = Xtest.size();
    vector<double> result(mtest, 0.0);

    for(int i = 0; i < mtest; i++)
        for(int j = 0; j < n; j++)
            result[i] += Xtest[i][j] * W[j];

    return result;
}

vector<double> LinearRegression::getWeights() const {
    return W;
}

double LinearRegression::getBias() const {
	return b;
}
