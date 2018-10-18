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
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
    setFramesPerSecond(60);
    
    // register the sign component as a listener to the SServer instance and start the thread.
    server.addActionListener(this);
    server.startThread();
    config = std::make_shared<SConfig>();
    //std::cout << "SignComponent got config...." << config->getMixingMessage(0) << std::endl;
    
    strStatus = config->getMixingMessage(0);
    strProjectName = config->getProjectName(0);
    strDirector = "Director: " + config->getDirectorName(0);
}

SignComponent::~SignComponent()
{
    //config.writeConfigToSetupFile();
}

void SignComponent::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (signColour);
    g.fillAll();

    g.setColour (Colours::white);
    g.setFont (getHeight() * 0.08f);
    g.setOpacity (1.0f);
    g.drawText (strStatus, 0, getHeight() * 0.4f, getWidth(), getHeight() * 0.12f, Justification::centredTop, true);
    g.setFont (getHeight() * 0.05f);
    g.setOpacity (0.75f);
    g.drawText (strProjectName, 0, getHeight() * 0.6f, getWidth(), getHeight() * 0.12f, Justification::centredTop, true);
    g.drawText (strDirector, 0, getHeight() * 0.7f, getWidth(), getHeight() * 0.12f, Justification::centredTop, true);
    

    
    // silly animation -------------------------------------------------------------------------------------------------
    
    auto fishLength = 15;
    
    Path spinePath;
    
    int counterclockwise = screeningMode ? 1 : -1;
    
    for (auto i = 0; i < fishLength; i++)
    {
        auto radius = 200 + 20 * std::sin (getFrameCounter() * 0.3f + i * 0.6f);
        //auto radius = 200;
        
        
        Point<float> p (getWidth()  / 2.0f + 1.5f * radius * std::sin (getFrameCounter() * 0.04f + i * 0.13f) * counterclockwise,
                        getHeight() / 2.0f + 1.5f * radius * std::cos (getFrameCounter() * 0.04f + i * 0.18f));
        g.setOpacity(0.2f);
        g.fillEllipse (p.x - i, p.y - i, 2.0f + 2.0f * i, 2.0f + 2.0f * i);
        
        if (i == 0)
            spinePath.startNewSubPath (p);
        else
            spinePath.lineTo (p);
    }
    g.setColour (Colours::cornflowerblue);
    g.setOpacity(0.1f);
    g.strokePath (spinePath, PathStrokeType (4.0f));
    
    // end animation -------------------------------------------------------------------------------------------------

}

void SignComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void SignComponent::update()
{
    
}

void SignComponent::actionListenerCallback (const String & message)
{
    
    std::cout << "received message: " << message << std::endl;
    //strStatus = message;
    if (message == "screening_start")
    {
        strStatus = config->getScreeningMessage(0);
        setScreeningMode(true);
    }
    if (message == "screening_stop")
    {
        strStatus = config->getMixingMessage(0);
        setScreeningMode(false);
    }
}

void SignComponent::setScreeningMode(bool isScreening)
{
    screeningMode = isScreening;
    signColour = isScreening ? Colours::red : Colours::darkslateblue;
}
