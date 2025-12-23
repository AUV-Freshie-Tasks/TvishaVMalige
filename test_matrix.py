import matrix_module

# Test 1: Initialize and Display
# Uses Matrix(const vector<vector<T>>& data)
data = [[2.0, 1.0], [1.0, 2.0]]
m = matrix_module.MatrixDouble(data)
print("Matrix M:")
m.displayVector() #

# Test 2: Matrix Multiplication
# Uses operator* from matrixOps.h
identity = matrix_module.MatrixDouble.identity(2) #
result = m * identity 
print("\nM * I result (should be same as M):")
result.displayVector()

# Test 3: LU Decomposition and Caching
# Uses computeLU standalone function
print("\nTesting LU Decomposition:")
lu = matrix_module.computeLU(m) #
print("L Matrix:")
lu.lmat.displayVector() #

# Test 4: Solving Equations (Ax = b)
# Uses EqnSolver
b = [5.0, 4.0]
x = m.EqnSolver(b) #
print("\nSolution for Ax = [5, 4]:")
x.displayVector()
