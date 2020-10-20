#include <fstream>
#include <exception>
#include <iostream>
#include <chrono>
#include <string>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <GpioControl.hpp>

using namespace mandroid;

inline bool directoryExists(std::string directory) {
    struct stat info;
    const auto dirTestResult = stat(directory.c_str(), &info);
    return dirTestResult == 0 && (info.st_mode & S_IFDIR);
}

PwmPin::PwmPin(
        const PinName &pin,
        const std::chrono::nanoseconds &duty,
        const std::chrono::nanoseconds &period) :
        _pin(pin), _duty(duty), _period(period) {
    if(static_cast<int>(pin) < 1) {
        throw NotAPwmPinException(pin);
    }
    if(duty >= period) {
        throw DutyCycleTooSmallException(duty, period);
    }
}

void PwmPin::init() const {
    const auto pinFolder = _pwmPinFolder(_pin);
    const auto chipFolder = _pwmPinChipFolder(_pin);
    const auto pinId = _pwmPinChipId(_pin);

    if(!directoryExists(pinFolder)) {
        // Ex: echo 0 > /sys/class/pwmchip1/export
        std::stringstream exportFileName;
        exportFileName << chipFolder << "/export";
        std::ofstream exportFile(exportFileName.str());
        exportFile << pinId << "\n";
        exportFile.close();
    }

    // Ex: echo 1000000 > /sys/class/pwmchip1/pwm-1:0/period 
    std::stringstream periodFileName;
    periodFileName << pinFolder << "/period";
    std::ofstream periodFile(periodFileName.str());
    periodFile << _period.count() << "\n";
    periodFile.close();

    // Ex: echo 500000 > /sys/class/pwmchip1/pwm-1:0/duty_cycle
    std::stringstream dutyFileName;
    dutyFileName << pinFolder << "/duty_cycle";
    std::ofstream dutyFile(dutyFileName.str());
    dutyFile << _duty.count() << "\n";
    dutyFile.close();
}

void PwmPin::on() const {
    const auto pinFolder = _pwmPinFolder(_pin);

    // Ex: echo 1 > /sys/class/pwmchip1/pwm-1:0/enable
    std::stringstream enableFileName;
    enableFileName << pinFolder << "/enable";
    std::ofstream enableFile(enableFileName.str());
    enableFile << "1\n";
    enableFile.close();
}

void PwmPin::off() const {
    const auto pinFolder = _pwmPinFolder(_pin);

    // Ex: echo 0 > /sys/class/pwmchip1/pwm-1:0/enable
    std::stringstream enableFileName;
    enableFileName << pinFolder << "/enable";
    std::ofstream enableFile(enableFileName.str());
    enableFile << "0\n";
    enableFile.close();
}

void PwmPin::deInit() const {
    off();
    
    const auto chipFolder = _pwmPinChipFolder(_pin);
    const auto pinId = _pwmPinChipId(_pin);
    
    std::stringstream unExportFileName;
    unExportFileName << chipFolder << "/unexport";
    std::ofstream unExportFile(unExportFileName.str());
    unExportFile << pinId << "\n";
    unExportFile.close();
}

std::string PwmPin::_pwmPinChipFolder(const PinName &pin) {
    switch(pin) {
        case PinName::Pwm_P9_22:
            return "/sys/class/pwmchip1";
        
        default:
            return "";
    }
}

std::string PwmPin::_pwmPinFolder(const PinName &pin) {
    switch(pin) {
        case PinName::Pwm_P9_22:
            return "/sys/class/pwmchip1/pwm-1:0";
        
        default:
            return "";
    }
}

std::string PwmPin::_pwmPinChipId(const PinName &pin) {
    switch(pin) {
        case PinName::Pwm_P9_22:
            return "0";
        
        default:
            return "";
    }
}

const char *GpioControlException::what() const throw() {
    return "A GPIO control exception occured.";
}

NotAPwmPinException::NotAPwmPinException(const PinName &pin) : _pin(pin) {
}

const char *NotAPwmPinException::what() const throw() {
    std::stringstream message;
    message << "Provided pin '" << static_cast<int>(_pin)
        << "' is not a pwm pin.";
    return message.str().c_str();
}

DutyCycleTooSmallException::DutyCycleTooSmallException(
        const std::chrono::nanoseconds &duty,
        const std::chrono::nanoseconds &period) :
        _duty(duty), _period(period) {
}

const char *DutyCycleTooSmallException::what() const throw() {
    std::stringstream message;
    message << "Duty '" << _duty.count() << "' must be greater than"
        << "period '" << _period.count() <<"'.";
    return message.str().c_str();
}
