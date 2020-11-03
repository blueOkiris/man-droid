#include <iostream>
#include <Tests.hpp>
#include <Brain.hpp>

using namespace mandroid;

inline void runBot(const std::shared_ptr<Mandroid> &brain) {
    while(brain->respond());
}

int main(int argc, char **args) {
    std::cout << "Initializing the Mandroid!" << std::endl;
    
    //testServo();
    //testSpeechRecognition();
    //testSpeechSynthesis();
    testHearAndRespond();

    //runBot(std::make_shared<IfElseBot>(IfElseBot()));

    return 0;
}
