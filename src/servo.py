import Adafruit_BBIO.PWM as pwm

def dutyFromAngle(angle):
    dutyMin = 3
    dutyMax = 14.5
    dutySpan = dutyMax - dutyMin

def start(pin):
    pwm.start(pin, 97, 60)

def setAngle(pin, angle):
    duty = dutyFromAngle(angle)
    pwm.set_duty_cycle(pin, duty)

def stop(pin):
    pwm.stop(pin)
    pwm.cleanup()