#include <vector>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <StringHelper.hpp>
#include <Servo.hpp>
#include <PwmPins.hpp>
#include <Speech.hpp>

using namespace mandroid;

static const int mouthMaxAngle_g = 90;
static const int mouthMinAngle_g = 0;

SpeechSynthesizer::SpeechSynthesizer() : _mouth(PwmPinName::P9_22) {
    _mouth.start();
    _mouth.setAngle(mouthMinAngle_g);
}

SpeechSynthesizer::~SpeechSynthesizer() {
    _mouth.stop();
}

ClipBasedSpeechSynthesizer::ClipBasedSpeechSynthesizer(
            const std::string &audioFolder, const std::string &dictFile) :
        SpeechSynthesizer(),
        _speechTable(_generateSpeechTable(audioFolder)),
        _wordToPronunciation(_generatePronunciationTable(dictFile)) {
}

ClipBasedSpeechSynthesizer::~ClipBasedSpeechSynthesizer() {
    for(auto &symbolFilePair : _speechTable) {
        Mix_FreeChunk(symbolFilePair.second);
    }
    Mix_Quit();
    SDL_Quit();
    _mouth.stop();
}

void ClipBasedSpeechSynthesizer::say(const std::string &ipa) const {
    const auto sounds = split(ipa, " ");
    for(const auto &sound : sounds) {
        if(sound == ".") {
            _mouth.setAngle(mouthMinAngle_g);
        } else if(sound == "#") {
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
        } else {
            _mouth.setAngle(mouthMaxAngle_g);
            Mix_PlayChannel(0, _speechTable.at(sound), 0);
            while(Mix_Playing(0));
        }
    }
}

std::string ClipBasedSpeechSynthesizer::englishToIpa(
        const std::string &english) const {
    std::stringstream ipa;

    // Remove punctuation and split by spaces
    const auto cleanStr = toLower(
        remove(
            remove(
                remove(
                    remove(remove(remove(remove(english, '!'), '.'), '?'), ','),
                    '/'
                ), '\''
            ), '"'
        )
    );
    const auto words = split(cleanStr, " ");
    for(const auto &word : words) {
        const auto pronounceMapIt = _wordToPronunciation.find(word);
        if(pronounceMapIt == _wordToPronunciation.end()) {
            ipa << _guessSound(word) << " # ";
        } else {
            ipa << pronounceMapIt->second << " # ";
        }
    }

    return ipa.str();
}

SpeechSynthesisIntializationException::SpeechSynthesisIntializationException(
        const std::string &message) : _message(message) {   
}

const char *SpeechSynthesisIntializationException::what() const throw() {
    std::stringstream error;
    error << "Failed to initialize speech synthesisizer. SDL error: "
        << _message;
    return error.str().c_str();
}
