#include <iostream>
#include <chrono>
#include <GpioControl.hpp>

using namespace mandroid;

int main(int argc, char **args) {
    std::cout << "Initializing the Mandroid...";

    if(argc < 2) {
        std::cout << "This application requires Google's Speech to Text API"
            << std::endl
            << "Please provide the JSON file with your credentials as"
            << " and argument" << std::endl;
    } else if(argc > 2) {
        std::cout << "Too many arguments provided!";
    }

    std::cout << "Testing pwm..." << std::endl;
    const auto light = PwmPin(
        PinName::Pwm_P9_22,
        std::chrono::nanoseconds(500000000),
        std::chrono::nanoseconds(1000000000)
    );
    light.init();
    light.on();

    std::string waitStr;
    std::cout << "Type a short response and press enter to end...";
    std::cin >> waitStr;

    light.deInit();

    return 0;
}