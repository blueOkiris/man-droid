#pragma once

#include <string>
#include <PwmPins.hpp>

namespace mandroid {
    class Servo {
        private:
            static float _dutyFromAngle(const int &angle);
            const PwmPin _pin;
        
        public:
            Servo(const PwmPinName &pinName);

            void start() const;
            void setAngle(const int &angle) const;
            void stop() const;
    };
}
