#include <map>
#include <vector>
#include <string>
#include <string_view>
#include <sstream>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <algorithm>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <Servo.hpp>
#include <PwmPins.hpp>
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

static inline std::string trim(const std::string &str) {
    auto strMutCopy = str;
    strMutCopy.erase(
        strMutCopy.begin(), std::find_if(
            strMutCopy.begin(), strMutCopy.end(), [](unsigned char ch) {
                return !std::isspace(ch);
            }
        )
    );
    strMutCopy.erase(
        std::find_if(
            strMutCopy.rbegin(), strMutCopy.rend(), [](unsigned char ch) {
                return !std::isspace(ch);
            }
        ).base(), strMutCopy.end()
    );
    return strMutCopy;
}

static inline bool endsWith(
        const std::string &mainStr, const std::string &toMatch) {
    if(mainStr.size() >= toMatch.size() &&
            mainStr.compare(
                mainStr.size() - toMatch.size(), toMatch.size(), toMatch
            ) == 0) {
        return true;
    } else {
        return false;
    }
}

static inline std::vector<std::string> split(
        const std::string &str, const std::string &splitStr) {
    std::vector<std::string> subStrs;

    // Loop through all space-separated strings
    auto strMutCpy = str;
    if(endsWith(strMutCpy, splitStr)) {
        strMutCpy += splitStr;
    }
    size_t pos = 0;
    while((pos = strMutCpy.find(splitStr)) != std::string::npos) {
        const auto substr = strMutCpy.substr(0, pos);
        subStrs.push_back(substr);
        strMutCpy.erase(0, pos + 1);
    }

    return subStrs;
}

std::map<std::string, Mix_Chunk *> SpeechSynthesizer::_generateSpeechTable(
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

std::map<std::string, std::string>
    SpeechSynthesizer::_generatePronunciationTable(
        const std::string &dictFileName) {
    // Read in and split the entries (line-separated)
    std::ifstream dictFile(dictFileName);
    std::string dictStr;
    dictFile.seekg(0, std::ios::end);   
    dictStr.reserve(dictFile.tellg());
    dictFile.seekg(0, std::ios::beg);
    dictStr.assign(
        std::istreambuf_iterator<char>(dictFile),
        std::istreambuf_iterator<char>()
    );
    dictFile.close();
    const auto lines = split(dictStr, "\n");

    // Parse the pairs, <word> <space> <ipa-string>
    std::map<std::string, std::string> pronunciationTable;
    for(const auto &line : lines) {
        const auto pieces = split(line, " ");
        if(pieces.size() < 1) {
            throw SpeechSynthesisIntializationException(
                "Invalid dictionary file"
            );
        } else {
            const auto wordStr = pieces.at(0);
            const auto ipaStr = trim(line.substr(wordStr.length()));
            pronunciationTable[wordStr] = ipaStr;
        }
    }
    return pronunciationTable;
}

std::string SpeechSynthesizer::_guessSound(const std::string &word) {
    /*
     * No known pronunciation, so we have to guess based on the letters
     * Consonants:
     *  - ph -> /f/
     *  - th -> /ð/
     *  - ch -> /tʃ/
     *  - rest correlate with IPA
     * Vowels:
     *  - ae -> /e/
     *  - ay -> /e/
     *  - ei -> /e/
     *  - ie -> /i/
     *  - ou -> /aʊ/
     *  - y -> /j/
     *  - rest guess 5 vowel system
     */
    return "";
}

SpeechSynthesizer::SpeechSynthesizer(
            const std::string &audioFolder, const std::string &dictFile) :
        _speechTable(_generateSpeechTable(audioFolder)),
        _wordToPronunciation(_generatePronunciationTable(dictFile)),
        _mouth(PwmPinName::P9_22) {
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
    const auto sounds = split(ipa, " ");
    for(const auto &sound : sounds) {
        if(sound == ".") {
            _mouth.setAngle(mouthMinAngle_g);
        } else {
            _mouth.setAngle(mouthMaxAngle_g);
            Mix_PlayChannel(0, _speechTable.at(sound), 0);
            while(Mix_Playing(0));
        }
    }
}

std::string SpeechSynthesizer::englishToIpa(const std::string &english) const {
    std::stringstream ipa;

    const auto words = split(english, " ");
    for(const auto &word : words) {
        const auto pronounceMapIt = _wordToPronunciation.find(word);
        if(pronounceMapIt == _wordToPronunciation.end()) {
            ipa << _guessSound(word);
        } else {
            ipa << pronounceMapIt->second;
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
