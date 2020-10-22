# Mandroid

## Executive Summary

![project image](images/temp-image.png)

A humanoid talking robot head.

The head listens to you with a microphone, formulates a response, and then replies using speech synthesis while moving its mouth.

Currently, I have PWM working on the beaglebone and a rudimentary speech synthesizer as well as speech recognition.

The primitive chat-bot, the mouth, and servo control are not working.

An example of a much more complex version of what I'm aiming for can be found [here](https://www.youtube.com/watch?v=WN9IdpB2-oo). At a minimum, this robot will respond to some speech input, move its mouth a bit, and output some speech output. If I can't build a complex chat bot in time, that's okay with me. I plan to focus on the other three parts more than anything else.

## Packaging

If you have hardware, consider Small Build, Big Execuition for ideas on the final packaging.

## Installation Instructions

Give step by step instructions on how to install your project.

* Include your github path as a link like this to the read-only git site: https://github.com/MarkAYoder/gitLearn.

* Be sure your README.md is includes an up-to-date and clear description of your project so that someone who comes across you git repository can quickly learn what you did and how they can reproduce it.

* Include a Makefile for your code if using C.

* Include any additional packages installed via apt. Include install.sh and setup.sh files.

* Include kernel mods.

* If there is extra hardware needed, include links to where it can be obtained.

SDL2_mixer is required for speech synthesis.

To install: `sudo apt -y install libsdl2-dev libsdl2-mixer-dev`

The Python pip library `SpeechRecognition` is required for speech recognition

To install: `sudo apt -y install python3-pyaudio`

That library makes use of the `PocketSphinx` libray.

Install that with `sudo apt -y install python3-pocketsphinx`

## User Instructions

Once everything is installed, how do you use the program? Give details here, so if you have a long user manual, link to it here.

Consider making it autostart for full credit.

## Highlights

Here is where you brag about what your project can do.

Include a YouTube demo the audio description.

## Theory of Operation

Give a high level overview of the structure of your software. Are you using GStreamer? Show a diagram of the pipeline. Are you running multiple tasks? Show what they do and how they interact.

## Work Breakdown

List the major tasks in your project and who did what.

Also list here what doesn't work yet and when you think it will be finished and who is finishing it.

## Future Work

Suggest addition things that could be done with this project.

## Conclusions

Give some concluding thoughts about the project. Suggest some future additions that could make it even more interesting.
