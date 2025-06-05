#pragma once
#include <JuceHeader.h>

class CrystalPitchVisualizer : public juce::Component
{
public:
    CrystalPitchVisualizer()
    {
        for (int i = 0; i < 3; ++i)
        {
            pitches[i] = 0.5f;
            intensities[i] = 0.0f;
        }
    }

    void setPitchAndIntensity(int index, float pitch, float intensity)
    {
        if (index >= 0 && index < 3)
        {
            pitches[index] = juce::jlimit(0.0f, 1.0f, pitch);
            intensities[index] = juce::jlimit(0.0f, 1.0f, intensity);
            repaint();
        }
    }

    void paint(juce::Graphics& g) override
    {
        auto bounds = getLocalBounds().toFloat();
        g.fillAll(juce::Colours::transparentBlack);

        const float w = bounds.getWidth();
        const float h = bounds.getHeight();

        // Points for top and body
        juce::Point<float> top(w / 2.0f, 0.0f);
        juce::Point<float> bottomLeft(w * 0.25f, h);
        juce::Point<float> bottomRight(w * 0.75f, h);
        juce::Point<float> midLeft(w * 0.25f, h * 0.5f);
        juce::Point<float> midRight(w * 0.75f, h * 0.5f);
        juce::Point<float> centerBottom(w / 2.0f, h);

        // Outline paths
        juce::Path outline;
        outline.startNewSubPath(top);
        outline.lineTo(midLeft);
        outline.lineTo(bottomLeft);
        outline.lineTo(centerBottom);
        outline.lineTo(bottomRight);
        outline.lineTo(midRight);
        outline.lineTo(top);

        // Inner verticals
        outline.startNewSubPath(midLeft);
        outline.lineTo(centerBottom);
        outline.startNewSubPath(midRight);
        outline.lineTo(centerBottom);

        g.setColour(juce::Colours::black);
        g.strokePath(outline, juce::PathStrokeType(2.0f));

        // Draw glowing lines
        drawGlowingLine(g, midLeft, bottomLeft, pitches[0], intensities[0], juce::Colours::red);   // Left
        drawGlowingLine(g, midLeft, midRight, pitches[1], intensities[1], juce::Colours::green);   // Front
        drawGlowingLine(g, midRight, bottomRight, pitches[2], intensities[2], juce::Colours::blue); // Right
    }

    void setNote(int index, int midiNoteNumber, int velocity)
    {
        // Clamp values and store them
        if (index < 0 || index >= 3) return;

        // Convert MIDI note number to frequency
        float freq = 440.0f * std::pow(2.0f, (midiNoteNumber - 69) / 12.0f);
        float intensity = juce::jlimit(0.0f, 1.0f, velocity / 127.0f);

        pitches[index] = freq;
        intensities[index] = intensity;

        repaint();
    }


private:
    float pitches[3];
    float intensities[3];

    void drawGlowingLine(juce::Graphics& g,
        juce::Point<float> top, juce::Point<float> bottom,
        float normY, float intensity, juce::Colour baseColour)
    {
        if (intensity <= 0.01f) return;

        auto faceHeight = bottom.getY() - top.getY();
        float y = top.getY() + (1.0f - normY) * faceHeight;
        float x1 = top.getX();
        float x2 = bottom.getX();

        juce::Colour glow = baseColour.withAlpha(juce::jlimit(0.05f, 1.0f, intensity));

        for (int i = 4; i >= 0; --i)
        {
            float thickness = (float)i * 2.0f + 1.0f;
            float alpha = glow.getFloatAlpha() * (1.0f - i * 0.2f);
            g.setColour(glow.withAlpha(alpha));
            g.drawLine({ x1, y, x2, y }, thickness);
        }
    }
};
