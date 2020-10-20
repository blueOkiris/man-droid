#pragma once

#include <GpioControl.hpp>

namespace mandroid {
    class Servo {
        private:
            PwmPin _pin;
        
        public:
            Servo(PinName pin);

            void setAngle(int angle);
            void start();
            void stop();
    };
}
