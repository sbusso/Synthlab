
#include "Project.h"
#include "SampleEditor.h"
#include "push2/JuceToPush2DisplayBridge.h"



//==============================================================================
SampleEditor::SampleEditor (int buffersize, float sampleRate, AudioFormatManager* manager, SamplerModule* module)
{

    this->sampleModule = module;

    addAndMakeVisible (midiKeyboard = new MidiKeyboardComponent (state,orientation));
    addAndMakeVisible (component = new AudioThumbnailComponent(buffersize, sampleRate));

    setSize (600, 400);
    
    if (sampleModule->getBuffer() != nullptr) {
        component->setSampleBuffer(sampleModule->getBuffer());
    }
    state.addListener(this);

}

SampleEditor::~SampleEditor()
{
    state.removeListener(this);
    midiKeyboard = nullptr;
    component = nullptr;

}


void SampleEditor::mouseDoubleClick(const juce::MouseEvent &event) {
    openSample(sampleModule);
}

void SampleEditor::paint (Graphics& g)
{

    g.fillAll (Colour (0xff323e44));

}

void SampleEditor::resized()
{
    midiKeyboard->setBounds (0, 200, proportionOfWidth (1.0000f), 100);
    component->setBounds (0, 0, proportionOfWidth (1.0000f), 200);
}

void SampleEditor::handleNoteOn(juce::MidiKeyboardState *source, int midiChannel, int midiNoteNumber, float velocity) {
    sampleModule->selectSample(midiNoteNumber);
    if (sampleModule->getBuffer() != nullptr) {
        component->setSampleBuffer(sampleModule->getBuffer());
    }
    
}

void SampleEditor::handleNoteOff(juce::MidiKeyboardState *source, int midiChannel, int midiNoteNumber, float velocity) {
    
}

void SampleEditor::openSample(SamplerModule *sm) {
    
    FileChooser chooser("Select file to open", File::nonexistent, "*");
    
    if (chooser.browseForFileToOpen()) {
        
#if JUCE_IOS
        URL url = chooser.getURLResult();
        InputStream* is = url.createInputStream(false);
        
        sm->loadSample(is);
        
        delete is;
        
        ScopedPointer<XmlElement> xml = XmlDocument(data).getDocumentElement();
#else
        File file = chooser.getResult();
        FileInputStream* is = new FileInputStream(file);
        sm->setSamplePath(file.getFullPathName());
        sm->loadSample(is);
        if (sm->getBuffer() != nullptr) {
            component->setSampleBuffer(sm->getBuffer());
        }
        
        // delete is;
        
#endif
        
    }
}
