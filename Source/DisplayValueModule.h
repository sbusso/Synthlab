/*
  ==============================================================================

    DisplayValueModule.h
    Created: 16 Apr 2018 12:51:10pm
    Author:  Matthias Pueski

  ==============================================================================
*/

#pragma once


#include "../JuceLibraryCode/JuceHeader.h"
#include "Module.h"

//==============================================================================
/*
 */
class DisplayValueModule    : public Module
{
public:
    DisplayValueModule();
    ~DisplayValueModule();
    
    void paint (Graphics& g) override;

    virtual void process() override;
    
    virtual void configurePins() override;
    
    virtual String getCategory() override {
        return "Debug";
    }
    
private:
    float value = 0;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DisplayValueModule)
};
