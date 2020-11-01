#pragma once

#include <string>

namespace mandroid {
    class SpeechRecognizer {
        public:
            virtual std::string listen() const = 0;
    };

    class PythonSpeechRecognizer : public SpeechRecognizer {
        public:
            PythonSpeechRecognizer();
            std::string listen() const override;
    };
}
