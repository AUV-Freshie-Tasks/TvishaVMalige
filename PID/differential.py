class Differential:
    def __init__(self, kd):
        self.kd = kd
        self.last_error = 0.0

    def calculate(self, error, dt):
      
            
   
            
        
        derivative = (error - self.last_error) / dt
        self.last_error = error
        return self.kd * derivative
