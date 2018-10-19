/*
  ==============================================================================

    SConfig.cpp
    Created: 17 Oct 2018 10:37:24am
    Author:  Dorian Cheah

    Manages the applications settings (for now, just the text that is displayed
    on the sign in various modes).
 
  ==============================================================================
*/

#include "SConfig.h"
using std::cout;
using std::endl;

SConfig::SConfig()
{
    // load the default config file when we start up.
    config = JSON::parse(getDefaultConfigFile()).getDynamicObject();
}

SConfig::~SConfig()
{
    // write the current config to the default config file when we quit, so the settings are "sticky".
    saveToDefaultConfigFile();
}

var SConfig::readConfig (const String & jsonString)
{
    return JSON::parse (jsonString);
}

// returns default.conf file in user's /Library/ScreenServe424 directory, creating it if it doesn't exist.
File SConfig::getDefaultConfigFile() const
{
    File defaultFile (File::getSpecialLocation(File::SpecialLocationType::userApplicationDataDirectory).getFullPathName()
                      + "/ScreenServe424/default.conf");
    if (! defaultFile.exists())
    {
        defaultFile.create();
        String strDefault = "{\"mixingMessage\": \"Mix In Progress. Please Enter Quietly.\",\"screeningMessage\": \"Screening In Progress. Do Not Enter.\",\"projectName\": \"Project Name\",\"directorName\": \"Director Name\"}";
        
        jassert (defaultFile.replaceWithText(strDefault));
    }
    
    return defaultFile;
}

// saves current config to the default.conf file.
void SConfig::saveToDefaultConfigFile() const
{
    File defaultFile (File::getSpecialLocation(File::SpecialLocationType::userApplicationDataDirectory).getFullPathName()
                      + "/ScreenServe424/default.conf");
    MemoryOutputStream outStream;
    config->writeAsJSON(outStream, 3, false, 0);
    defaultFile.replaceWithText(outStream.toString());
}


// PUBLIC GETTERS ---------------------------------------------------------------
String SConfig::getMixingMessage()
{
    return config->getProperty("mixingMessage");
}

String SConfig::getScreeningMessage()
{
    return config->getProperty("screeningMessage");
}

String SConfig::getProjectName()
{
    return config->getProperty("projectName");
}

String SConfig::getDirectorName()
{
    return config->getProperty("directorName");
}
