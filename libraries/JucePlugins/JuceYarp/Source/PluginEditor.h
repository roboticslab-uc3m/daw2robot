/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

class RemoteLabelListener : public Label::Listener
{
    void labelTextChanged (Label* labelThatHasChanged)
    {
        printf("I have changed to: %s.\n", labelThatHasChanged->getText().getCharPointer());
    }
};

//==============================================================================
/**
*/
class JuceYarpAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    JuceYarpAudioProcessorEditor (JuceYarpAudioProcessor&);
    ~JuceYarpAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JuceYarpAudioProcessor& processor;

    Label remoteInput { "Remote input", "/teoSim/rightArm"};
    Label remoteFixedText { "Remote title", "Remote"};
    RemoteLabelListener remoteLabelListener;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceYarpAudioProcessorEditor)
};
