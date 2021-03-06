#include <string>
#include <memory>
#include <iostream>
#include <pybind11/embed.h>
#include <StringHelper.hpp>
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

IfElseBot::IfElseBot(
        const std::shared_ptr<SpeechRecognizer> &ears,
        const std::shared_ptr<SpeechSynthesizer> &mouth) :
        Mandroid(ears, mouth) {
    const auto ipa = _mouth->englishToIpa("Hello");
    _mouth->say(ipa);
    std::cout << "Initialized!" << std::endl;
}

bool IfElseBot::respond() const {
    const auto userInput = toLower(_ears->listen());
    if(userInput == "bye" || userInput == "goodbye") {
        const auto ipa = _mouth->englishToIpa("Bye bye!");
        _mouth->say(ipa);
        return false;
    } else if(userInput == "hi" || userInput == "hey" ||
            startsWith(userInput, "hello")) {
        const auto hiSounds = _mouth->englishToIpa("hello");
        _mouth->say(hiSounds);
    } else if(startsWith(userInput, "tell me about")) {
        const auto okaySounds = _mouth->englishToIpa("Okay");
        _mouth->say(okaySounds);

        const auto thingToSearch = trim(userInput.substr(13));
        pybind11::scoped_interpreter guard{};
        auto searchModule = pybind11::module::import("duckduckgo");
        auto result = pybind11::cast<std::string>(
            searchModule.attr("get_zci")(thingToSearch)
        );
        const auto resultSounds = _mouth->englishToIpa(result);

        std::cout << result << std::endl << "Saying " << resultSounds << std::endl;
        _mouth->say(resultSounds);
    } else {
        const auto ipa = _mouth->englishToIpa("I didn't understand that");
        _mouth->say(ipa);
    }
    return true;
}
