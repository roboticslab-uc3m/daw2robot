/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include <yarp/os/all.h>
#include <yarp/dev/all.h>

//==============================================================================
/**
*/
class JuceYarpAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    JuceYarpAudioProcessor();
    ~JuceYarpAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    //==============================================================================
    void setRemoteName(String str)
    {
        printf("Set: %s.\n", str.toStdString().c_str());
    }

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceYarpAudioProcessor)
    
    //==============================================================================
    AudioProcessorValueTreeState parameters;

    yarp::os::Network yarp;
    yarp::dev::PolyDriver device;
    yarp::dev::IPositionDirect* pos;
    yarp::dev::IControlMode* mode;
};
