/*
  ==============================================================================

    AnimComponent.h
    Created: 19 Oct 2018 4:33:44pm
    Author:  Dorian Cheah

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class AnimComponent    : public AnimatedAppComponent
{
public:
    AnimComponent();
    ~AnimComponent();

    void paint (Graphics&) override;
    void update() override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AnimComponent)
};
