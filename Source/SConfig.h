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
    
    String getMixingMessage() const;
    String getScreeningMessage() const;
    Image getMixingImage() const;
    Image getScreeningImage() const;
    String getProjectName() const;
    String getDirectorName() const;
    String getTextColour() const;
    String getShadow() const;
    
    String getMixingImageFilename() const;
    String getScreeningImageFilename() const;
    
    void setMixingMessage (String const& msg);
    void setScreeningMessage (String const& msg);
    void setProjectName (String const& msg);
    void setDirectorName (String const& msg);
    void setTextColour (String const& col);
    void setShadow (String const& shadow);
    
private:
    File getDefaultConfigFile() const;
    DynamicObject::Ptr config = nullptr;
};
