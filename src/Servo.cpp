#include <iostream>
#include <chrono>
#include <string>
#include <utility>
#include <memory>
#include <libsoc_pwm.h>
#include <libsoc_debug.h>
#include <Servo.hpp>

using namespace mandroid;

Servo::Servo(const PinName &pin) : 
        _generatePwm(pinNameToChip(pin)) {
}

std::shared_ptr<pwm> Servo::_generatePwm(const std::pair<int, int> &pinId) {
    libsoc_set_debug(1);
    pwm *pwm = libsoc_pwm_request(_pinId.first, _pinId.second, LS_PWM_SHARED);
    if(!pwm) {
        std::cout << "Couldn't start pwm" << std::endl;
    }
    return std::make_shared<pwm>(pwm);
}

void Servo::start() const {
    libsoc_pwm_set_enabled(_pwm.get());
    libsoc_pwm_set_period(_pwm.get(), 1000000000 / 60);
    libsoc_pwm_set_duty(_pwm.get(), 1000000000 / 58);
}

void Servo::setAngle(const int &angle) const {
    const auto duty = dutyFromAngle(angle) * 60;
    libsoc_pwm_set_duty(_pwm.get(), 1000000000 / static_cast<int>(duty));
}

void Servo::stop() const {
    libsoc_pwm_free(_pwm.get());
}
