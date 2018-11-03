/*
  ==============================================================================

    SServerJ.h
    Created: 23 Oct 2018 6:06:18am
    Author:  Dorian Cheah

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class SServerJ : public ActionBroadcaster,
                    public Thread
{
public:
    
    SServerJ() : Thread("SServerJ") {}
    ~SServerJ();
    void run();
    
private:

    StreamingSocket sock;
    
    

};
