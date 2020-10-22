#include <chrono>
#include <GpioControl.hpp>
#include <Servo.hpp>

using namespace mandroid;

Servo::Servo(PinName pin) : 
        _pin(
            PwmPin(
                pin,
                std::chrono::nanoseconds(1000000),
                std::chrono::nanoseconds(20000000)
            )
        ) {
}

void Servo::setAngle(int angle) const {
    const auto minPulse = std::chrono::nanoseconds(1000000);
    const auto maxPulse = std::chrono::nanoseconds(2000000);
    const auto pulseRange = maxPulse - minPulse;
    const auto pulseWidthPerDeg = pulseRange / 181;
    const auto pulseWidth = minPulse + (angle * pulseWidthPerDeg);
    _pin.setDuty(pulseWidth);
}

void Servo::start() const {
    _pin.init();
}

void Servo::stop() const {
    _pin.deInit();
}
