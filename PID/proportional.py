class Proportional:
    def __init__(self, kp):
        self.kp = kp

    def calculate(self, error):
        return self.kp * error
