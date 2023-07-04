/*
  ==============================================================================

    WaveformDisplay.cpp
    Created: 24 Feb 2022 10:42:17am
    Author:  xinli

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveformDisplay.h"

//==============================================================================
WaveformDisplay::WaveformDisplay(int _id,
                                AudioFormatManager& formatManager,
                                AudioThumbnailCache& thumbCache
                                ) : audioThumb(1000, formatManager, thumbCache),
                                    fileLoaded(false),
                                    position(0),
                                    id(_id)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    audioThumb.addChangeListener(this);
}

WaveformDisplay::~WaveformDisplay()
{
}

void WaveformDisplay::paint(Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.
       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId)); // clear the background
    g.setColour(Colours::grey);
    g.drawRect(getLocalBounds(), 1);   // draw an outline around the component
    g.setColour(Colours::pink);

    g.setFont(18.0f);
    g.drawText("Deck: " + std::to_string(id), getLocalBounds(),
        Justification::topLeft, true);

    if (fileLoaded)
    {
        g.setFont(15.0f);
        audioThumb.drawChannel(g,
            getLocalBounds(),
            0,
            audioThumb.getTotalLength(),
            0,
            1.0f
        );
        g.setColour(Colours::lightgreen);
        g.drawRect(position * getWidth(), 0, getWidth() / 20, getHeight());
        g.setColour(Colours::white);
        g.drawText(fileName, getLocalBounds(),
            Justification::bottomLeft, true);
    }
    else
    {
        g.setFont(20.0f);
        g.drawText("File not loaded...", getLocalBounds(),
            Justification::centred, true);   // draw some placeholder text
    }
}

void WaveformDisplay::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void WaveformDisplay::changeListenerCallback(ChangeBroadcaster* source)
{
    repaint();
}

void WaveformDisplay::loadURL(URL audioURL)
{
    std::cout << "WaveformDisplay::loadURL called" << std::endl;
    audioThumb.clear();
    fileLoaded = audioThumb.setSource(new URLInputSource(audioURL));
    if (fileLoaded)
    {
        std::cout << "WaveformDisplay::loadURL file loaded" << std::endl;
        fileName = audioURL.getFileName();
        repaint();
    }
    else
    {
        std::cout << "WaveformDisplay::loadURL file NOT loaded" << std::endl;
    }
}

void WaveformDisplay::setPositionRelative(double pos)
{
    if (pos != position)
    {
        position = pos;
        repaint();
    }
}
