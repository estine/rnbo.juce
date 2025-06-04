#pragma once

#include <JuceHeader.h>
#include <random>

class CrystallineSliderLookAndFeel : public juce::LookAndFeel_V4
{
public:
    CrystallineSliderLookAndFeel()
    {
        std::random_device rd;
        rng.seed(rd()); // Unique RNG seed per instance
    }

    void drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height,
        float sliderPos, float minSliderPos, float maxSliderPos,
        const juce::Slider::SliderStyle style, juce::Slider& slider) override
    {
        const float trackHeight = 10.0f;
        juce::Rectangle<float> track(x, y + height / 2.0f - trackHeight / 2.0f, width, trackHeight);

        // Pastel background
        g.setColour(juce::Colour::fromRGB(230, 240, 255)); // lavender
        g.fillRect(track);

        // Irregular crystal fill
        juce::Rectangle<float> fill(x, track.getY(), sliderPos - x, trackHeight);

        juce::Path crystalPath;

        std::uniform_real_distribution<float> segDist(6.0f, 20.0f);
        std::uniform_real_distribution<float> peakJitter(-6.0f, 6.0f);
        std::uniform_real_distribution<float> hueJitter(-0.03f, 0.03f);

        float cursor = fill.getX();
        const float maxX = fill.getRight();
        float midY = fill.getCentreY();

        while (cursor < maxX)
        {
            float segWidth = juce::jmin(segDist(rng), maxX - cursor);
            float left = cursor;
            float right = left + segWidth;
            float peak = midY + peakJitter(rng);

            juce::Path facet;
            facet.startNewSubPath(left, midY);
            facet.lineTo((left + right) / 2.0f, peak);
            facet.lineTo(right, midY);
            facet.closeSubPath();

            float baseHue = slider.isMouseButtonDown() ? 0.55f : 0.6f;
            float jitteredHue = juce::jlimit(0.0f, 1.0f, baseHue + hueJitter(rng));
            juce::Colour c = juce::Colour::fromHSV(jitteredHue, 0.6f, 0.9f, 1.0f);

            g.setColour(c);
            g.fillPath(facet);

            cursor += segWidth;
        }

        // Subtle overlay
        g.setColour(juce::Colours::white.withAlpha(0.05f));
        g.fillRect(fill);

        // Border
        g.setColour(juce::Colours::mediumpurple.withAlpha(0.4f));
        g.drawRect(track, 1.0f);
    }

private:
    std::mt19937 rng; // RNG persists between calls and is unique per instance
};
