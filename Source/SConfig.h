/*
  ==============================================================================

    SConfig.h
    Created: 17 Oct 2018 10:37:24am
    Author:  Dorian Cheah

    Manages the applications settings (for now, just the text that is displayed
    on the sign in various modes).
  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class SConfig
{
public:
    SConfig();
    ~SConfig();
    
    var readConfig(const String & jsonString);

    void saveToDefaultConfigFile() const;
    
    String getMixingMessage();
    String getScreeningMessage();
    String getProjectName();
    String getDirectorName();
    
private:
    File getDefaultConfigFile() const;
    DynamicObject::Ptr config = nullptr;
    
};
