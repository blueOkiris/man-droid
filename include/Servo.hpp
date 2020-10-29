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
            const PinName _pin;
        
        public:
            Servo(PinName pin);

            void setAngle(int angle) const;
            void start() const;
            void stop() const;
    };
}
