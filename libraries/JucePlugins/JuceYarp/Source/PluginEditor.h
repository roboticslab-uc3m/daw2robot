/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class JuceYarpAudioProcessorEditor  : public AudioProcessorEditor, public Label::Listener
{
public:
    JuceYarpAudioProcessorEditor (JuceYarpAudioProcessor&);
    ~JuceYarpAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    void labelTextChanged (Label* labelThatHasChanged)
    {
        if(&remoteInput == labelThatHasChanged)
        {
            printf("I have changed to: %s.\n", labelThatHasChanged->getText().toStdString().c_str());
        }
    }

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JuceYarpAudioProcessor& processor;

    Label remoteInput { "Remote input", "/teoSim/rightArm"};
    Label remoteFixedText { "Remote title", "Remote"};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceYarpAudioProcessorEditor)
};
