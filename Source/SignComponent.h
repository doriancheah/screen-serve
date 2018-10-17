/*
  ==============================================================================

    SignComponent.h
    Created: 16 Oct 2018 10:36:32pm
    Author:  Dorian Cheah

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "SServer.h"
#include "SConfig.h"

//==============================================================================
/*
*/
class SignComponent    : public AnimatedAppComponent,
                         public ActionListener

{
public:
    SignComponent();
    ~SignComponent();

    void paint (Graphics&) override;
    void resized () override;
    void update () override;
    void actionListenerCallback (const String & message) override;
    void setScreeningMode (bool isScreening);
    std::shared_ptr<SConfig> config;
    
private:
    SServer server;
    String strStatus = "Mix in progress. Please enter quietly.";
    String strProjectName = "E.T.";
    String strDirector = "Steven Spielberg";
    bool screeningMode;
    Colour signColour = Colours::darkslateblue;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SignComponent)
};
