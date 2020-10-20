#pragma once

#include <chrono>
#include <string>

namespace mandroid {
    enum class PinName {
        Pwm_P9_22 = 0
    };

    class GpioPin {
        public:
            virtual void init() const = 0;
            virtual void on() const = 0;
            virtual void off() const = 0;
            virtual void deInit() const = 0;
    };

    class PwmPin : public GpioPin {
        private:
            const PinName _pin;
            const std::chrono::nanoseconds _duty, _period;

            static std::string _pwmPinChipFolder(const PinName &pin);
            static std::string _pwmPinFolder(const PinName &pin);
            static std::string _pwmPinChipId(const PinName &pin);

        public:
            PwmPin(
                const PinName &pin,
                const std::chrono::nanoseconds &duty,
                const std::chrono::nanoseconds &period
            );

            void init() const override;
            void on() const override;
            void off() const override;
            void deInit() const override;
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
