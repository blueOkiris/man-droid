#pragma once

#include <chrono>
#include <string>

namespace mandroid {
    enum class PinName {
        Pwm_P9_22 = 0
    };

    class GpioPin {
        public:
            virtual void init() = 0;
            virtual void on() = 0;
            virtual void off() = 0;
            virtual bool isRunning() = 0;
            virtual void deInit() = 0;
    };

    class PwmPin : public GpioPin {
        private:
            const PinName _pin;
            std::chrono::nanoseconds _duty, _period;
            bool _running;

            static std::string _pwmPinChipFolder(const PinName &pin);
            static std::string _pwmPinFolder(const PinName &pin);
            static std::string _pwmPinChipId(const PinName &pin);

        public:
            PwmPin(
                const PinName &pin,
                const std::chrono::nanoseconds &duty,
                const std::chrono::nanoseconds &period
            );
            void setDuty(const std::chrono::nanoseconds &duty);
            void setPeriod(const std::chrono::nanoseconds &period);

            void init() override;
            void on() override;
            void off() override;
            bool isRunning();
            void deInit() override;
    };

    struct GpioControlException : public std::exception {
        virtual const char *what() const throw();
    };

    struct NotAPwmPinException : public GpioControlException {
        private:
            PinName _pin;
        
        public:
            NotAPwmPinException(const PinName &pin);
            const char *what() const throw() override;
    };

    struct DutyCycleTooSmallException : public GpioControlException {
        private:
            std::chrono::nanoseconds _duty, _period;

        public:
            DutyCycleTooSmallException(
                const std::chrono::nanoseconds &duty,
                const std::chrono::nanoseconds &period
            );
            const char *what() const throw() override;
    };
}
