#ifndef LINEAR_REGRESSION_H
#define LINEAR_REGRESSION_H

#include <vector>

class LinearRegression {
private:
    int m; 
    int n; 
    double alpha; 
    int iterations;

    std::vector<std::vector<double>> X; 
    std::vector<double> Y;              
    std::vector<double> W;              
	
    double b = 0.0;

public:
    LinearRegression(double lr = 0.01, int iters = 1000);

    void fit(const std::vector<std::vector<double>>& X,
             const std::vector<double>& Y);

    std::vector<double> predict(const std::vector<std::vector<double>>& Xtest);

    std::vector<double> getWeights() const;
    double getBias() const;
};

#endif

