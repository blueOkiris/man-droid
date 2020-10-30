#pragma once

#include <string>

namespace mandroid {
    enum class PinName {
        P9_22 = 922
    };
    
    inline float dutyFromAngle(const int &angle) {
        const auto dutyMin = 3;
        const auto dutyMax = 14.5;
        const auto dutySpan = dutyMax - dutyMin;
        return 100 - ((((float) angle) / 180) * dutySpan + dutyMin);
    }
    
    class Servo {
        private:
            const int _pinNumber;
        
        public:
            Servo(PinName pin);

            void start() const;
            void setAngle(const int &angle) const;
            void stop() const;
    };
}
