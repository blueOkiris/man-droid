#include <chrono>
#include <string>
#include <pybind11/embed.h>
#include <Servo.hpp>

using namespace mandroid;

Servo::Servo(PinName pin) : 
        _pinName(pinNameStr(pin)) {
}

void Servo::start() const {
    pybind11::scoped_interpreter guard{};
    auto servoModule = pybind11::module::import("src.servo");
    servoModule.attr("start")(_pinName);
}

void Servo::setAngle(int angle) const {
    pybind11::scoped_interpreter guard{};
    auto servoModule = pybind11::module::import("src.servo");
    servoModule.attr("setAngle")(_pinName, angle);
}

void Servo::stop() const {
    pybind11::scoped_interpreter guard{};
    auto servoModule = pybind11::module::import("src.servo");
    servoModule.attr("stop")(_pinName);
}
