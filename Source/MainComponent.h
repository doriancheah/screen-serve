/*
  ==============================================================================

  MainComponent owns the SignComponent, MenuBarComponent and the FileChooser.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "SignComponent.h"
#include "SConfig.h"
#include "AnimComponent.h"

class MainComponent   : public Component,
                        public MenuBarModel,
                        public ApplicationCommandTarget
{
public:
    MainComponent();
    ~MainComponent();
    
    // overrides for MenuBarModel
    StringArray getMenuBarNames() override;
    PopupMenu getMenuForIndex (int topLevelMenuIndex, const String& menuName) override;
    void menuItemSelected (int menuItemID, int topLevelMenuIndex) override;
    void menuBarActivated (bool isActive) override;
    
    // overrides for ApplicationCommandTarget
    ApplicationCommandTarget* getNextCommandTarget () override {return nullptr;}
    void getAllCommands (Array<CommandID>& c) override;
    void getCommandInfo (CommandID commandID, ApplicationCommandInfo &result) override;
    bool perform (InvocationInfo const& info) override;

    // -------------------------------------------------------------------------------
    void paint (Graphics& g) override;
    void resized() override;

    enum CommandIDs
    {
        setupLoad = 1,
        setupSave
    };
    
private:
    SignComponent sign;
    MenuBarComponent menuBar;
    ApplicationCommandManager commandManager;
    FileChooser fileChooser { "hello", File("~"), "*.json", false };
    std::shared_ptr<SConfig> config;
    AnimComponent anim;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
