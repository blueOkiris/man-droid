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

### External Hardware

This project was constructed with [this mask](https://www.amazon.com/Realistic-Latex-Halloween-Rubber-Masquerade/dp/B07Y9LSPGD/ref=sr_1_50?dchild=1&keywords=human+costume+mask&qid=1603054888&refinements=p_85%3A2470955011&rnid=2470954011&rps=1&sr=8-50), [these dowels](https://www.amazon.com/Hygloss-Products-4-Inch-12-Inch-10-Pack/dp/B06WWNBRXJ/ref=sr_1_3?dchild=1&keywords=wooden+dowel&qid=1603055087&sr=8-3), [this wooden base](https://www.amazon.com/Better-Crafts-Wooden-Perfect-Projects/dp/B07DDNHGR7/ref=sr_1_4?dchild=1&keywords=wooden+base&qid=1603055130&sr=8-4), and [this servo](https://www.amazon.com/gp/product/B076CNKQX4/ref=crt_ewc_img_dp_1?ie=UTF8&psc=1&smid=A3NMC7084N0TIJ).

The dowels and wooden base are used to make a framework for holding up the mask as well as holding the beaglebone.

Another dowel is attached to a motor, which is attached to the central dowel. The motor's dowel is also connected at the other end to the base of the jaw so that the mouth can be opened.

## Software

Here's the installation commands for installing the mandroid software:

```
git clone https://github.com/blueOkiris/man-droid
pip3 install SpeechRecognition
sudo apt install -y libsdl2-dev libsdl2-mixer-dev python3-pyaudio pybind11-dev
make
sudo make install
```

Here's the explanation

 - Download from git
 
 - Dependencies:

   + SDL2_mixer is required for speech synthesis: `libsdl2-dev libsdl2-mixer-dev`

   + The Python pip library `SpeechRecognition` is required for speech recognition. It relies on: `python3-pyaudio`

   + The python speech recognition library is called in C++ using pybind: `pybind11-dev`
 
 - Build with make
 
 - Install system service for running at start

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
