#include <iostream>
#include <Tests.hpp>
#include <Brain.hpp>

using namespace mandroid;

const auto bot_g = std::make_shared<IfElseBot>(IfElseBot());

int main(int argc, char **args) {
    std::cout << "Initializing the Mandroid!" << std::endl;
    
    //testServo();
    //testSpeechRecognition();
    //testSpeechSynthesis();
    //testHearAndRespond();

    const auto brain = bot_g;
    while(brain->respond());

    return 0;
}