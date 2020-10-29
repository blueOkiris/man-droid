#pragma once

#include <string>

namespace mandroid {
    enum class PinName {
        P9_22    
    };
    
    inline std::string pinNameStr(const PinName &pin) {
        switch(pin) {
            case PinName::P9_22:
                return "P9_22";
            
            default:
                return "";
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
            const std::string _pinName;
        
        public:
            Servo(PinName pin);

            void start() const;
            void setAngle(const int &angle) const;
            void stop() const;
    };
}
