#pragma once

#include <chrono>
#include <thread>
#include <string>
#include <GpioControl.hpp>
#include <Servo.hpp>
#include <Speech.hpp>

namespace mandroid {
    inline void testPwm() {
        std::cout << "Testing pwm..." << std::endl;
        auto light = PwmPin(
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
        std::cout << "Done testing pwm." << std::endl;
    }

    inline void testServo() {
        std::cout << "Testing servo..." << std::endl;
        auto servo = Servo(PinName::Pwm_P9_22);
        servo.start();
        for(int i = 0; i < 31; i++) {
            servo.setAngle(i);
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
        }
        for(int i = 30; i >= 0; i--) {
            servo.setAngle(i);
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
        }
        servo.stop();
        std::cout << "Done testing servo." << std::endl;
    }
    
    inline void testSpeechSynthesis() {
        std::cout << "Testing synthesis..." << std::endl;
        auto synth = SpeechSynthesizer("audio");
        std::cout << "Saying \"Hello, world!\"" << std::endl;
        synth.say("h ɛ l l o w ɚ l d");
    }
}
