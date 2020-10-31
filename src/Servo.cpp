#include <iostream>
#include <chrono>
#include <string>
#include <utility>
#include <memory>
#include <libsoc_pwm.h>
#include <libsoc_debug.h>
#include <Servo.hpp>

/*
 * Version control
 * 
 * Old libsoc used LS_SHARED
 * New versions use LS_PWM_SHARED
 */
#ifndef LS_PWM_WEAK
#define LS_PWM_WEAK LS_WEAK
#endif

using namespace mandroid;

float Servo::_dutyFromAngle(const int &angle) {
    const auto dutyMin = 3;
    const auto dutyMax = 14.5;
    const auto dutySpan = dutyMax - dutyMin;
    return 100 - ((((float) angle) / 180) * dutySpan + dutyMin);
}

Servo::Servo(const PinName &pin) : 
        _pwm(_generatePwm(pinNameToChip(pin))) {
}

std::shared_ptr<pwm> Servo::_generatePwm(
        const std::pair<int, int> &pinId) const {
    libsoc_set_debug(1);
    std::shared_ptr<pwm> pwmShared(
        libsoc_pwm_request(pinId.first, pinId.second, LS_PWM_SHARED)
    );
    if(!pwmShared) {
        std::cout << "Couldn't start pwm" << std::endl;
    }
    return pwmShared;
}

void Servo::start() const {
    libsoc_pwm_set_enabled(_pwm.get(), ENABLED);
    libsoc_pwm_set_period(_pwm.get(), 1000000000 / 60);
    libsoc_pwm_set_duty_cycle(_pwm.get(), 1000000000 / 58);
}

void Servo::setAngle(const int &angle) const {
    const auto duty = _dutyFromAngle(angle) * 60;
    libsoc_pwm_set_duty_cycle(_pwm.get(), 1000000000 / static_cast<int>(duty));
}

void Servo::stop() const {
    libsoc_pwm_free(_pwm.get());
}
