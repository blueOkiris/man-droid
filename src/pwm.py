import Adafruit_BBIO.PWM as pwm
import sys

try:
    pwm.start(sys.argv[1], 97, 60)
finally:
    # Try again
    try:
        pwm.start(sys.argv[1], 97, 60)
    finally:
        print('Failed to initialize Servo pwm. Sorry!')
