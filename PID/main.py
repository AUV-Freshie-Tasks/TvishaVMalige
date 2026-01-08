import time

dt = 0.1  

from proportional import Proportional
from integral import Integral
from differential import Differential

class PIDController:
    def __init__(self, kp, ki, kd):
        
        self.p = Proportional(kp)
        self.i = Integral(ki)
        self.d = Differential(kd)
        

    def update(self, setpoint, measured_value, dt):    
        error = setpoint - measured_value
        p_out = self.p.calculate(error)
        i_out = self.i.calculate(error, dt)
        d_out = self.d.calculate(error, dt)
        
        
        return p_out + i_out + d_out


pid = PIDController(0.001, 0.001, 0.001)

target = float(input("Enter set point: "))  
current = float(input("Enter initial point: "))

for _ in range(1000):
    output = pid.update(target, current, dt)

    
    current += output 

    print(f"Current Value: {current:.2f} | Output: {output:.2f}")


