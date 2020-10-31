def speechToText():
    import speech_recognition
    import sys
    
    recognizer = speech_recognition.Recognizer()
    mic = speech_recognition.Microphone()
    
    with mic as source:
        recognizer.adjust_for_ambient_noise(source)
        print('Talk now!')
        audio = recognizer.listen(mic)
    response = ''
    try:
        response = recognizer.recognize_google(audio)
    except speech_recognition.RequestError:
        print('Speech Recognition API Unavailable!')
        return ''
    except speech_recognition.UnknownValueError:
        print('Unable to recognize speech!')
        return ''
    except:
        print('Unknown error occurred: ', sys.exc_info()[0])
        return ''
    return response
