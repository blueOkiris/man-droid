#include <chrono>
#include <string>
//#include <pybind11/embed.h>
#include <Servo.hpp>

using namespace mandroid;

Servo::Servo(PinName pin) : 
        _pinName(pinNameStr(pin)) {
}

void Servo::start() const {
    /*pybind11::scoped_interpreter guard{};
    auto pwm = pybind11::module::import("Adafruit_BBIO.PWM");
    pwm.attr("start")(pybind11::str(_pinName.c_str()), 97, 60);*/
}

void Servo::setAngle(const int &angle) const {
    /*pybind11::scoped_interpreter guard{};
    auto pwm = pybind11::module::import("Adafruit_BBIO.PWM");
    pwm.attr("set_duty_cycle")(
        pybind11::str(_pinName.c_str()), dutyFromAngle(angle)
    );*/
}

void Servo::stop() const {
    /*pybind11::scoped_interpreter guard{};
    auto pwm = pybind11::module::import("Adafruit_BBIO.PWM");
    pwm.attr("stop")(pybind11::str(_pinName.c_str()));
    pwm.attr("cleanup")();*/
}
