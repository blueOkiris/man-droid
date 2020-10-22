#include <string>
#include <Python.h>
#include <Listen.hpp>

using namespace mandroid;

SpeechRecognizer::SpeechRecognizer() {
    //import speech_recognition
    Py_SetProgramName(L"RecognitionApp");
    Py_Initialize();
    PyRun_SimpleString(
        "from time import time,ctime\n"
        "print('Today is ' + str(ctime(time())))\n"
    );
    Py_Finalize();
}

std::string SpeechRecognizer::listen() {
    return "";
}
