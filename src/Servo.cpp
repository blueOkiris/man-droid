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

Servo::Servo() {
}

void Servo::start() const {
    const auto exportFileName = "/sys/class/pwm/pwmchip1/export";
    const auto periodFileName = "/sys/class/pwm/pwmchip1/pwm-1:0/period";
    const auto dutyFileName = "/sys/class/pwm/pwmchip1/pwm-1:0/duty_cycle";
    const auto enableFileName = "/sys/class/pwm/pwmchip1/pwm-1:0/enable";

    std::ofstream exportFile(exportFileName);
    exportFile << "0";
    exportFile.close();
    std::ofstream periodFile(periodFileName);
    periodFile << "16666666";
    periodFile.close();
    std::ofstream dutyFile(dutyFileName);
    dutyFile << "999999";
    dutyFile.close();
    std::ofstream enableFile(enableFileName);
    enableFile << "1";
    enableFile.close();
}

void Servo::setAngle(const int &angle) const {

}

void Servo::stop() const {
    
}
