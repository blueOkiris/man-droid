#include <iostream>
#include <memory>
#include <Tests.hpp>
#include <Brain.hpp>

using namespace mandroid;

int main(int argc, char **args) {
    std::cout << "Initializing the Mandroid!" << std::endl;
    
    //testServo();
    //testSpeechRecognition();
    //testSpeechSynthesis();
    testHearAndRespond();

    /*auto success = false;
    while(!success) {
        try {
            const auto ears = PythonSpeechRecognizer();
            const auto mouth = ClipBasedSpeechSynthesizer("audio", "dict.txt");
            const auto earsPtr = std::make_shared<PythonSpeechRecognizer>(ears);
            const auto mouthPtr = std::make_shared<ClipBasedSpeechSynthesizer>(
                mouth
            );
            const auto brain = IfElseBot(earsPtr, mouthPtr);
            
            while(brain.respond()) {
            }
            
            success = true;
        } catch(const SpeechSynthesisIntializationException &ssie) {
            std::cout << "Failed to initialize speech synthesis" << std::endl;
        }
    }*/

    return 0;
}
