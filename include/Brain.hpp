#pragma once

#include <Speech.hpp>
#include <Listen.hpp>

namespace mandroid {
    class Mandroid {
        protected:
            const SpeechRecognizer _ears;
            const SpeechSynthesizer _mouth;

            virtual bool _respond() const = 0;
        
        public:
            Mandroid();
            virtual void boot() const;
    };

    class IfElseBot : public Mandroid {
        private:
            bool _respond() const override;
    };
}
