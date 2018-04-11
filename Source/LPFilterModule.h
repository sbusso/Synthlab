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
#include "AudioEngine/LowPassFilter.h"

//==============================================================================
/*
*/
class LPFilterModule : public Module
{
public:
    LPFilterModule(double sampleRate, int buffersize);
    ~LPFilterModule();

    void paint (Graphics& g) override;

    void process() override;
    virtual void configurePins() override;
    virtual String getCategory() override {
        return "Filter";
    }

private:
    
    LowPassFilter* filter;

    Image* image;

    double sampleRate;
    int buffersize;
    int currentSample = 0;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LPFilterModule)
};