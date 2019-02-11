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

String SConfig::getMixingImageFilename() const
{
    return File::getSpecialLocation(File::SpecialLocationType::userApplicationDataDirectory).getFullPathName()
    + "/ScreenServe424/Mixing.jpg";
}

String SConfig::getScreeningImageFilename() const
{
    return File::getSpecialLocation(File::SpecialLocationType::userApplicationDataDirectory).getFullPathName()
    + "/ScreenServe424/Screening.jpg";
}




// GETTERS ---------------------------------------------------------------
String SConfig::getMixingMessage() const
{
    return config->getProperty("mixingMessage");
}

Image SConfig::getMixingImage() const
{
    File fileMixingImage (getMixingImageFilename());
    return ImageFileFormat::loadFrom (fileMixingImage);
}

Image SConfig::getScreeningImage() const
{
    File fileScreeningImage (getScreeningImageFilename());
    return ImageFileFormat::loadFrom (fileScreeningImage);
}


String SConfig::getScreeningMessage() const
{
    return config->getProperty("screeningMessage");
}

String SConfig::getProjectName() const
{
    return config->getProperty("projectName");
}

String SConfig::getDirectorName() const
{
    return config->getProperty("directorName");
}

// SETTERS ----------------------------------------------------------------
void SConfig::setScreeningMessage (String const& msg)
{
    config->setProperty ("screeningMessage", msg);
}

void SConfig::setMixingMessage (String const& msg)
{
    config->setProperty ("mixingMessage", msg);
}

void SConfig::setProjectName (String const& name)
{
    config->setProperty ("projectName", name);
}

void SConfig::setDirectorName (String const& name)
{
    config->setProperty ("directorName", name);
}
