/*
  ==============================================================================

    MainTabbedComponent.cpp
    Created: 4 Apr 2018 12:50:15pm
    Author:  Matthias Pueski

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "MainTabbedComponent.h"
#include "CloseableTabButton.h"
//==============================================================================
MainTabbedComponent::MainTabbedComponent() : juce::TabbedComponent(TabbedButtonBar::Orientation::TabsAtTop)
{


}

MainTabbedComponent::MainTabbedComponent(TabbedButtonBar::Orientation orientation) : juce::TabbedComponent(TabbedButtonBar::Orientation::TabsAtTop){
    
}


void MainTabbedComponent::paint(juce::Graphics &g) {
    g.fillAll (Colour (0xff2e373c));
    g.setColour(Colours::grey);
    // g.drawRect(getBounds());
    g.drawLine(getWidth(), 0, getWidth(), getHeight());
    g.drawLine(0, getHeight(), getWidth(), getHeight());
}

void MainTabbedComponent::popupMenuClickOnTab(int tabIndex, const juce::String &tabName) {
    
    if (tabIndex == 0){
        return;
    }
    
    PopupMenu* m = new PopupMenu();
    
    m->addItem(1, "Close tab");

    const int result = m->show();
    
    if (result == 0)
    {
        // user dismissed the menu without picking anything
    }
    else if (result == 1) {
        TabbedComponent::removeTab(tabIndex);
    }
    delete m;
 
}

void MainTabbedComponent::buttonClicked(juce::Button * button) {
    TabbedComponent::removeTab(button->getName().getIntValue());
}

TabBarButton* MainTabbedComponent::createTabButton(const juce::String &tabName, int tabIndex)
{
    TabBarButton* tb = new TabBarButton(tabName,getTabbedButtonBar());
    
    TextButton* closeButton = new TextButton("x");
    closeButton->setName(String(tabIndex));
    closeButton->addListener(this);
    closeButton->setBounds(0,0,30,20);
    tb->setExtraComponent(closeButton, juce::TabBarButton::ExtraComponentPlacement::afterText);
    return tb;
}
