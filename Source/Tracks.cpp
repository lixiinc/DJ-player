/*
  ==============================================================================

    Tracks.cpp
    Created: 6 Mar 2022 1:47:03am
    Author:  xinli

  ==============================================================================
*/

#include "Tracks.h"
#include <filesystem>

Track::Track(File _file) : file(_file),
                           title(_file.getFileNameWithoutExtension()),
                           URL{_file}
{
    std::cout << "Created new track with title: " << title << std::endl;
}

bool Track::operator==(const String& other) const
{
    return title == other;
}