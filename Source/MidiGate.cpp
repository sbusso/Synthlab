/*
  ==============================================================================

    MidiGate.cpp
    Created: 4 Apr 2018 3:48:23pm
    Author:  Matthias Pueski

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "MidiGate.h"
#include "Connection.h"
#include "MidiOut.h"

//==============================================================================
MidiGate::MidiGate()
{   
    setSize(120,60);
    
    nameLabel->setJustificationType (Justification::left);
    nameLabel->setTopLeftPosition(2,2);
    editable = false;
    prefab = true;
    
}

MidiGate::~MidiGate()
{
    
 
}

void MidiGate::configurePins() {
    Pin* p1 = new Pin(Pin::Type::EVENT);
    p1->direction = Pin::Direction::OUT;
    p1->listeners.push_back(this);
    p1->setName("G");
    addPin(Pin::Direction::OUT,p1);
    
    Pin* p2 = new Pin(Pin::Type::VALUE);
    p2->direction = Pin::Direction::OUT;
    p2->listeners.push_back(this);
    p2->setName("V");
    addPin(Pin::Direction::OUT,p2);
}

void MidiGate::paint(juce::Graphics &g) {
    Module::paint(g);
}

void MidiGate::gateOn(int velocity) {
    
    Event* e = new Event("gate",Event::Type::GATE);
    e->setValue(velocity);
    pins.at(0)->sendEvent(e);
    
    pins.at(1)->setValue(1);
    /*
    for (int i = 0; i < pins.size();i++) {

        MidiOut* out;
        Module* module;
        
        if ((out = dynamic_cast<MidiOut*>(connections->at(i)->target)) != NULL) {
            out->gate(true, velocity);
        }
        if ((module = dynamic_cast<Module*>(connections->at(i)->target)) != NULL) {
            connections->at(i)->b->sendEvent(new Event("gate",Event::Type::GATE));
        }
        

    }
     */
}

void MidiGate::gateOff() {
    Event* e = new Event("gate",Event::Type::GATE);
    e->setValue(0);
    pins.at(0)->sendEvent(e);
    
    pins.at(1)->setValue(0);
}
