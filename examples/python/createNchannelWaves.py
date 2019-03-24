#!/usr/bin/env python

# Thanks: https://stackoverflow.com/questions/4201852/how-do-i-create-a-series-of-high-and-low-pitch-beeps-using-ruby-or-python/21318379#21318379
# Thanks: https://www.daniweb.com/code/snippet263775.html

import math
import wave
import struct

nchannels = 3
freqs = [0.5, 0.25, 0.125]

sample_rate = 44100.0

audios = list()
for i in range(nchannels):
    audios.append( list() )

def append_silence(duration_milliseconds=1000):

    num_samples = duration_milliseconds * (sample_rate / 1000.0)

    for x in range(int(num_samples)): 
        for audio in audios:
            audio.append(0.0)

    return


def append_sinewave(freqs=[], duration_milliseconds=4000, volume=1.0):

    num_samples = duration_milliseconds * (sample_rate / 1000.0)

    for x in range(int(num_samples)):
        for audio,freq in zip(audios,freqs):
            audio.append(volume * math.sin(2 * math.pi * freq * ( x / sample_rate )))

    return


def save_wav(file_name):

    wav_file = wave.open(file_name,"w")

    sampwidth = 2 # Defines 2 bytes => 16 bit (signed integer) amplitude resolution
    # The WAV will have -32767 to 32767 integers, but JUCE will read -1.0 to 1.0 float32

    nframes = len(audios[0])
    comptype = "NONE"
    compname = "not compressed"
    wav_file.setparams((nchannels, sampwidth, sample_rate, nframes, comptype, compname))

    for frameIdx in range(nframes):
        for channelIdx in range(nchannels):
            wav_file.writeframes(struct.pack('h', int( audios[channelIdx][frameIdx] * 32767.0 )))

    wav_file.close()

    return

def createStereoWaveControl():
    append_sinewave(freqs, volume=0.25)
    append_silence()
    append_sinewave(freqs, volume=0.5)
    append_silence()
    append_sinewave(freqs)
    save_wav("waveNcontrol.wav")

createStereoWaveControl()

