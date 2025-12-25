import time

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


pid = PIDController(1.0, 0.1, 0.05)

target = 100.0  
current = 0.0
dt = 0.1         

for _ in range(20):
    output = pid.update(target, current, dt)

    
    current += (output * 0.1)

    print(f"Current Value: {current:.2f} | Output: {output:.2f}")
