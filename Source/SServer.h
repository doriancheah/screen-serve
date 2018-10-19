/*
  ==============================================================================

    SServer.h
    Created: 16 Oct 2018 10:32:52pm
    Author:  Dorian Cheah
 
    Establishes network connection from Vantage Control lighting system and
    receives messages from it, passing them on to SignComponent.
 
    Some of the calls to the socket library are blocking so this runs on a
    separate thread, allowing the GUI to be displayed and respond to user.
 

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

class SServer               : public ActionBroadcaster,
                              public Thread
{
    
public:
    
    SServer() : Thread("SServer") {}
    ~SServer();
    void run();
    
private:
    socklen_t serverSocket;
    int clientSocket;
    int serverPort = 3001;
    struct sockaddr_in serverAddr;
    struct sockaddr_in clientAddr;
    socklen_t clientSize;
    char messageBuffer[256] = "";
};
