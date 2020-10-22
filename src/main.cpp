#include <iostream>
#include <Tests.hpp>

using namespace mandroid;

int main(int argc, char **args) {
    std::cout << "Initializing the Mandroid..." << std::endl;

    if(argc < 2) {
        std::cout << "This application requires Google's Speech to Text API"
            << std::endl
            << "Please provide the JSON file with your credentials as"
            << " and argument" << std::endl;
    } else if(argc > 2) {
        std::cout << "Too many arguments provided!";
    }

    //testPwm();
    //testServo();
    //testSpeechSynthesis();
    testSpeechRecognition();

    return 0;
}