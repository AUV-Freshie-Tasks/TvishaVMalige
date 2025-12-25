class Integral:
    def __init__(self, ki):
        self.ki = ki
        self.integral_sum = 0.0

    def calculate(self, error, dt):
        self.integral_sum += error * dt
        return self.ki * self.integral_sum
