#pragma once

#include <JuceHeader.h>

class EsmwADSRDisplay : public juce::Component
{
public:
    EsmwADSRDisplay() {}

    void setEnvelope(float a, float d, float s, float r)
    {
        attack = juce::jlimit(0.0f, 1.0f, a);
        decay = juce::jlimit(0.0f, 1.0f, d);
        sustain = juce::jlimit(0.0f, 1.0f, s);
        release = juce::jlimit(0.0f, 1.0f, r);
        repaint();
    }

    void paint(juce::Graphics& g) override
    {
        g.fillAll(juce::Colours::transparentWhite);
        g.setColour(juce::Colours::black);

        auto bounds = getLocalBounds().toFloat();
        float width = bounds.getWidth()-10;
        float height = bounds.getHeight()-10;

        // Total duration units = a + d + r + fixed sustain portion
        float sustainLength = 0.3f; // fixed horizontal length for sustain
        float total = attack + decay + release + sustainLength;
        if (total < 0.0001f) return; // avoid divide by zero

        float scaleX = width / total;

        float x0 = 0.0f;
        float y0 = height;

        float x1 = x0 + attack * scaleX;
        float y1 = 0.0f;

        float x2 = x1 + decay * scaleX;
        float y2 = height * (1.0f - sustain); // sustain height

        float x3 = x2 + sustainLength * scaleX;
        float y3 = y2;

        float x4 = x3 + release * scaleX;
        float y4 = height;

        juce::Path env;
        env.startNewSubPath(x0, y0);
        env.lineTo(x1, y1);
        env.lineTo(x2, y2);
        env.lineTo(x3, y3);
        env.lineTo(x4, y4);

        g.strokePath(env, juce::PathStrokeType(2.0f));
    }

private:
    float attack = 0.1f;
    float decay = 0.1f;
    float sustain = 0.5f;
    float release = 0.1f;
};
