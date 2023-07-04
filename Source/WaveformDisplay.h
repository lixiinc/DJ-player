/*
  ==============================================================================

    WaveformDisplay.h
    Created: 24 Feb 2022 10:42:17am
    Author:  xinli

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class WaveformDisplay : public Component,
                        public ChangeListener
{
public:
    WaveformDisplay(int _id,
        AudioFormatManager& formatManager,
        AudioThumbnailCache& thumbCache);
    ~WaveformDisplay() override;

    void paint(Graphics&) override;
    void resized() override;
    void changeListenerCallback(ChangeBroadcaster* source) override;
    void loadURL(URL audioURL);
    /**set the relative position of the playhead*/
    void setPositionRelative(double pos);
private:
    int id;
    bool fileLoaded;
    double position;
    String fileName;
    AudioThumbnail audioThumb;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WaveformDisplay)
};