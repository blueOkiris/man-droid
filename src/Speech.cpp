#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <Speech.hpp>

using namespace mandroid;

static const std::vector<std::string> ipaSymbols = {
    "i", "y", "u", "ɪ", "ʊ", "e", "o", "ə", "ɚ", "ɛ", "ʌ", "ɔ", "æ", "a", "ɒ",
    "p", "b", "t", "d", "c", "ɟ", "k", "g", "ʔ",
    "m", "n", "ɲ", "ŋ",
    "r", "ɹ", "l"
    "f", "v", "θ", "ð", "s", "z", "ʃ", "ʒ", "x", "h"
    "j", "w"
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
        fileName << audioFolder << "/" << ipaSymbol;
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
    
}

SpeechSynthesisIntializationException::SpeechSynthesisIntializationException(
        const std::string &message) : _message(message) {   
}

const char *SpeechSynthesisIntializationException::what() const throw() {
    return std::string(
            "Failed to initialize speech synthesisizer. SDL error: " + _message
        ).c_str();
}
