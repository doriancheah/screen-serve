#include "MainComponent.h"

MainComponent::MainComponent()
{
    addAndMakeVisible (sign);
    addAndMakeVisible (menuBar);
    MenuBarModel::setMacMainMenu(this);
    setApplicationCommandManagerToWatch(&commandManager);
    commandManager.registerAllCommandsForTarget(this);
    
    setSize (800, 600);
}

MainComponent::~MainComponent()
{
    MenuBarModel::setMacMainMenu (nullptr);
}

StringArray MainComponent::getMenuBarNames()
{
    return { "Setup" };
}

PopupMenu MainComponent::getMenuForIndex(int menuIndex, const String& /*menuName*/)
{
    PopupMenu menu;
    
    if (menuIndex == 0)
    {
        menu.addCommandItem(&commandManager, CommandIDs::setupLoad);
        menu.addCommandItem(&commandManager, CommandIDs::setupSave);
    }
    
    return menu;
}

void MainComponent::menuItemSelected (int /*menuItemID*/, int /*topLevelMenuIndex*/) {}

void MainComponent::menuBarActivated (bool isActive) {}

void MainComponent::getAllCommands(Array<CommandID>& c)
{
    Array<CommandID> commands { CommandIDs::setupLoad,
                                CommandIDs::setupSave};
    c.addArray (commands);
}

void MainComponent::getCommandInfo (CommandID commandID, ApplicationCommandInfo& result)
{
    switch (commandID)
    {
        case CommandIDs::setupLoad:
            result.setInfo ("Load Setup", "Load a previously stored setup", "Setup", 0);
            result.addDefaultKeypress ('l', ModifierKeys::commandModifier);
            break;
        case CommandIDs::setupSave:
            result.setInfo ("Save setup", "Save current setup", "Setup", 0);
            result.addDefaultKeypress ('s', ModifierKeys::commandModifier);
            break;
        default:
            break;
    }
}

bool MainComponent::perform (InvocationInfo const& info)
{
    switch (info.commandID)
    {
        case CommandIDs::setupLoad:
            std::cout << "LOAD SETUP" << std::endl;
            if (fileChooser.browseForFileToOpen())
            {
                auto chosenFile = fileChooser.getResult();
                std::cout << chosenFile.getFullPathName() << std::endl;
            }
            break;
        case CommandIDs::setupSave:
            std::cout << "SAVE SETUP" << std::endl;
            break;
        default:
            return false;
    }
    return true;
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{

}

void MainComponent::resized()
{
    sign.setBounds(0, 0, getWidth(), getHeight());
}
