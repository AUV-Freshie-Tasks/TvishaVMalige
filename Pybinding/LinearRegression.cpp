#include "LinearRegression.h"
#include <iostream>

LinearRegression::LinearRegression(double lr, int iters) {
    alpha = lr;
    iterations = iters;
}

void LinearRegression::fit(const std::vector<std::vector<double>>& Xdata,
                           const std::vector<double>& Ydata) {
    X = Xdata;
    Y = Ydata;

    m = X.size();
    n = X[0].size();

    W = std::vector<double>(n, 0.0); 

    for(int it = 0; it < iterations; it++) {
        
        std::vector<double> pred(m, 0.0);
        for(int i = 0; i < m; i++)
            for(int j = 0; j < n; j++)
                pred[i] += X[i][j] * W[j];

        
        std::vector<double> grad(n, 0.0);
        for(int j = 0; j < n; j++) {
            for(int i = 0; i < m; i++)
                grad[j] += (pred[i] - Y[i]) * X[i][j];
            grad[j] /= m;
        }

       
        for(int j = 0; j < n; j++)
            W[j] -= alpha * grad[j];
    }
}

std::vector<double> LinearRegression::predict(const std::vector<std::vector<double>>& Xtest) {
    int mtest = Xtest.size();
    std::vector<double> result(mtest, 0.0);

    for(int i = 0; i < mtest; i++)
        for(int j = 0; j < n; j++)
            result[i] += Xtest[i][j] * W[j];

    return result;
}

std::vector<double> LinearRegression::getWeights() const {
    return W;
}


