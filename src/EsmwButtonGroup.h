#pragma once

#include <JuceHeader.h>
#include "EsmwLookAndFeel.h"

class EsmwButtonGroup : public juce::Component
{
public:
    EsmwButtonGroup() {}

    EsmwButtonGroup(const juce::StringArray& options)
    {
        buttons.clear();
        for (int i = 0; i < options.size(); ++i)
        {
            auto* btn = new juce::TextButton(options[i]);
            btn->setClickingTogglesState(true);
            btn->setRadioGroupId(1234);  // all buttons share this id for radio behavior
            btn->setLookAndFeel(&lookAndFeel);
            addAndMakeVisible(btn);
            buttons.add(btn);

            btn->onClick = [this, i]()
                {
                    selectedIndex = i;
                    if (onSelectionChanged)
                        onSelectionChanged(selectedIndex);

                    repaint(); // optional, if your UI doesn’t auto-repaint
                };
        }

        if (buttons.size() > 0)
            buttons[0]->setToggleState(true, juce::dontSendNotification);
    }

    ~EsmwButtonGroup()
    {
        for (auto* btn : buttons)
            btn->setLookAndFeel(nullptr);
    }

    void resized() override
    {
        auto area = getLocalBounds();
        int buttonWidth = area.getWidth() / buttons.size();

        for (int i = 0; i < buttons.size(); ++i)
        {
            buttons[i]->setBounds(area.removeFromLeft(buttonWidth).reduced(2, 2));
        }
    }

    std::function<void(int)> onSelectionChanged;
    int getSelectedIndex() const { return selectedIndex; }

private:
    juce::OwnedArray<juce::TextButton> buttons;
    int selectedIndex = 0;
    EsmwLookAndFeel lookAndFeel;
};
