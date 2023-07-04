/*
  ==============================================================================

    DeckGUI.h
    Created: 21 Feb 2022 8:46:39am
    Author:  xinli

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"

//==============================================================================
/*
*/
class DeckGUI : public Component,
    public Button::Listener,
    public Slider::Listener,
    public FileDragAndDropTarget,
    public Timer
{
public:
    DeckGUI(int _id,
        DJAudioPlayer* player,
        AudioFormatManager& formatManager,
        AudioThumbnailCache& thumbCache);
    ~DeckGUI() override;

    void paint(Graphics&) override;
    void resized() override;
    
    /**Implement Button::Listener*/
    void buttonClicked(Button* button) override;
    /**Implement Slider::Listener */
    void sliderValueChanged(Slider* slider) override;
    /**Detects if file is being dragged over deck*/
    bool isInterestedInFileDrag(const StringArray& files) override;
    /**Detects if file is dropped */
    void filesDropped(const StringArray& files, int x, int y) override;
    /**Listen for changes of the waveform*/
    void timerCallback() override;

private:
    int id;

    TextButton playButton{ "PLAY" };
    TextButton stopButton{ "STOP" };
    TextButton replayButton{ "REPLAY" };
    TextButton loadButton{ "LOAD" };
    Slider volSlider;
    Label volLabel;
    Slider speedSlider;
    Label speedLabel;
    Slider posSlider;
    Label posLabel;

    void loadFile(URL audioURL);

    DJAudioPlayer* player;
    WaveformDisplay waveformDisplay;
    SharedResourcePointer< TooltipWindow > sharedTooltip;

    friend class PlaylistComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeckGUI)
};