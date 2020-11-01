#include <string>
#include <memory>
#include <Speech.hpp>
#include <Listen.hpp>
#include <Brain.hpp>

using namespace mandroid;

// Defaults:
Mandroid::Mandroid(
        const std::shared_ptr<SpeechRecognizer> &ears,
        const std::shared_ptr<SpeechSynthesizer> &mouth) :
        _ears(ears), _mouth(mouth) {
}

IfElseBot::IfElseBot() :
        Mandroid(
            std::make_shared<PythonSpeechRecognizer>(
                PythonSpeechRecognizer()
            ), std::make_shared<ClipBasedSpeechSynthesizer>(
                ClipBasedSpeechSynthesizer("audio", "dict.txt")
            )
        ) {
}

bool IfElseBot::respond() const {
    const auto userInput = _ears->listen();
    if(userInput == "bye" || userInput == "goodbye") {
        const auto ipa = _mouth->englishToIpa("Bye bye!");
        _mouth->say(ipa);
        return false;
    } else {
        const auto ipa = _mouth->englishToIpa("I didn't understand that");
        _mouth->say(ipa);
    }
    return true;
}
