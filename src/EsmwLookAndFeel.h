#pragma once

#include <JuceHeader.h>

class EsmwLookAndFeel : public juce::LookAndFeel_V4
{
public:
    EsmwLookAndFeel()
    {
        setColour(juce::ComboBox::textColourId, juce::Colours::white);
        setColour(juce::ComboBox::backgroundColourId, juce::Colours::black);
        setColour(juce::ComboBox::outlineColourId, juce::Colours::white);
        setColour(juce::Label::textColourId, juce::Colours::white);
        setColour(juce::Label::backgroundColourId, juce::Colours::black);
        setColour(juce::TabbedButtonBar::tabOutlineColourId, juce::Colours::white);
    }

    // === Rotary Knob (black circle + white line) ===
    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
        float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle,
        juce::Slider&) override
    {
        const float radius = juce::jmin(width, height) / 2.0f - 2.0f;
        const float centerX = x + width * 0.5f;
        const float centerY = y + height * 0.5f;

        // Outer black circle
        g.setColour(juce::Colours::black);
        g.fillEllipse(centerX - radius, centerY - radius, radius * 2.0f, radius * 2.0f);

        // White line from center outward
        float angle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);
        float lineX = centerX + radius * std::cos(angle);
        float lineY = centerY + radius * std::sin(angle);

        g.setColour(juce::Colours::white);
        g.drawLine(centerX, centerY, lineX, lineY, 2.0f);
    }

    // === Linear slider (single line + vertical thumb line) ===
    void drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height,
        float sliderPos, float minSliderPos, float maxSliderPos,
        const juce::Slider::SliderStyle style, juce::Slider& slider) override
    {
        g.setColour(juce::Colours::black);

        if (style == juce::Slider::LinearHorizontal)
        {
            const int centerY = y + height / 2;
            g.drawLine((float)x, (float)centerY, (float)(x + width), (float)centerY, 1.0f);

            // Thumb line
            g.drawLine(sliderPos, (float)y, sliderPos, (float)(y + height), 2.0f);
        }
        else if (style == juce::Slider::LinearVertical)
        {
            const int centerX = x + width / 2;
            g.drawLine((float)centerX, (float)y, (float)centerX, (float)(y + height), 1.0f);

            // Thumb line
            g.drawLine((float)x, sliderPos, (float)(x + width), sliderPos, 2.0f);
        }
    }

    // === ComboBox (black with white text) ===
    void drawComboBox(juce::Graphics& g, int width, int height, bool,
        int, int, int, int, juce::ComboBox&) override
    {
        g.setColour(juce::Colours::black);
        g.fillRect(0, 0, width, height);

        g.setColour(juce::Colours::white);
        g.drawRect(0, 0, width, height, 1);
    }

    juce::Font getComboBoxFont(juce::ComboBox&) override
    {
        return juce::Font(14.0f, juce::Font::plain);
    }

    // === Popup menu (matches combo box) ===
    void drawPopupMenuBackground(juce::Graphics& g, int width, int height) override
    {
        g.fillAll(juce::Colours::black);
    }

    void drawPopupMenuItem(juce::Graphics& g, const juce::Rectangle<int>& area,
        bool isSeparator, bool isActive, bool isHighlighted,
        bool isTicked, bool hasSubMenu,
        const juce::String& text, const juce::String&, const juce::Drawable*,
        const juce::Colour* textColourToUse) override
    {
        if (isSeparator)
        {
            g.setColour(juce::Colours::white);
            g.drawLine((float)area.getX(), (float)area.getCentreY(),
                (float)area.getRight(), (float)area.getCentreY());
        }
        else
        {
            if (isHighlighted)
                g.setColour(juce::Colours::darkgrey);
            else
                g.setColour(juce::Colours::black);

            g.fillRect(area);

            g.setColour(textColourToUse ? *textColourToUse : juce::Colours::white);
            g.drawText(text, area, juce::Justification::centredLeft, true);
        }
    }

    // === Labels ===
    juce::Font getLabelFont(juce::Label&) override
    {
        return juce::Font(14.0f, juce::Font::plain);
    }

    void drawLabel(juce::Graphics& g, juce::Label& label) override
    {
        g.setColour(label.findColour(juce::Label::backgroundColourId));
        g.fillAll();

        g.setColour(label.findColour(juce::Label::textColourId));
        g.setFont(getLabelFont(label));
        g.drawText(label.getText(), label.getLocalBounds().reduced(2), juce::Justification::centredLeft, true);
    }

    // === Tabs ===
    void drawTabButton(juce::TabBarButton& button, juce::Graphics& g,
        bool isMouseOver, bool isMouseDown) override
    {
        auto area = button.getLocalBounds();
        bool isActive = button.getToggleState();

        g.setColour(isActive ? juce::Colours::white : juce::Colours::black);
        g.fillRect(area);

        g.setColour(isActive ? juce::Colours::black : juce::Colours::white);
        g.drawText(button.getButtonText(), area, juce::Justification::centred, true);
        g.drawRect(area);
    }

    // --- TextButton painting ---
    void drawButtonBackground(juce::Graphics& g, juce::Button& button,
        const juce::Colour&, bool, bool) override
    {
        auto bounds = button.getLocalBounds().toFloat();

        g.setColour(button.getToggleState() ? juce::Colours::black : juce::Colours::transparentWhite);
        g.fillRect(bounds); // possibly use draw rect for cleaner look in the future
    }

    void drawButtonText(juce::Graphics& g, juce::TextButton& button,
        bool, bool) override
    {
        g.setColour(button.getToggleState() ? juce::Colours::white : juce::Colours::black);
        g.setFont(juce::Font(14.0f, juce::Font::bold));
        g.drawFittedText(button.getButtonText(), button.getLocalBounds(),
            juce::Justification::centred, 1);
    }
};
