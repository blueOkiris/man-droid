#include <iostream>
#include <Tests.hpp>

using namespace mandroid;

int main(int argc, char **args) {
    std::cout << "Initializing the Mandroid!" << std::endl;
    
    //testServo();
    testSpeechRecognition();
    //testSpeechSynthesis();

    return 0;
}