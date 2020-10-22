#pragma once

#include <string>

namespace mandroid {
    class SpeechRecognizer {
        public:
            SpeechRecognizer();
            std::string listen() const;
    };
}
