/*
  ==============================================================================

    SServerJ.cpp
    Created: 23 Oct 2018 6:06:18am
    Author:  Dorian Cheah

  ==============================================================================
*/

#include "SServerJ.h"
using std::cout;
using std::endl;

void SServerJ::run()
{
    sock.createListener(3001);
    
    StreamingSocket* newSock = sock.waitForNextConnection();
    
    newSock->waitUntilReady(true, -1);
    
    char buf[256];
    int i = 0;
    
    while (1)
    {
        cout << ++i << endl;
        newSock->read(&buf, 256, true);
        cout << buf << endl;
        memset (buf, 0, sizeof (buf));
        
        if (threadShouldExit())
        {
            break;
        }
    }
    
    
    
    
}
