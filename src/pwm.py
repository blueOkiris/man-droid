import Adafruit_BBIO.PWM as pwm

def pinNumberToStr(pin):
    if pin == 922:
        return 'P9_22'
    else:
        return ''

def start(pinNumber):
    pwm.start(pinNumberToStr(pinNumber, 97, 60))

def setDuty(pinNumber, duty):
    pwm.set_duty_cycle(pinNumberToStr(pinNumber), duty)

def stop(pinNumber):
    pwm.stop(pinNumberToStr(pinNumber))
    pwm.cleanup()
