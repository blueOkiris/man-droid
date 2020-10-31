#pragma once

#include <tuple>
#include <string>

namespace mandroid {
    enum class PinName {
        P9_22
    };

    inline std::tuple<std::string, std::string, std::string> pinNameToChip(
            const PinName &pin) {
        switch(pin) {
            case PinName::P9_22:
                return std::make_tuple<std::string, std::string, std::string>(
                    "pwmchip1", "pwm-1:0", "0"
                );
            
            default:
                return std::make_tuple<std::string, std::string, std::string>(
                    "", "", ""
                );
        }
    }
    
    class Servo {
        private:
            static float _dutyFromAngle(const int &angle);
            const std::tuple<std::string, std::string, std::string> _pinId;
        
        public:
            Servo(const PinName &pin);

            void start() const;
            void setAngle(const int &angle) const;
            void stop() const;
    };
}
