#pragma once

#include <JuceHeader.h>
#include <random>

class CrystallineComboBoxLookAndFeel : public juce::LookAndFeel_V4
{
public:
    CrystallineComboBoxLookAndFeel()
    {
        std::random_device rd;
        rng.seed(rd());
    }

    void drawComboBox(juce::Graphics& g, int width, int height,
        bool isButtonDown,
        int buttonX, int buttonY, int buttonW, int buttonH,
        juce::ComboBox& box) override
    {
        juce::Rectangle<int> boxBounds(0, 0, width, height);

        // Background
        g.setColour(juce::Colour::fromRGB(240, 250, 255)); // pastel
        g.fillRect(boxBounds);

        // Crystal facets
        drawCrystallineFill(g, boxBounds.toFloat(), isButtonDown || box.hasKeyboardFocus(false));

        // Outline
        g.setColour(juce::Colours::mediumpurple.withAlpha(0.4f));
        g.drawRect(boxBounds, 1.0f);

        // Arrow button (drawn as triangle)
        juce::Path arrow;
        float cx = width - buttonW / 2.0f;
        float cy = height / 2.0f;
        float size = 5.0f;

        arrow.startNewSubPath(cx - size, cy - size);
        arrow.lineTo(cx + size, cy - size);
        arrow.lineTo(cx, cy + size);
        arrow.closeSubPath();

        g.setColour(isButtonDown ? juce::Colours::mediumvioletred : juce::Colours::mediumpurple);
        g.fillPath(arrow);
    }

    void positionComboBoxText(juce::ComboBox& box, juce::Label& label) override
    {
        label.setBounds(2, 1, box.getWidth() - 18, box.getHeight() - 2);
        label.setFont(getComboBoxFont(box));
        label.setColour(juce::Label::textColourId, juce::Colours::purple);
    }

private:
    std::mt19937 rng;

    void drawCrystallineFill(juce::Graphics& g, juce::Rectangle<float> bounds, bool active)
    {
        std::uniform_real_distribution<float> xDist(4.0f, 20.0f);
        std::uniform_real_distribution<float> yJitter(-4.0f, 4.0f);
        std::uniform_real_distribution<float> hueJitter(-0.03f, 0.03f);

        float x = bounds.getX();
        float endX = bounds.getRight();
        float midY = bounds.getCentreY();

        while (x < endX)
        {
            float w = juce::jmin(xDist(rng), endX - x);
            float left = x;
            float right = x + w;
            float peak = midY + yJitter(rng);

            juce::Path facet;
            facet.startNewSubPath(left, midY);
            facet.lineTo((left + right) / 2.0f, peak);
            facet.lineTo(right, midY);
            facet.closeSubPath();

            float baseHue = active ? 0.55f : 0.6f;
            float jitteredHue = juce::jlimit(0.0f, 1.0f, baseHue + hueJitter(rng));
            juce::Colour c = juce::Colour::fromHSV(jitteredHue, 0.5f, 0.9f, 1.0f);

            g.setColour(c);
            g.fillPath(facet);

            x += w;
        }
    }
};
