#include "MainComponent.h"
using std::cout;
using std::endl;

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
        menu.addCommandItem(&commandManager, CommandIDs::setupEdit);
        menu.addCommandItem(&commandManager, CommandIDs::setupChooseMixingImage);
        menu.addCommandItem(&commandManager, CommandIDs::setupChooseScreeningImage);
    }
    
    return menu;
}

void MainComponent::menuItemSelected (int /*menuItemID*/, int /*topLevelMenuIndex*/) {}

void MainComponent::menuBarActivated (bool isActive) {}

void MainComponent::getAllCommands(Array<CommandID>& c)
{
    Array<CommandID> commands { CommandIDs::setupEdit,
                                CommandIDs::setupChooseMixingImage,
                                CommandIDs::setupChooseScreeningImage
    };
    c.addArray (commands);
}

void MainComponent::getCommandInfo (CommandID commandID, ApplicationCommandInfo& result)
{
    switch (commandID)
    {
        case CommandIDs::setupEdit:
            result.setInfo ("Edit Text Labels", "Edit setup", "Setup", 0);
            //result.addDefaultKeypress ('l', ModifierKeys::commandModifier);
            break;
        case CommandIDs::setupChooseMixingImage:
            result.setInfo ("Choose Mixing Image", "Choose mxing image", "Setup", 0);
            break;
        case CommandIDs::setupChooseScreeningImage:
            result.setInfo ("Choose Screening Image", "Choose screening image", "Setup", 0);
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
            AlertWindow w ("Edit Text Labels", "", AlertWindow::NoIcon);

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
          
        case CommandIDs::setupChooseMixingImage:
        {
            FileChooser chooser ("Select an image file to display in Mixing mode...", {}, "*.jpg", false);
            if (chooser.browseForFileToOpen())
            {
                auto file = chooser.getResult();
                file.copyFileTo(config->getMixingImageFilename());
                sign.setSignMode(SignComponent::SignModes::modeMixing);
            }
            break;
        }

        case CommandIDs::setupChooseScreeningImage:
        {
            FileChooser chooser ("Select an image file to display in Screening mode...", {}, "*.jpg", false);
            if (chooser.browseForFileToOpen())
            {
                auto file = chooser.getResult();
                file.copyFileTo(config->getScreeningImageFilename());
                sign.setSignMode(SignComponent::SignModes::modeScreening);
                //sign.repaint();
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
}
