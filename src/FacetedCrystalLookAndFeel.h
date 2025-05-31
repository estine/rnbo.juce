#pragma once

#include <JuceHeader.h>

class FacetedCrystalLookAndFeel : public juce::LookAndFeel_V4,
    private juce::Timer
{
public:
    FacetedCrystalLookAndFeel()
    {
        startTimerHz(30); // 30 fps shimmer update
    }

    void registerSlider(juce::Slider* sliderToRegister)
    {
        if (sliderToRegister != nullptr)
            slidersToRepaint.addIfNotAlreadyThere(sliderToRegister);
    }

    void drawLinearSliderThumb(juce::Graphics& g, int x, int y, int width, int height,
        float sliderPos, float /*minSliderPos*/, float /*maxSliderPos*/,
        const juce::Slider::SliderStyle /*style*/, juce::Slider& /*slider*/) override
    {
        const float thumbSize = 16.0f;
        const float centerY = y + height / 2.0f;
        const float thumbX = sliderPos - thumbSize / 2.0f;
        const float thumbY = centerY - thumbSize / 2.0f;

        juce::Path crystal;
        crystal.addTriangle(thumbX, centerY,
            thumbX + thumbSize / 2.0f, thumbY,
            thumbX + thumbSize, centerY);
        crystal.addTriangle(thumbX, centerY,
            thumbX + thumbSize / 2.0f, thumbY + thumbSize,
            thumbX + thumbSize, centerY);

        juce::ColourGradient grad(
            juce::Colour::fromHSV(shimmerBaseHue, 0.6f, 1.0f, 1.0f), thumbX, thumbY,
            juce::Colours::white.withAlpha(0.3f), thumbX + thumbSize, thumbY + thumbSize, false);
        grad.addColour(0.5, juce::Colours::aqua.withAlpha(0.4f));

        g.setGradientFill(grad);
        g.fillPath(crystal);

        g.setColour(juce::Colours::white.withAlpha(0.7f));
        g.strokePath(crystal, juce::PathStrokeType(1.0f));
    }

    void drawLinearSliderBackground(juce::Graphics& g, int x, int y, int width, int height,
        float /*sliderPos*/, float /*minSliderPos*/, float /*maxSliderPos*/,
        const juce::Slider::SliderStyle, juce::Slider&) override
    {
        const float trackHeight = 4.0f;
        const float centerY = y + height / 2.0f - trackHeight / 2.0f;

        juce::Rectangle<float> track(x, centerY, width, trackHeight);
        g.setColour(juce::Colours::darkblue.withAlpha(0.4f));
        g.fillRoundedRectangle(track, 2.0f);
    }

private:
    juce::Array<juce::Slider*> slidersToRepaint;
    float shimmerBaseHue = 0.5f;

    void timerCallback() override
    {
        shimmerBaseHue += 0.002f;
        if (shimmerBaseHue > 1.0f)
            shimmerBaseHue = 0.0f;

        for (auto* slider : slidersToRepaint)
        {
            if (slider != nullptr)
                slider->repaint();
        }
    }
};
