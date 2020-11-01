#pragma once

#include <Speech.hpp>
#include <Listen.hpp>

namespace mandroid {
    class Mandroid {
        private:
            const SpeechRecognizer _ears;
            const SpeechSynthesizer _mouth;
        
        public:
            Mandroid();
    };
}
