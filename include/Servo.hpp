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
    
    class Servo {
        private:
            const std::string _pinName;
        
        public:
            Servo(PinName pin);

            void start() const;
            void setAngle(int angle) const;
            void stop() const;
    };
}
