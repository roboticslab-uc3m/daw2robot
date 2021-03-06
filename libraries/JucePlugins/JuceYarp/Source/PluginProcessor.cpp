/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
JuceYarpAudioProcessor::JuceYarpAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::canonicalChannelSet(32), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::mono(), true)
                     #endif
                       )
#endif
{
    printf("JuceYarpAudioProcessor::JuceYarpAudioProcessor()\n");
    robotName = "None";
    pos = nullptr;
    robotIsConnected = false;
}

JuceYarpAudioProcessor::~JuceYarpAudioProcessor()
{
}

//==============================================================================
const String JuceYarpAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool JuceYarpAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool JuceYarpAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool JuceYarpAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double JuceYarpAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int JuceYarpAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int JuceYarpAudioProcessor::getCurrentProgram()
{
    return 0;
}

void JuceYarpAudioProcessor::setCurrentProgram (int index)
{
}

const String JuceYarpAudioProcessor::getProgramName (int index)
{
    return {};
}

void JuceYarpAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void JuceYarpAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    printf("prepareToPlay(%s)\n",robotName.c_str());
    robotOpen();
}

void JuceYarpAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    printf("releaseResources()\n");
    robotClose();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool JuceYarpAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void JuceYarpAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.

    if(!robotIsConnected)
    {
        printf("processBlock: !robotIsConnected\n");
        return;
    }
    if(!pos)
    {
        printf("processBlock: !pos\n");
        return;
    }

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
        for(int sampleIdx=0; sampleIdx<buffer.getNumSamples(); sampleIdx++)
        {
            float f = buffer.getSample(channel,sampleIdx);
            //if ((f>0.001)||(f<-0.001))
            //{
            if (sampleIdx == 0)
            {
                pos->setPosition(channel, f*90.0);
            }
            //}
        }

    }
}

//==============================================================================
bool JuceYarpAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* JuceYarpAudioProcessor::createEditor()
{
    return new JuceYarpAudioProcessorEditor (*this);
}

//==============================================================================
void JuceYarpAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void JuceYarpAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
void JuceYarpAudioProcessor::setRobotName(std::string value)
{
    robotName = value;
    printf("JuceYarpAudioProcessor::setRobotName(%s)\n", robotName.c_str());
}

bool JuceYarpAudioProcessor::robotOpen()
{
    printf("JuceYarpAudioProcessor::robotOpen(%s)\n",robotName.c_str());
    if ("None" == robotName)
    {
        printf("Pass due to: None == robotName\n");
        return false;
    }
    if (robotIsConnected)
    {
        printf("Pass due to: robotIsConnected\n");
        return false;
    }
    yarp::os::Property options;
    options.put("device","remote_controlboard");
    options.put("remote",robotName);
    options.put("local","/reaper"+robotName);
    if(!device.open(options))
    {
        printf("Failed to open device.\n");
        return false;
    }
    device.view(pos);
    device.view(mode);
    int axes;
    pos->getAxes(&axes);
    std::vector<int> modePosd(axes,yarp::os::createVocab('p','o','s','d'));
    mode->setControlModes(modePosd.data());
    robotIsConnected = true;
    return true;
}

void JuceYarpAudioProcessor::robotClose()
{
    printf("JuceYarpAudioProcessor::robotClose()\n");
    if (!robotIsConnected)
    {
        printf("robotClose() Pass due to: !robotIsConnected\n");
        return;
    }
    robotIsConnected = false;
    pos = nullptr;
    device.close();
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new JuceYarpAudioProcessor();
}
