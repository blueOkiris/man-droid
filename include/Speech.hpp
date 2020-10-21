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

namespace mandroid {
    class SpeechSynthesizer {
        private:
            // Possibly replace with smart pointers in future
            std::map<std::wstring, Mix_Chunk *> _speechTable;
            
        public:
            SpeechSynthesizer(const std::string &audioFolder);
            ~SpeechSynthesizer();
            void say(const std::wstring &ipa);
    };
}
