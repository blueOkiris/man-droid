#pragma once

#include <string>

namespace mandroid {
    enum class PwmPinName {
        P9_22
    };

    struct PwmPin {
        const std::string exportFileName;
        const std::string chipId;
        const std::string periodFileName;
        const std::string dutyFileName;
        const std::string enableFileName;
        const std::string unExportFileName;
    };

    inline PwmPin pinFromName(const PwmPinName &pin) {
        switch(pin) {
            case PwmPinName::P9_22:
                return { 
                    "/sys/class/pwm/pwmchip1/export", "0",
                    "/sys/class/pwm/pwmchip1/pwm-1:0/period",
                    "/sys/class/pwm/pwmchip1/pwm-1:0/duty_cycle",
                    "/sys/class/pwm/pwmchip1/pwm-1:0/enable",
                    "/sys/class/pwm/pwmchip1/unexport"
                };

            default:
                return { "", "", "", "", "" };
        }
    }

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
