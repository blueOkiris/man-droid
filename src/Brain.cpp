#include <string>
#include <memory>
#include <Speech.hpp>
#include <Listen.hpp>
#include <Brain.hpp>

using namespace mandroid;

Mandroid::Mandroid(
        const std::shared_ptr<SpeechRecognizer> &ears,
        const std::shared_ptr<SpeechSynthesizer> &mouth) :
        _ears(ears), _mouth(mouth) {
}

void Mandroid::boot() const {
    while(_respond()) {
    }
}

inline std::shared_ptr<PythonSpeechRecognizer> createPyRecognizer() {
    PythonSpeechRecognizer recog;
    return std::make_shared<PythonSpeechRecognizer>(recog);
}

inline std::shared_ptr<ClipBasedSpeechSynthesizer> createClipSynth() {
    ClipBasedSpeechSynthesizer synth("audio", "dict.txt");
    return std::make_shared<ClipBasedSpeechSynthesizer>(synth);
}

IfElseBot::IfElseBot() :
        Mandroid(createPyRecognizer(), createClipSynth()) {
}

bool IfElseBot::_respond() const {
    const auto userInput = _ears->listen();
    if(userInput == "bye" || userInput == "goodbye") {
        _mouth->say(_mouth->englishToIpa("Bye bye!"));
        return false;
    } else {
        _mouth->say(_mouth->englishToIpa("I didn't understand that"));
    }
    return true;
}
