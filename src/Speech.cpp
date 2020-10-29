#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <chrono>
#include <thread>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <Servo.hpp>
#include <Speech.hpp>

using namespace mandroid;

static const std::vector<std::string> ipaSymbols_g = {
    "i", "u", "ɪ", "ʊ", "e", "o", "ɚ", "ɛ", "ʌ", "æ", "a",
    "p", "b", "t", "d", "k", "g",
    "m", "n", "ɲ", "ŋ",
    "ɹ", "l",
    "aj", "aʊ",
    "f", "v", "θ", "ð", "s", "z", "ʃ", "ʒ", "x", "h",
    "j", "w", "uhl",
};

static const int mouthMaxAngle_g = 90;
static const int mouthMinAngle_g = 0;
static const PinName mouthPin_g = PinName::P9_22;

inline std::map<std::string, Mix_Chunk *> generateSpeechTable(
        const std::string &audioFolder) {
    std::map<std::string, Mix_Chunk *> speechTable;
    
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
    
    for(const auto &ipaSymbol : ipaSymbols_g) {
        std::stringstream fileName;
        fileName << audioFolder << "/" << ipaSymbol << ".wav";
        auto sound = Mix_LoadWAV(fileName.str().c_str());
        if(sound == NULL) {
            throw SpeechSynthesisIntializationException(
                std::string(Mix_GetError())
            );
        }
        speechTable[ipaSymbol] = sound;
    }
    
    return speechTable;
}

SpeechSynthesizer::SpeechSynthesizer(const std::string &audioFolder) :
        _speechTable(generateSpeechTable(audioFolder)), _mouth(mouthPin_g) {
    _mouth.start();
    _mouth.setAngle(mouthMinAngle_g);
}

SpeechSynthesizer::~SpeechSynthesizer() {
    for(auto &symbolFilePair : _speechTable) {
        Mix_FreeChunk(symbolFilePair.second);
    }
    Mix_Quit();
    SDL_Quit();
    _mouth.stop();
}

void SpeechSynthesizer::say(const std::string &ipa) const {
    auto ipaStrMut = ipa;
    if(*(ipaStrMut.end() - 1) != ' ') {
        ipaStrMut += ' ';
    }
    size_t pos = 0;
    while((pos = ipaStrMut.find(" ")) != std::string::npos) {
        const auto sound = ipaStrMut.substr(0, pos);
        if(sound == ".") {
            _mouth.setAngle(mouthMinAngle_g);
        } else {
            _mouth.setAngle(mouthMaxAngle_g);
            Mix_PlayChannel(0, _speechTable.at(sound), 0);
            while(Mix_Playing(0));
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
