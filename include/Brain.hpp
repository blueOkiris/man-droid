#pragma once

#include <memory>
#include <Speech.hpp>
#include <Listen.hpp>

namespace mandroid {
    /*
     * To use, create an instance of a child class
     * Call .boot()
     * 
     * The child class need simply implement the respond question
     * That function returns false if the bot should stop
     * Inside it handles listening/talking
     * 
     * Here I've implemented a simple chat bot that simply does
     * if statements
     * One could also implement a more robust chat bot
     * by using natural language processing
     */

    class Mandroid {
        protected:
            const std::shared_ptr<SpeechRecognizer> _ears;
            const std::shared_ptr<SpeechSynthesizer> _mouth;
        
        public:
            Mandroid(
                const std::shared_ptr<SpeechRecognizer> &ears,
                const std::shared_ptr<SpeechSynthesizer> &mouth
            );
            virtual bool respond() const = 0; // used like "while(respond());"
    };

    class IfElseBot : public Mandroid {
        public:
            IfElseBot(
                const std::shared_ptr<SpeechRecognizer> &ears,
                const std::shared_ptr<SpeechSynthesizer> &mouth
            );
            bool respond() const override;
    };
}
