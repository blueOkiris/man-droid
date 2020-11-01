#pragma once

/*
 * The speech synthesis api I will be creating
 * will utilize IPA notation to build syllables.
 * 
 * If you want to have an understanding of IPA
 * Here's a website that shows pronunciation:
 * https://www.ipachart.com/
 */

#include <map>
#include <string>
#include <SDL2/SDL_mixer.h>
#include <Servo.hpp>

namespace mandroid {
    class SpeechSynthesizer {
        private:
            // Possibly replace with smart pointers in future
            const std::map<std::string, Mix_Chunk *> _speechTable;
            const std::map<std::string, std::string> _wordToPronunciation;
            const Servo _mouth;

            static std::map<std::string, Mix_Chunk *> _generateSpeechTable(
                const std::string &audioFolder
            );
            static std::map<std::string, std::string> 
                _generatePronunciationTable(const std::string &dictFileName);
            static std::string _guessSound(const std::string &word);
            
        public:
            SpeechSynthesizer(
                const std::string &audioFolder,
                const std::string &dictFile
            );
            ~SpeechSynthesizer();
            void say(const std::string &ipa) const;
            std::string englishToIpa(const std::string &english) const;
    };
    
    struct SpeechSynthesisIntializationException : public std::exception {
        private:
            const std::string _message;
        public:
            SpeechSynthesisIntializationException(const std::string &message);
            const char *what() const throw();
    };
}
