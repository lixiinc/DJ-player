/*
  ==============================================================================

    PlaylistComponent.h
    Created: 27 Feb 2022 6:15:47pm
    Author:  xinli

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Tracks.h"
#include "DeckGUI.h"
#include "DJAudioPlayer.h"

#include <vector>
#include <algorithm>
#include <fstream>

//==============================================================================
/*
*/
class PlaylistComponent : public Component,
    public TableListBoxModel,
    public Button::Listener,
    public TextEditor::Listener
{
public:
    PlaylistComponent(DeckGUI* _deckGUI1,
        DeckGUI* _deckGUI2,
        DJAudioPlayer* _playerForParsingMetaData
    );
    ~PlaylistComponent() override;

    void paint(Graphics&) override;
    void resized() override;

    int getNumRows() override;
    void paintRowBackground(Graphics& g,
        int rowNumber,
        int width,
        int height,
        bool rowIsSelected
    ) override;
    void paintCell(Graphics& g,
        int rowNumber,
        int columnId,
        int width,
        int height,
        bool rowIsSelected
    ) override;

    Component* refreshComponentForCell(int rowNumber,
                                        int columnId,
                                        bool isRowSelected,
                                        Component* existingComponentToUpdate) override;
    void buttonClicked(Button* button) override;
private:
    std::vector<Track> tracks;

    TextEditor searchField;
    TableListBox library;
    TextButton importButton{ "+ NEW TRACKS" };
    TextButton addToPlayer1Button{ "+ TO DECK 1" };
    TextButton addToPlayer2Button{ "+ TO DECK 2" };

    DeckGUI* deckGUI1;
    DeckGUI* deckGUI2;
    DJAudioPlayer* playerForParsingMetaData;

    String getLength(URL audioURL);
    String secondsToMinutes(double seconds);

   
    void importToLibrary();
    void searchLibrary(String searchText);
    void saveLibrary();
    void loadLibrary();
    void deleteFromTracks(int id);
    bool isInTracks(String fileNameWithoutExtension);
    int whereInTracks(String searchText);
    void loadInPlayer(DeckGUI* deckGUI);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlaylistComponent)
};