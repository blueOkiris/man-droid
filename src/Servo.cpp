#include <iostream>
#include <string>
#include <fstream>
#include <Servo.hpp>

using namespace mandroid;

float Servo::_dutyFromAngle(const int &angle) {
    const auto dutyMin = 3;
    const auto dutyMax = 14.5;
    const auto dutySpan = dutyMax - dutyMin;
    return 100 - ((((float) angle) / 180) * dutySpan + dutyMin);
}

Servo::Servo(const PwmPinName &pinName) : _pin(pinFromName(pinName)) {
}

void Servo::start() const {
    const auto pythonCmd = "python3 src/pwm.py '" + _pin.pythonName + "'";
    system(pythonCmd.c_str());
    std::ofstream periodFile(_pin.periodFileName);
    periodFile << "16666666";
    periodFile.close();
    std::ofstream dutyFile(_pin.dutyFileName);
    dutyFile << "999999";
    dutyFile.close();
    std::ofstream enableFile(_pin.enableFileName);
    enableFile << "1";
    enableFile.close();
}

void Servo::setAngle(const int &angle) const {
    const auto dutyPercent = 100 - _dutyFromAngle(angle) + 1;
    const auto dutyNumber = 16666666 * dutyPercent / 100;
    const auto dutyStr = std::to_string(static_cast<int>(dutyNumber));
    std::ofstream dutyFile(_pin.dutyFileName);
    dutyFile << dutyStr;
    dutyFile.close();
}

void Servo::stop() const {
    std::ofstream enableFile(_pin.enableFileName);
    enableFile << "0";
    enableFile.close();
}
