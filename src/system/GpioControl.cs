using System;
using System.IO;

namespace mandroid {
    enum PinName {
        PwmP9_22 = 0
    }

    interface GpioPin {
        void Init();
        void On();
        void Off();
        void DeInit();
    }

    class PwmPin : GpioPin {
        private PinName pin;
        private long dutyNs, periodNs;
        
        public PwmPin(PinName pin, long dutyNs, long periodNs) {
            this.pin = pin;
            this.dutyNs = dutyNs;
            this.periodNs = periodNs;

            if((int) pin > 1) {
                throw new NotAPwmPinException(pin);
            }

            if(dutyNs >= periodNs) {
                throw new DutyCycleTooSmallException(dutyNs, periodNs);
            }
        }

        public void Init() {
            var pinFolder = pwmPinFolder(pin);
            var chipFolder = pwmPinChipFolder(pin);
            var pinId = pwmPinChipId(pin);

            if(!Directory.Exists(pinFolder)) {
                // echo 0 > /sys/class/pwmchip1/export
                File.WriteAllText(chipFolder + "/export", pinId + "\n");
            }
            File.WriteAllText(pinFolder + "/period", periodNs + "\n");
            File.WriteAllText(pinFolder + "/duty_cycle", dutyNs + "\n");
        }

        public void On() {
            var pinFolder = pwmPinFolder(pin);
            File.WriteAllText(pinFolder + "/enable", "1\n");
        }

        public void Off() {
            var pinFolder = pwmPinFolder(pin);
            File.WriteAllText(pinFolder + "/enable", "0\n");
        }

        public void DeInit() {
            Off();
            
            var chipFolder = pwmPinChipFolder(pin);
            var pinId = pwmPinChipId(pin);
            File.WriteAllText(chipFolder + "/unexport", pinId);
        }

        private static string pwmPinChipFolder(PinName pin) {
            switch(pin) {
                case PinName.PwmP9_22:
                    return "/sys/class/pwmchip1/pwm-1:0/";
                
                default:
                    return "";
            }
        }

        private static string pwmPinFolder(PinName pin) {
            switch(pin) {
                case PinName.PwmP9_22:
                    return "/sys/class/pwmchip1/pwm-1:0/";
                
                default:
                    return "";
            }
        }

        private static string pwmPinChipId(PinName pin) {
            switch(pin) {
                case PinName.PwmP9_22:
                    return "0";
                
                default:
                    return "1";
            }
        }
    }

    class NotAPwmPinException : Exception {
        public NotAPwmPinException(PinName pin) :
                base("Provided pin '" + pin + "' is not a pwm pin") {
        }
    }

    class DutyCycleTooSmallException : Exception {
        public DutyCycleTooSmallException(long dutyNs, long periodNs) :
                base(
                    "Duty cycle '" + dutyNs
                    + "' must be lower than period '" + periodNs
                ) {
        }
    }
}
 
