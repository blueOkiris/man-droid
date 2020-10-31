#include <iostream>
#include <utility>
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

Servo::Servo() : _pin(pinFromName(PwmPinName::P9_22)) {
}

void Servo::start() const {
    std::ofstream exportFile(_pin.exportFileName);
    exportFile << _pin.chipId;
    exportFile.close();
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

}

void Servo::stop() const {
    
}
