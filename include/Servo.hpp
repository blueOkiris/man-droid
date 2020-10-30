#pragma once

#include <memory>
#include <utility>

namespace mandroid {
    enum class PinName {
        P9_22
    };

    inline std::pair<int, int> pinNameToChip(const PinName &pin) {
        switch(pin) {
            case PinName::P9_22:
                return std::make_pair<int, int>(0, 0);
            
            default:
                return std::make_pair<int, int>(-1, -1);
        }
    }
    
    inline float dutyFromAngle(const int &angle) {
        const auto dutyMin = 3;
        const auto dutyMax = 14.5;
        const auto dutySpan = dutyMax - dutyMin;
        return 100 - ((((float) angle) / 180) * dutySpan + dutyMin);
    }
    
    class Servo {
        private:
            const std::shared_ptr<pwm> _pwm;

            std::shared_ptr<pwm> _generatePwm(const std::pair<int, int> &pinId);
        
        public:
            Servo(const PinName &pin);

            void start() const;
            void setAngle(const int &angle) const;
            void stop() const;
    };
}
