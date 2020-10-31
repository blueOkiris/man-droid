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

Servo::Servo(const PinName &pin) : 
        _pinId(pinNameToChip(pin)) {
}

void Servo::start() const {
    const auto exportFileName = "/sys/class/pwm/" + std::get<0>(_pinId)
        + "/export";
    const auto pinPeriodFileName = "/sys/class/pwm/" + std::get<0>(_pinId) + "/"
        + std::get<1>(_pinId) + "/period";
    const auto period = 1000000000 / 60;
    const auto pinDutyFileName = "/sys/class/pwm/" + std::get<0>(_pinId) + "/"
        + std::get<1>(_pinId) + "/duty_cycle";
    const float dutyCycle = 1000000000 / (0.97 * 60);
    const auto enableFileName = "/sys/class/pwm/" + std::get<0>(_pinId) + "/"
        + std::get<1>(_pinId) + "/enable";

    std::ofstream exportFile(exportFileName);
    exportFile << std::get<2>(_pinId) << std::endl;
    exportFile.close();
    std::ofstream periodFile(pinPeriodFileName);
    periodFile << period << std::endl;
    periodFile.close();
    std::ofstream dutyFile(pinDutyFileName);
    dutyFile << static_cast<int>(dutyCycle) << std::endl;
    dutyFile.close();
    std::ofstream enableFile(enableFileName);
    enableFile << "1" << std::endl;
    enableFile.close();
}

void Servo::setAngle(const int &angle) const {
    const auto duty = _dutyFromAngle(angle) * 60;

    const auto enableFileName = "/sys/class/pwm/" + std::get<0>(_pinId) + "/"
        + std::get<1>(_pinId) + "/enable";
    const auto pinDutyFileName = "/sys/class/pwm/" + std::get<0>(_pinId) + "/"
        + std::get<1>(_pinId) + "/duty_cycle";

    std::ofstream enableFile(enableFileName);
    enableFile << "0" << std::endl;
    std::ofstream dutyFile(pinDutyFileName);
    dutyFile << static_cast<int>(duty) << std::endl;
    dutyFile.close();
    enableFile << "1" << std::endl;
    enableFile.close();
}

void Servo::stop() const {
    const auto enableFileName = "/sys/class/pwm/" + std::get<0>(_pinId) + "/"
        + std::get<1>(_pinId) + "/enable";
    const auto unExportFileName = "/sys/class/pwm/" + std::get<0>(_pinId)
        + "/unexport";
    std::ofstream enableFile(enableFileName);
    enableFile << "0" << std::endl;
    enableFile.close();
    std::ofstream unExportFile(unExportFileName);
    unExportFile << std::get<2>(_pinId) << std::endl;
    unExportFile.close();
}
