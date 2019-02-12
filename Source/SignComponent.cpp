/*
  ==============================================================================

    SignComponent.cpp
    Created: 16 Oct 2018 10:36:32pm
    Author:  Dorian Cheah

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "SignComponent.h"
//#include <iomanip>

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
    
    Image img = getImage(signMode);

    g.setColour (getSignColour(signMode));
    g.fillAll();

    float sourceAR = static_cast <float> (img.getWidth()) / static_cast <float> (img.getHeight());
    float targetAR = static_cast <float> (getWidth()) / static_cast <float> (getHeight());
    
    //std::cout << "source dimensions: " << img.getWidth() << " x " << img.getHeight() << std::endl;
    //std::cout << "sourceAR " << std::fixed << std::setprecision(3) << sourceAR << std::endl;
    //std::cout << "targetAR " << std::fixed << std::setprecision(3) << targetAR << std::endl;
    
    // if sourceAR > targetAR, our source image is wider than target, so we have to crop horizontally, meaning
    // sourceX should be > 0 and sourceWidth should be < img.getWidth().
    // sourceWidth = targetAR * sourceHeight
    // sourceX = (img.getWidth() - sourceWidth) / 2
    
    // otherwise, our source image is taller than target, so we have to crop vertically, meaning...
    // sourceY should be > 0 and sourceHeight should be < img.getHeight().
    // int sourceHeight = img.getWidth() / targetAR
    
    if (sourceAR > targetAR)
    {
        int sourceWidth = targetAR * img.getHeight();
        int sourceX = (img.getWidth() - sourceWidth) / 2;
        
        g.drawImage(img, 0, 0, getWidth(), getHeight(), sourceX, 0, sourceWidth, img.getHeight());

    } else {
        
        int sourceHeight = img.getWidth() / targetAR;
        int sourceY = (img.getHeight() - sourceHeight) / 2;
        
        g.drawImage(img, 0, 0, getWidth(), getHeight(), 0, sourceY, img.getWidth(), sourceHeight);
    }
    
    drawShadowText(g, getStatus(signMode), 0.35f, 0.11f);
    drawShadowText(g, signMode == SignModes::modeDark ? "" : config->getProjectName(), 0.5f, 0.09f);
    drawShadowText(g, signMode == SignModes::modeDark ? "" : config->getDirectorName(), 0.6f, 0.09f);

}

void SignComponent::resized()
{

}

void SignComponent::drawShadowText(Graphics & g, String const& text, float const& relY, float const& relHeight) const
{
    DrawableText dt;
    dt.setBoundingBox(Rectangle <float> (0, getHeight() * relY, getWidth(), getHeight() * (relHeight + 0.01f)));
    dt.setFont(Font(getHeight() * relHeight), true);
    dt.setJustification(Justification::centredTop);
    dt.setColour(Colour::fromString(config->getTextColour()));
    dt.setText(text);
    
    if (config->getShadow() == "1")
    {
        Path p = dt.getOutlineAsPath();
        
        DropShadow drop (Colours::black, 8, Point <int> (0, 0));
        drop.drawForPath(g, p);
    }
    
    dt.drawAt(g, 0, 0, 1);

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

Image SignComponent::getImage(SignModes const& mode) const
{
    switch (signMode)
    {
        case SignModes::modeMixing:
            return config->getMixingImage();
        case SignModes::modeScreening:
            return config->getScreeningImage();
        default:
            Image noImage;
            return noImage;
            
    }
}
