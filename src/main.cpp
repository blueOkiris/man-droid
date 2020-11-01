#include <iostream>
#include <Tests.hpp>
#include <Brain.hpp>

using namespace mandroid;

int main(int argc, char **args) {
    std::cout << "Initializing the Mandroid!" << std::endl;
    
    //testServo();
    //testSpeechRecognition();
    //testSpeechSynthesis();
    testHearAndRespond();

    //const Mandroid brain;

    return 0;
}