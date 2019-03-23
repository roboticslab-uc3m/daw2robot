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
        audio.append(0.0)

    return


def append_sinewave(freq=0.5, duration_milliseconds=4000, volume=1.0):

    num_samples = duration_milliseconds * (sample_rate / 1000.0)

    for x in range(int(num_samples)):
        audio.append(volume * math.sin(2 * math.pi * freq * ( x / sample_rate )))

    return


def save_wav(file_name):

    wav_file = wave.open(file_name,"w")

    nchannels = 1 # Mono
    sampwidth = 2 # Defines 2 bytes => 16 bit (signed integer) amplitude resolution
    # The WAV will have -32767 to 32767 integers, but JUCE will read -1.0 to 1.0 float32

    nframes = len(audio)
    comptype = "NONE"
    compname = "not compressed"
    wav_file.setparams((nchannels, sampwidth, sample_rate, nframes, comptype, compname))

    for sample in audio:
        wav_file.writeframes(struct.pack('h', int( sample * 32767.0 )))
    # The next three lines provide an alternative vectorized version (also replace 'struct' above by 'numpy as np')
    #np_audio = np.array(audio) * 32767.0
    #np_audio = np_audio.astype(np.int16)
    #wav_file.writeframes(np_audio.tobytes())

    wav_file.close()

    return

def createMonoWaveControl():
    append_sinewave(freq=0.5, volume=0.25)
    append_silence()
    append_sinewave(freq=0.5, volume=0.5)
    append_silence()
    append_sinewave(freq=0.5)
    save_wav("wave1control.wav")

def createMonoWaveSound():
    append_sinewave(freq=261.63, volume=0.25)
    append_silence()
    append_sinewave(freq=293.67, volume=0.5)
    append_silence()
    append_sinewave(freq=329.63)
    save_wav("wave1sound.wav")

audio = []
createMonoWaveControl()
audio = []
createMonoWaveSound()
