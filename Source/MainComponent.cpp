#include "MainComponent.h"
using std::cout;
using std::endl;

MainComponent::MainComponent()
{
    addAndMakeVisible (anim);
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
        menu.addCommandItem(&commandManager, CommandIDs::setupEdit);
    }
    
    return menu;
}

void MainComponent::menuItemSelected (int /*menuItemID*/, int /*topLevelMenuIndex*/) {}

void MainComponent::menuBarActivated (bool isActive) {}

void MainComponent::getAllCommands(Array<CommandID>& c)
{
    Array<CommandID> commands { CommandIDs::setupEdit };
    c.addArray (commands);
}

void MainComponent::getCommandInfo (CommandID commandID, ApplicationCommandInfo& result)
{
    switch (commandID)
    {
        case CommandIDs::setupEdit:
            result.setInfo ("Edit Setup", "Edit setup", "Setup", 0);
            result.addDefaultKeypress ('l', ModifierKeys::commandModifier);
            break;
        default:
            break;
    }
}

bool MainComponent::perform (InvocationInfo const& info)
{
    switch (info.commandID)
    {
        case CommandIDs::setupEdit:
        {
            AlertWindow w ("hi", "Change the sign", AlertWindow::NoIcon);

            w.addTextEditor ("textScreening", sign.config->getScreeningMessage(), "Screening Message: ");
            w.addTextEditor ("textMixing", sign.config->getMixingMessage(), "Mixing Message: ");
            w.addTextEditor ("textProject", sign.config->getProjectName(), "Project Name: ");
            w.addTextEditor ("textDirector", sign.config->getDirectorName(), "Director Name: ");
            
            w.addButton ("OK",     1, KeyPress (KeyPress::returnKey, 0, 0));
            w.addButton ("Cancel", 0, KeyPress (KeyPress::escapeKey, 0, 0));

            if (w.runModalLoop() != 0)
            {
                auto testMe = w.getTextEditorContents("textScreening");
                cout << testMe << endl;
                sign.config->setScreeningMessage (w.getTextEditorContents ("textScreening"));
                sign.config->setMixingMessage (w.getTextEditorContents ("textMixing"));
                sign.config->setProjectName (w.getTextEditorContents ("textProject"));
                sign.config->setDirectorName (w.getTextEditorContents ("textDirector"));
                sign.repaint();
            }
            break;
        }
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
    anim.setBounds(0, 0, getWidth(), getHeight());
}
