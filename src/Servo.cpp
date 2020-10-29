#include <chrono>
#include <string>
#include <pybind11/embed.h>
#include <Servo.hpp>

using namespace mandroid;

Servo::Servo(PinName pin) : 
        _pin(pin) {
}

void Servo::setAngle(int angle) const {
    pybind11::scoped_interpreter guard{};
    auto servoModule = pybind11::module::import("src.servo");
    servoModule.attr("setAngle")(pinNameStr(_pin), angle);
}

void Servo::start() const {
    pybind11::scoped_interpreter guard{};
    auto servoModule = pybind11::module::import("src.servo");
    servoModule.attr("start")(pinNameStr(_pin));
}

void Servo::stop() const {
    pybind11::scoped_interpreter guard{};
    auto servoModule = pybind11::module::import("src.servo");
    servoModule.attr("stop")(pinNameStr(_pin));
}
