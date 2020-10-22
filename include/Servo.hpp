#pragma once

#include <GpioControl.hpp>

namespace mandroid {
    class Servo {
        private:
            const PwmPin _pin;
        
        public:
            Servo(PinName pin);

            void setAngle(int angle) const;
            void start() const;
            void stop() const;
    };
}
