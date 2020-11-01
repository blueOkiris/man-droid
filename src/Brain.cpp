#include <string>
#include <Speech.hpp>
#include <Listen.hpp>
#include <Brain.hpp>

using namespace mandroid;

Mandroid::Mandroid() : _ears(), _mouth("audio", "dict.txt") {
}

void Mandroid::boot() const {
    while(_respond()) {
    }
}

bool IfElseBot::_respond() const {
    const auto userInput = _ears.listen();
    if(userInput == "bye" || userInput == "goodbye") {
        _mouth.say(_mouth.englishToIpa("Bye bye!"));
        return false;
    } else {
        _mouth.say(_mouth.englishToIpa("I didn't understand that"));
    }
    return true;
}
