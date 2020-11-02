#pragma once

#include <chrono>
#include <thread>
#include <string>
#include <PwmPins.hpp>
#include <Servo.hpp>
#include <Speech.hpp>
#include <Listen.hpp>

namespace mandroid {
    inline void testServo() {
        std::cout << "Testing servo..." << std::endl;
        Servo servo(PwmPinName::P9_22);
        std::cout << "Turning on..." << std::endl;
        servo.start();
        std::cout << "Testing angles..." << std::endl;
        for(int i = 0; i < 10; i++) {
            servo.setAngle(10);
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            servo.setAngle(0);
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
        std::cout << "Turning off..." << std::endl;
        servo.stop();
        std::cout << "Done testing servo." << std::endl;
    }
    
    inline void testSpeechRecognition() {
        const PythonSpeechRecognizer listener;
        const auto speech = listener.listen();
        std::cout << "You said: '" << speech << "'" << std::endl;
    }
    
    inline void testSpeechSynthesis() {
        try {
            std::cout << "Testing synthesis..." << std::endl;
            const ClipBasedSpeechSynthesizer synth("audio", "dict.txt");
            std::cout << "Saying \"Hello, world!\"" << std::endl;
            synth.say("h ɛ . uhl o");
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            synth.say("w ɚ . uhl d");
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            
            std::cout << "Saying \"Kill all humans\"" << std::endl;
            synth.say("k ɪ uhl");
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            synth.say("a uhl");
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            synth.say("h u . m ɪ n z");
            std::this_thread::sleep_for(std::chrono::milliseconds(500));

            std::cout << "Saying (from English) "
                << "\"Hello, world! Kill all humans!\""
                << std::endl;
            const auto testSentence = "Hello, world! Kill all humans!";
            const auto ipa = synth.englishToIpa(testSentence);
            synth.say(ipa);
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        } catch(const SpeechSynthesisIntializationException &ssie) {
            std::cout << "Exception occurred!" << std::endl << ssie.what()
                << std::endl;
        }
    }

    inline void testHearAndRespond() {
        const PythonSpeechRecognizer ear;
        const ClipBasedSpeechSynthesizer mouth("audio", "dict.txt");

        std::string input = "";
        while(input != "quit") {
            input = ear.listen();
            const auto sounds = mouth.englishToIpa(input);
            mouth.say(sounds);
        }
    }
}
