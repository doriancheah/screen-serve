/*
  ==============================================================================

    AnimComponent.cpp
    Created: 19 Oct 2018 4:33:44pm
    Author:  Dorian Cheah

    Removed the animation component from the rest of the sign so that part
    doesn't have to repaint itself continuously -- only when messages are
    received.
 
    But don't know how to "overlay" this with some degree of transparency
    onto the sign component yet.
 
  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "AnimComponent.h"

//==============================================================================
AnimComponent::AnimComponent()
{
    setFramesPerSecond(60);
}

AnimComponent::~AnimComponent()
{
}

void AnimComponent::paint (Graphics& g)
{
    g.fillAll(Colours::transparentBlack);
    
    auto fishLength = 15;
    
    Path spinePath;

    for (auto i = 0; i < fishLength; i++)
    {
        auto radius = 200 + 20 * std::sin (getFrameCounter() * 0.3f + i * 0.6f);

        Point<float> p (getWidth()  / 2.0f + 1.5f * radius * std::sin (getFrameCounter() * 0.04f + i * 0.13f),
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
    
}

void AnimComponent::update()
{
}

void AnimComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
