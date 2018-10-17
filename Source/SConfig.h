/*
  ==============================================================================

    SConfig.h
    Created: 17 Oct 2018 10:37:24am
    Author:  Dorian Cheah

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class SConfig
{
public:
    SConfig();
    var readConfig(const String & jsonString);
    var readConfigFromSetupFile();
    bool writeConfigToSetupFile();
    
    String getMixingMessage(int const& setupNum);
    String getScreeningMessage(int const& setupNum);
    String getProjectName(int const& setupNum);
    String getDirectorName(int const& setupNum);
    
private:
    String mixingMessage;
    String screeningMessage;
    String projectName;
    String directorName;
    var config;
    
};
