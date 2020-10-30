import Adafruit_BBIO.PWM as pwm

def pinNumberToStr(pin):
    if pin == 922:
        return 'P9_22'
    elif pin == 914:
        return 'P9_14'
    else:
        return ''

def start():
    #pinStr = pinNumberToStr(pinNumber)
    #print('Converted 0d' + str(pinNumber) + ' to ' + pinStr)
    pwm.start('P9_14', 97, 60)
    print('Initialized')

def setDuty(pinNumber, duty):
    pwm.set_duty_cycle(pinNumberToStr(pinNumber), duty)

def stop(pinNumber):
    pwm.stop(pinNumberToStr(pinNumber))
    pwm.cleanup()
