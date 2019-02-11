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
class SignComponent    : public Component,
                         public ActionListener

{
public:
    SignComponent();
    ~SignComponent();

    void paint (Graphics&) override;
    void resized () override;
    void actionListenerCallback (String const& message) override;
    
    std::shared_ptr<SConfig> config;
    
    enum SignModes
    {
        modeScreening = 1,
        modeMixing,
        modeDark
    };
    
    void setSignMode (SignModes const& mode);
    String getStatus (SignModes const& mode) const;
    Image getImage (SignModes const& mode) const;
    SignModes getSignMode ();
    
private:
    SServer server;
    String strStatus;
    String strProjectName;
    String strDirector;

    SignModes signMode;
    Colour signColour = Colours::darkslateblue;
    
    Colour getSignColour(SignModes const& mode) const;

    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SignComponent)
};
