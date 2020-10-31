#pragma once

#include <libsoc_pwm.h>
#include <memory>
#include <utility>

namespace mandroid {
    enum class PinName {
        P9_22
    };

    inline std::pair<int, int> pinNameToChip(const PinName &pin) {
        switch(pin) {
            case PinName::P9_22:
                return std::make_pair<int, int>(1, 0);
            
            default:
                return std::make_pair<int, int>(-1, -1);
        }
    }
    
    class Servo {
        private:
            static float _dutyFromAngle(const int &angle);

            const std::shared_ptr<pwm> _pwm;
            std::shared_ptr<pwm> _generatePwm(
                const std::pair<int, int> &pinId
            ) const;
        
        public:
            Servo(const PinName &pin);

            void start() const;
            void setAngle(const int &angle) const;
            void stop() const;
    };
}
