#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <chrono>
#include <thread>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <Speech.hpp>

using namespace mandroid;

static const std::vector<std::string> ipaSymbols = {
    "i", "u", "ɪ", "ʊ", "e", "o", "ɚ", "ɛ", "ʌ", "æ", "a",
    "p", "b", "t", "d", "k", "g",
    "m", "n", "ɲ", "ŋ",
    "ɹ", "l",
    "aj", "aʊ",
    "f", "v", "θ", "ð", "s", "z", "ʃ", "ʒ", "x", "h",
    "j", "w", "uhl",
};

SpeechSynthesizer::SpeechSynthesizer(const std::string &audioFolder) {
    if(SDL_Init(SDL_INIT_AUDIO)) {
        throw SpeechSynthesisIntializationException(
            std::string(SDL_GetError())
        );
    }
    
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        throw SpeechSynthesisIntializationException(
            std::string(Mix_GetError())
        );
    }
    
    for(const auto &ipaSymbol : ipaSymbols) {
        std::stringstream fileName;
        fileName << audioFolder << "/" << ipaSymbol << ".wav";
        auto sound = Mix_LoadWAV(fileName.str().c_str());
        if(sound == NULL) {
            throw SpeechSynthesisIntializationException(
                std::string(Mix_GetError())
            );
        }
        _speechTable[ipaSymbol] = sound;
    }
}

SpeechSynthesizer::~SpeechSynthesizer() {
    for(auto &symbolFilePair : _speechTable) {
        Mix_FreeChunk(symbolFilePair.second);
        symbolFilePair.second = NULL;
    }
    Mix_Quit();
    SDL_Quit();
}

void SpeechSynthesizer::say(const std::string &ipa) {
    auto ipaStrMut = ipa;
    if(*(ipaStrMut.end() - 1) != ' ') {
        ipaStrMut += ' ';
    }
    size_t pos = 0;
    while((pos = ipaStrMut.find(" ")) != std::string::npos) {
        const auto sound = ipaStrMut.substr(0, pos);
        if(sound == ".") {
            // TODO: Close mouth
        } else {
            Mix_PlayChannel(-1, _speechTable[sound], 0);
            //std::cout << sound << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(150));
        }
        ipaStrMut.erase(0, pos + 1);
    }
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
