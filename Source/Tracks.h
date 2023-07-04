/*
  ==============================================================================

    Tracks.h
    Created: 6 Mar 2022 1:47:03am
    Author:  xinli

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Track
{
public:
    Track(File _file);
    File file;
    URL URL;
    String title;
    String length;
    /**objects are compared by title*/
    bool operator==(const String& other) const;
};
