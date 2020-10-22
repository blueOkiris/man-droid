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
            std::map<std::string, Mix_Chunk *> _speechTable;
            Servo _mouth;
            
        public:
            SpeechSynthesizer(const std::string &audioFolder);
            ~SpeechSynthesizer();
            void say(const std::string &ipa);
    };
    
    struct SpeechSynthesisIntializationException : public std::exception {
        private:
            const std::string _message;
        public:
            SpeechSynthesisIntializationException(const std::string &message);
            const char *what() const throw();
    };
}
