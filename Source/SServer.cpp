/*
  ==============================================================================

    SServer.cpp
    Created: 16 Oct 2018 10:32:52pm
    Author:  Dorian Cheah

    Establishes network connection from Vantage Control lighting system and
    receives messages from it, passing them on to SignComponent.
 
    Some of the calls to the socket library are blocking so this runs on a
    separate thread, allowing the GUI to be displayed and respond to user.
 
  ==============================================================================
*/

#include "SServer.h"
using std::cerr;
using std::cout;
using std::endl;

SServer::~SServer()
{
    int shutdownReturn = shutdown (clientSocket, SHUT_RDWR);
    if (shutdownReturn == -1)
    {
        cerr << "Shutdown error - " << strerror(errno) << endl;
    }
    stopThread(100);
}

void SServer::run()
{
    // create server socket
    serverSocket = socket (AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1)
    {
        cerr << "Couldn't create server socket - " << strerror (errno) << endl;
    }
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons (serverPort);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // bind to socket
    int bindReturn = bind (serverSocket, (struct sockaddr*)&serverAddr, sizeof (serverAddr));
    if (bindReturn == -1)
    {
        cerr << "Unable to bind server socket - " << strerror(errno) << endl;
    }
    else if (bindReturn == 0)
    {
        cout << "bound..." << endl;
    }
    // listen for connection
    int isListening = listen (serverSocket, SOMAXCONN);
    cout << "isListening: " << isListening << endl;
    
    // wait for connection -- BLOCKING
    clientSocket = accept (serverSocket, (struct sockaddr*)&clientAddr, &clientSize);
    if (clientSocket == -1)
    {
        cerr << "Couldn't accept connection - " << strerror (errno) << endl;
    }
    else
    {
        cout << "Connected. clientSocket: " << clientSocket << endl;
    }

    // read from client -- BLOCKING
    while (1)
    {
        cout << "in loop." << endl;
        if (threadShouldExit())
        {
            break;
        }
        ssize_t charsRead = recv (clientSocket, messageBuffer, sizeof (messageBuffer), 0);
        if (charsRead > 0)
        {
            cout << messageBuffer << endl;
            sendActionMessage (static_cast<String>(messageBuffer));
            memset (messageBuffer, 0, sizeof (messageBuffer));
        }
        else if (charsRead == -1)
        {
            cerr << "Read error - " << strerror(errno) << endl;
            break;
        }

    }
}
