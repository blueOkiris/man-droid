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

SpeechSynthesizer::SpeechSynthesizer() : _mouth(PwmPinName::P9_22),
        _mouthMinAngle(0), _mouthMaxAngle(10) {
    _mouth.start();
    _mouth.setAngle(_mouthMinAngle);
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
    _mouth.setAngle(_mouthMinAngle);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    const auto sounds = split(ipa, " ");
    for(const auto &sound : sounds) {
        if(sound == ".") {
            _mouth.setAngle(_mouthMinAngle);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        } else if(sound == "#") {
            _mouth.setAngle(_mouthMinAngle);
            std::this_thread::sleep_for(std::chrono::milliseconds(400));
        } else {
            _mouth.setAngle(_mouthMaxAngle);
            Mix_PlayChannel(0, _speechTable.at(sound), 0);
            while(Mix_Playing(0));
        }
    }
    _mouth.setAngle(_mouthMinAngle);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
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
        const std::string &message) : _message(
            "Failed to initialize speech synthesisizer. Error: " + message
        ) {   
}

const char *SpeechSynthesisIntializationException::what() const throw() {
    return _message.c_str();
}
