/*
  ==============================================================================

    SConfig.cpp
    Created: 17 Oct 2018 10:37:24am
    Author:  Dorian Cheah

  ==============================================================================
*/

#include "SConfig.h"

SConfig::SConfig()
{
    config = readConfigFromSetupFile();

}

var SConfig::readConfig (const String & jsonString)
{
    return JSON::parse (jsonString);
}

var SConfig::readConfigFromSetupFile()
{
    File configFile ("~/ss424setup.json");
    return JSON::parse (configFile);
}

bool SConfig::writeConfigToSetupFile()
{
    File configFile ("~/ss424setup1.json");
    configFile.deleteFile();
    
    FileOutputStream configFileStream (configFile);
    JSON::writeToStream(configFileStream, config);
    
    return true;
}

String SConfig::getMixingMessage(int const& setupNum)
{
    return config["config"][setupNum]["mixingMessage"];
}

String SConfig::getScreeningMessage(int const& setupNum)
{
    return config["config"][setupNum]["screeningMessage"];
}

String SConfig::getProjectName(int const& setupNum)
{
    return config["config"][setupNum]["projectName"];
}

String SConfig::getDirectorName(int const& setupNum)
{
    return config["config"][setupNum]["directorName"];
}
