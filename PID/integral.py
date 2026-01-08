class Integral:
    def __init__(self, ki):
        self.ki = ki
        self.integral_sum = 0.0
        self.iter = 0

    def calculate(self, error, dt):
        self.iter += 1
        self.integral_sum += (error * dt)/self.iter

        return self.ki * self.integral_sum
