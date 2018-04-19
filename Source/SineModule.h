/*
 ==============================================================================
 
 MidiGate.h
 Created: 4 Apr 2018 3:48:23pm
 Author:  Matthias Pueski
 
 ==============================================================================
 */

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Module.h"
#include "AudioEngine/Sine.h"

//==============================================================================
/*
 */
class SineModule : public Module
{
public:
    SineModule(double sampleRate, int buffersize);
    ~SineModule();
    
    void paint (Graphics& g) override;
    
    void setPitch(int pitch);
    void setAmplitude(float amplitude);
    void setFine(float fine);
    void process() override;
    virtual void configurePins() override;
    
    virtual String getCategory() override {
        return "Sound sources";
    }
    virtual String getDescription() override {
        return BinaryData::oscillator_txt;
    }
    
private:
    
    int pitch = 0;
    float amplitude;
    float fine = 0;
    Image* image;
    Sine* oscillator[128];
    int currentSample = 0;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SineModule)
};

