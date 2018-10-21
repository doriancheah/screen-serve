/*
  ==============================================================================

    SignComponent.cpp
    Created: 16 Oct 2018 10:36:32pm
    Author:  Dorian Cheah

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "SignComponent.h"

//==============================================================================
SignComponent::SignComponent()
{
    // register the sign component as a listener to the SServer instance and start the thread.
    server.addActionListener(this);
    server.startThread();
    
    // instantiate the config object to get the app settings.
    config = std::make_shared<SConfig>();
    
    setSignMode(SignModes::modeMixing);
}

SignComponent::~SignComponent()
{
    
}

void SignComponent::paint (Graphics& g)
{
    g.setColour (getSignColour(signMode));
    g.fillAll();

    g.setColour (Colours::white);
    g.setFont (getHeight() * 0.08f);
    g.setOpacity (1.0f);
    g.drawText (getStatus(signMode), 0, getHeight() * 0.4f, getWidth(), getHeight() * 0.12f, Justification::centredTop, true);
    g.setFont (getHeight() * 0.05f);
    g.setOpacity (0.75f);
    
    g.drawText (signMode == SignModes::modeDark ? "" : config->getProjectName(),
                0,
                getHeight() * 0.6f,
                getWidth(),
                getHeight() * 0.12f,
                Justification::centredTop,
                true);
    
    g.drawText (signMode == SignModes::modeDark ? "" : config->getDirectorName(),
                0,
                getHeight() * 0.7f,
                getWidth(),
                getHeight() * 0.12f,
                Justification::centredTop,
                true);
}

void SignComponent::resized()
{

}

// The callback function for SServer, called when SServer receives its message. We check for the special strings from
// Vantage system and set the sign mode accordingly.

void SignComponent::actionListenerCallback (const String & message)
{
    if (message.contains ("screening_start"))
    {
        setSignMode(SignModes::modeScreening);
        
    }
    else if (message.contains ("screening_stop"))
    {
        setSignMode(SignModes::modeMixing);
        
    }
    else if (message.contains ("screening_shutdown"))
    {
        setSignMode(SignModes::modeDark);
    }
}

void SignComponent::setSignMode(SignModes const& mode)
{
    signMode = mode;
    repaint();
}

Colour SignComponent::getSignColour(SignModes const& mode) const
{
    switch (signMode)
    {
        case SignModes::modeMixing:
            return Colours::darkslateblue;
        case SignModes::modeScreening:
            return Colours::red;
        case SignModes::modeDark:
            return Colours::black;
        default:
            return Colours::black;
    }
}

String SignComponent::getStatus(SignModes const& mode) const
{
    switch (signMode)
    {
        case SignModes::modeMixing:
            return config->getMixingMessage();
        case SignModes::modeScreening:
            return config->getScreeningMessage();
        default:
            return "";
    }
}

