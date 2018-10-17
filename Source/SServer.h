/*
  ==============================================================================

    SServer.h
    Created: 16 Oct 2018 10:32:52pm
    Author:  Dorian Cheah

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
    int serverPort = 12345;
    struct sockaddr_in serverAddr;
    struct sockaddr_in clientAddr;
    socklen_t clientSize;
    char messageBuffer[256] = "";
};
