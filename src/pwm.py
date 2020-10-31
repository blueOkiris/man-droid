import Adafruit_BBIO.PWM as pwm
import sys

pwm.start(sys.argv[1], 97, 60)
