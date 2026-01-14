import math

class LogisticRegression:
    def __init__(self, iterations, lr):
        self.iterations = iterations
        self.lr = lr
        self.w = None
        self.b = 0.0
        self.tol = 1e-5
        
        
        print(self.tol)

    def sigmoid(self, z):
        temp =  1 / (1 + math.exp(-z))
        return temp

    def fit(self, x, y):
        
        m = len(x)
        #print(m)
        n = len(x[0])
        
        
        self.w = [0.0] * n
        self.b = 0.0
 
        for _ in range(self.iterations):
            
            for i in range(m):
                
                z = sum(self.w[j] * x[i][j] for j in range(n)) + self.b
                #print(self.b)

                #print(self.w)
                y_pred = self.sigmoid(z)
                
                temp = y[i]

                self.loss = 0.0
                self.lossB = 0.0

                if(y_pred > self.tol):
                    for j in range(n):
                        self.loss = (y_pred - temp)*x[i][j]
                        self.lossB = (y_pred - temp)
                        #print(self.loss)
                else:
                    y_pred = self.tol

                #print(y_pred, " ", y[i])
                #print(self.loss);

                for j in range(n):
                    self.w[j] -= self.lr * self.loss
                    if(_ % 200 == 0):
                        print("w: ", self.w[j]) 
                    self.b -= self.lr * self.lossB
                    if(_ % 200 == 0):
                        print("b: ", self.b)
           

    def predict(self, x):
        predictions = []
        for row in x:
            z = sum(self.w[j] * row[j] for j in range(len(self.w))) + self.b
            
            predictions.append(1 if self.sigmoid(z) >= 0.5 else 0)
        return predictions

# Execution

data = [
        [0.5],
        [1.0],
        [1.2],
        [1.6],
        [2.0],
        [2.5],
        [2.9],
        [5.6],
        [1.4],
        [2.5]
    ]
y = [0, 0, 0, 0, 1, 1, 1, 1, 0, 1]

lR = LogisticRegression(iterations=5000, lr=0.01)
lR.fit(data, y)

preds = lR.predict(data)
print(f"Weights: {lR.w}")
print(f"Predictions: {preds}")
        


