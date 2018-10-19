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
    setFramesPerSecond(60);
    
    // register the sign component as a listener to the SServer instance and start the thread.
    server.addActionListener(this);
    server.startThread();
    
    // instantiate the config object to get the app settings.
    config = std::make_shared<SConfig>();
    
    // set default sign settings.
    strStatus = config->getMixingMessage();
    strProjectName = config->getProjectName();
    strDirector = "Director: " + config->getDirectorName();
}

SignComponent::~SignComponent()
{
    
}

void SignComponent::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (getSignColour(signMode));
    g.fillAll();

    g.setColour (Colours::white);
    g.setFont (getHeight() * 0.08f);
    g.setOpacity (1.0f);
    g.drawText (getStatus(signMode), 0, getHeight() * 0.4f, getWidth(), getHeight() * 0.12f, Justification::centredTop, true);
    g.setFont (getHeight() * 0.05f);
    g.setOpacity (0.75f);
    g.drawText (strProjectName, 0, getHeight() * 0.6f, getWidth(), getHeight() * 0.12f, Justification::centredTop, true);
    g.drawText (strDirector, 0, getHeight() * 0.7f, getWidth(), getHeight() * 0.12f, Justification::centredTop, true);
    

    
    // animation demo -------------------------------------------------------------------------------------------------
//
//    auto fishLength = 15;
//
//    Path spinePath;
//
//    int counterclockwise = screeningMode ? 1 : -1;
//
//    for (auto i = 0; i < fishLength; i++)
//    {
//        auto radius = 200 + 20 * std::sin (getFrameCounter() * 0.3f + i * 0.6f);
//        //auto radius = 200;
//
//
//        Point<float> p (getWidth()  / 2.0f + 1.5f * radius * std::sin (getFrameCounter() * 0.04f + i * 0.13f) * counterclockwise,
//                        getHeight() / 2.0f + 1.5f * radius * std::cos (getFrameCounter() * 0.04f + i * 0.18f));
//        g.setOpacity(0.2f);
//        g.fillEllipse (p.x - i, p.y - i, 2.0f + 2.0f * i, 2.0f + 2.0f * i);
//        
//        if (i == 0)
//            spinePath.startNewSubPath (p);
//        else
//            spinePath.lineTo (p);
//    }
//    g.setColour (Colours::cornflowerblue);
//    g.setOpacity(0.1f);
//    g.strokePath (spinePath, PathStrokeType (4.0f));
//
    // end animation -------------------------------------------------------------------------------------------------

}

void SignComponent::resized()
{

}

void SignComponent::update()
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

