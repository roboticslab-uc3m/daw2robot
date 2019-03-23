#!/usr/bin/env python

# Thanks: https://stackoverflow.com/questions/4201852/how-do-i-create-a-series-of-high-and-low-pitch-beeps-using-ruby-or-python/21318379#21318379
# Thanks: https://www.daniweb.com/code/snippet263775.html

import math
import wave
import struct

sample_rate = 44100.0

def append_silence(duration_milliseconds=1000):

    num_samples = duration_milliseconds * (sample_rate / 1000.0)

    for x in range(int(num_samples)): 
        audio0.append(0.0)
        audio1.append(0.0)

    return


def append_sinewave(freq0=0.5, freq1=0.5, duration_milliseconds=4000, volume=1.0):

    num_samples = duration_milliseconds * (sample_rate / 1000.0)

    for x in range(int(num_samples)):
        audio0.append(volume * math.sin(2 * math.pi * freq0 * ( x / sample_rate )))
        audio1.append(volume * math.sin(2 * math.pi * freq1 * ( x / sample_rate )))

    return


def save_wav(file_name):

    wav_file = wave.open(file_name,"w")

    nchannels = 2 # Stereo
    sampwidth = 2 # Defines 2 bytes => 16 bit (signed integer) amplitude resolution
    # The WAV will have -32767 to 32767 integers, but JUCE will read -1.0 to 1.0 float32

    nframes = len(audio0) # Assume: len(audio0) == len(audio1)
    comptype = "NONE"
    compname = "not compressed"
    wav_file.setparams((nchannels, sampwidth, sample_rate, nframes, comptype, compname))

    for sample0, sample1 in zip(audio0, audio1):
        wav_file.writeframes(struct.pack('h', int( sample0 * 32767.0 )))
        wav_file.writeframes(struct.pack('h', int( sample1 * 32767.0 )))

    wav_file.close()

    return

def createStereoWaveControl():
    append_sinewave(freq0=0.5, freq1=0.25, volume=0.25)
    append_silence()
    append_sinewave(freq0=0.5, freq1=0.25, volume=0.5)
    append_silence()
    append_sinewave(freq0=0.5, freq1=0.25)
    save_wav("wave2control.wav")

def createStereoWaveSound():
    append_sinewave(freq0=261.63, freq1=261.63, volume=0.25)
    append_silence()
    append_sinewave(freq0=293.67, freq1=293.67, volume=0.5)
    append_silence()
    append_sinewave(freq0=329.63, freq1=329.63)
    save_wav("wave2sound.wav")

audio0 = []
audio1 = []
createStereoWaveControl()
audio0 = []
audio1 = []
createStereoWaveSound()
