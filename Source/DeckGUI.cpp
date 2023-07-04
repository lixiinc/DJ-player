#include <JuceHeader.h>
#include "DeckGUI.h"

//==============================================================================
#include <JuceHeader.h>
#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(int _id,
                DJAudioPlayer* _player,
                AudioFormatManager& formatManager,
                AudioThumbnailCache& thumbCache
                ) : player(_player),
                    id(_id),
                    waveformDisplay(id, formatManager, thumbCache)
{
    // add all components and make visible
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(replayButton);
    addAndMakeVisible(loadButton);

    addAndMakeVisible(volSlider);
    addAndMakeVisible(volLabel);

    addAndMakeVisible(speedSlider);
    addAndMakeVisible(speedLabel);

    addAndMakeVisible(posSlider);
    addAndMakeVisible(posLabel);

    addAndMakeVisible(waveformDisplay);

    // add listeners
    playButton.addListener(this);
    stopButton.addListener(this);
    replayButton.addListener(this);
    loadButton.addListener(this);

    volSlider.addListener(this);
    speedSlider.addListener(this);
    posSlider.addListener(this);


    //configure volume slider and label
    volSlider.setRange(0.0, 1.0);
    volSlider.setNumDecimalPlacesToDisplay(2);
    volSlider.setTextBoxStyle(Slider::TextBoxLeft,
                            false,
                            50,
                            volSlider.getTextBoxHeight()
    );

    volLabel.setText("Volume", dontSendNotification);
    volLabel.attachToComponent(&volSlider, true);

    //configure speed slider and label
    speedSlider.setRange(0.0, 10.0); //reaches breakpoint if sliderValue == 0
    speedSlider.setNumDecimalPlacesToDisplay(2);
    speedSlider.setTextBoxStyle(Slider::TextBoxLeft,
        false,
        50,
        speedSlider.getTextBoxHeight()
    );
    speedLabel.setText("Speed", dontSendNotification);
    speedLabel.attachToComponent(&speedSlider, true);

    //configure position slider and label
    posSlider.setRange(0.0, 1.0);
    posSlider.setNumDecimalPlacesToDisplay(2);
    posSlider.setTextBoxStyle(Slider::TextBoxLeft,
                            false,
                            50,
                            posSlider.getTextBoxHeight()
    );
    posLabel.setText("Position", dontSendNotification);
    posLabel.attachToComponent(&posSlider, true);


    startTimer(500);
}

DeckGUI::~DeckGUI()
{
    stopTimer();
}

void DeckGUI::paint(Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.
       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));   // clear the background

    g.setColour(Colours::grey);
    g.drawRect(getLocalBounds(), 1);   // draw an outline around the component
}

void DeckGUI::resized()
{
    /*This method is where you should set the bounds of any child
    components that your component contains..*/
    auto slider = getWidth() / 9;
    auto mainComponent = getWidth() - getHeight() / getHeight();

    //                   x start, y start, width, height
    playButton.setBounds(0, 0, mainComponent / 4, getHeight() / 8);
    stopButton.setBounds(mainComponent / 4, 0, mainComponent / 4, getHeight() / 8);
    replayButton.setBounds(2 * mainComponent / 4, 0, mainComponent / 4, getHeight() / 8);
    loadButton.setBounds(3 * mainComponent / 4, 0, mainComponent / 4, getHeight() / 8);

    volSlider.setBounds(slider, getHeight() / 8, mainComponent - slider, getHeight() / 8);
    speedSlider.setBounds(slider, 2 * getHeight() / 8, mainComponent - slider, getHeight() / 8);
    posSlider.setBounds(slider, 3 * getHeight() / 8, mainComponent - slider, getHeight() / 8);
    waveformDisplay.setBounds(0, 4 * getHeight() / 8, mainComponent, 4 * getHeight() / 8);
}

void DeckGUI::buttonClicked(Button* button)
{
    if (button == &playButton)
    {
        std::cout << "Play button was clicked " << std::endl;
        player->start();
    }
    if (button == &stopButton)
    {
        std::cout << "Stop button was clicked " << std::endl;
        player->stop();
    }
    if (button == &replayButton)
    {
        std::cout << "Replay button was clicked " << std::endl;
        player->setPosition(0);
        player->start();
    }
    if (button == &loadButton)
    {
        std::cout << "Load button was clicked " << std::endl;
        FileChooser chooser{ "Select a file" };
        if (chooser.browseForFileToOpen())
        {
            loadFile(URL{ chooser.getResult() });
        }
    }
}


void DeckGUI::sliderValueChanged(Slider* slider)
{
    if (slider == &volSlider)
    {
        std::cout << "Volume slider moved " << slider->getValue() << std::endl;
        player->setGain(slider->getValue());
    }
    if (slider == &speedSlider)
    {
        std::cout << "Speed slider moved " << slider->getValue() << std::endl;
        player->setSpeed(slider->getValue());
    }
    if (slider == &posSlider)
    {
        std::cout << "Position slider moved " << slider->getValue() << std::endl;
        player->setPositionRelative(slider->getValue());
    }
}


bool DeckGUI::isInterestedInFileDrag(const StringArray& files)
{
    std::cout << "DeckGUI::isInterestedInFileDrag called. " << std::endl;
    return true;
}

void DeckGUI::filesDropped(const StringArray& files, int x, int y)
{

    std::cout << "DeckGUI::filesDropped " << std::endl;
    if (files.size() == 1)
    {
        loadFile(URL{ File{files[0]} });
    }
}

void DeckGUI::loadFile(URL audioURL)
{
    std::cout << "DeckGUI::loadFile called" << std::endl;
    player->loadURL(audioURL);
    waveformDisplay.loadURL(audioURL);
}

void DeckGUI::timerCallback()
{
    //check if the relative position is greater than 0
    //otherwise loading file causes error
    if (player->getPositionRelative() > 0)
    {
        waveformDisplay.setPositionRelative(player->getPositionRelative());
    }
}