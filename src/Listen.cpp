#include <string>
#include <iostream>
#include <pybind11/embed.h>
#include <Listen.hpp>

using namespace mandroid;

PythonSpeechRecognizer::PythonSpeechRecognizer() {
    pybind11::scoped_interpreter guard {};
    pybind11::print("Initialized speech recognition!");
}

// Dangerous C-like code *shivers*
std::string PythonSpeechRecognizer::listen() const {
    pybind11::scoped_interpreter guard{};
    auto listenModule = pybind11::module::import("src.listen");
    auto result = listenModule.attr("speechToText")();
    
    return result.cast<std::string>();
}
