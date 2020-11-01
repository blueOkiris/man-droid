#include <map>
#include <vector>
#include <string>
#include <string_view>
#include <sstream>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <StringHelper.hpp>
#include <Speech.hpp>

using namespace mandroid;

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
            continue;
        } else {
            const auto wordStr = pieces.at(0);
            const auto ipaStr = trim(line.substr(wordStr.length()));
            pronunciationTable[wordStr] = ipaStr;
        }
    }
    return pronunciationTable;
}

std::string SpeechSynthesizer::_guessSound(const std::string &word) {
    std::stringstream ipa;

    /*
     * No known pronunciation, so we have to guess based on the letters
     * Consonants:
     *  - ph -> /f/
     *  - gh -> //
     *  - th -> /ð/
     *  - ch -> /tʃ/
     *  - qu -> /kw/
     *  - ng -> /ŋ/
     *  - ny -> /ɲ/
     *  - rest correlate with IPA
     * Vowels:
     *  - ae -> /e/
     *  - ay -> /e/
     *  - ei -> /e/
     *  - ie -> /i/
     *  - ou -> /aʊ/
     *  - e at the end -> //
     *  - rest guess 5 vowel system
     */
    for(auto it = word.begin(); it != word.end(); ++it) {
        if(it + 1 == word.end() && *it == 'e') {
            continue;
        }

        if(it + 1 != word.end()) {
            // Check two character clusters
            if(*it == 'p' && *(it + 1) == 'h') {
                ipa << "f ";
                it++;
                continue;
            } else if(*it == 't' && *(it + 1) == 'h') {
                ipa << "ð ";
                it++;
                continue;
            } else if(*it == 'g' && *(it + 1) == 'h') {
                it++;
                continue;
            } else if(*it == 'c' && *(it + 1) == 'h') {
                ipa << "t ʃ ";
                it++;
                continue;
            } else if(*it == 'q' && *(it + 1) == 'u') {
                ipa << "k w ";
                it++;
                continue;
            } else if(*it == 'a' && *(it + 1) == 'e') {
                ipa << "e ";
                it++;
                continue;
            } else if(*it == 'a' && *(it + 1) == 'y') {
                ipa << "e ";
                it++;
                continue;
            } else if(*it == 'e' && *(it + 1) == 'i') {
                ipa << "e ";
                it++;
                continue;
            } else if(*it == 'i' && *(it + 1) == 'e') {
                ipa << "i ";
                it++;
                continue;
            } else if(*it == 'o' && *(it + 1) == 'u') {
                ipa << "aʊ ";
                it++;
                continue;
            } else if(*it == 'n' && *(it + 1) == 'g') {
                ipa << "ŋ ";
                it++;
                continue;
            } else if(*it == 'n' && *(it + 1) == 'y') {
                ipa << "ɲ ";
                it++;
                continue;
            }
        }

        switch(*it) {
            case 'a':
                ipa << "a ";
                break;
            case 'b':
                ipa << "b ";
                break;
            case 'c':
                ipa << "s ";
                break;
            case 'd':
                ipa << "d ";
                break;
            case 'e':
                ipa << "e ";
                break;
            case 'f':
                ipa << "f ";
                break;
            case 'g':
                ipa << "g ";
                break;
            case 'h':
                ipa << "h ";
                break;
            case 'i':
                ipa << "i ";
                break;
            case 'j':
                ipa << "ʒ";
                break;
            case 'k':
                ipa << "k ";
                break;
            case 'l':
                ipa << "uhl ";
                break;
            case 'm':
                ipa << "m ";
                break;
            case 'n':
                ipa << "n ";
                break;
            case 'o':
                ipa << "o ";
                break;
            case 'p':
                ipa << "p ";
                break;
            case 'r':
                ipa << "ɹ ";
                break;
            case 's':
                ipa << "s ";
                break;
            case 't':
                ipa << "t ";
                break;
            case 'u':
                ipa << "u ";
                break;
            case 'v':
                ipa << "v ";
                break;
            case 'w':
                ipa << "w ";
                break;
            case 'x':
                ipa << "k s ";
                break;
            case 'y':
                ipa << "j ";
                break;
            case 'z':
                ipa << "z ";
                break;
        }
    }

    return ipa.str();
}
