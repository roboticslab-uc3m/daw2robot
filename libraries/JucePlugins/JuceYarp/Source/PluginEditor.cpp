/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
JuceYarpAudioProcessorEditor::JuceYarpAudioProcessorEditor (JuceYarpAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    printf("JuceYarpAudioProcessorEditor::JuceYarpAudioProcessorEditor()\n");
    processor.setRobotName(remoteInput.getText().toStdString());
}

JuceYarpAudioProcessorEditor::~JuceYarpAudioProcessorEditor()
{
}

//==============================================================================
void JuceYarpAudioProcessorEditor::labelTextChanged (Label* labelThatHasChanged)
{
    if(&remoteInput == labelThatHasChanged)
    {
        printf("JuceYarpAudioProcessorEditor::labelTextChanged(%s)\n", labelThatHasChanged->getText().toStdString().c_str());
        processor.setRobotName(labelThatHasChanged->getText().toStdString());
    }
}

//==============================================================================
void JuceYarpAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    addAndMakeVisible (remoteFixedText);
    remoteFixedText.attachToComponent (&remoteInput, true);
    remoteFixedText.setColour (Label::textColourId, Colours::orange);
    remoteFixedText.setJustificationType (Justification::right);

    addAndMakeVisible (remoteInput);
    remoteInput.addListener(this);
    remoteInput.setEditable (true);
    remoteInput.setColour (Label::backgroundColourId, Colours::darkblue);
}

void JuceYarpAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    remoteInput    .setBounds (100, 50, getWidth() - 110, 20);
}
