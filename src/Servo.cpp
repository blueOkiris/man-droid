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
    const pybind11::bytes byteStr(_pinName);
    auto servoModule = pybind11::module::import("src.servo");
    servoModule.attr("start")(byteStr);
}

void Servo::setAngle(int angle) const {
    pybind11::scoped_interpreter guard{};
    const pybind11::bytes byteStr(_pinName);
    auto servoModule = pybind11::module::import("src.servo");
    servoModule.attr("setAngle")(byteStr, angle);
}

void Servo::stop() const {
    pybind11::scoped_interpreter guard{};
    const pybind11::bytes byteStr(_pinName);
    auto servoModule = pybind11::module::import("src.servo");
    servoModule.attr("stop")(byteStr);
}
