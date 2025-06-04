#pragma once
#include <JuceHeader.h>

class CrystalPitchVisualizer : public juce::Component
{
public:
    CrystalPitchVisualizer()
    {
        setOpaque(false);
    }

    // Pitches and intensities expected to be normalized (0..1)
    void setPitches(float low, float mid, float high,
        float lowIntensity, float midIntensity, float highIntensity)
    {
        pitches[0] = juce::jlimit(0.f, 1.f, low);
        pitches[1] = juce::jlimit(0.f, 1.f, mid);
        pitches[2] = juce::jlimit(0.f, 1.f, high);

        intensities[0] = juce::jlimit(0.f, 1.f, lowIntensity);
        intensities[1] = juce::jlimit(0.f, 1.f, midIntensity);
        intensities[2] = juce::jlimit(0.f, 1.f, highIntensity);

        repaint();
    }

    void paint(juce::Graphics& g) override
    {
        auto w = (float)getWidth();
        auto h = (float)getHeight();
        auto centerX = w * 0.5f;
        auto baseY = h * 0.9f;
        auto topY = h * 0.1f;
        auto midY = (topY + baseY) * 0.5f;
        auto sideWidth = w * 0.2f;

        // Define points for crystal shape
        juce::Point<float> top(centerX, topY);
        juce::Point<float> left(centerX - sideWidth, midY);
        juce::Point<float> right(centerX + sideWidth, midY);
        juce::Point<float> bottomLeft(centerX - sideWidth * 0.7f, baseY);
        juce::Point<float> bottomRight(centerX + sideWidth * 0.7f, baseY);
        juce::Point<float> bottom(centerX, baseY);

        // Draw crystal shape outline and fill
        juce::Path crystal;
        crystal.startNewSubPath(top);
        crystal.lineTo(left);
        crystal.lineTo(bottomLeft);
        crystal.lineTo(bottom);
        crystal.lineTo(bottomRight);
        crystal.lineTo(right);
        crystal.closeSubPath();

        g.setColour(juce::Colours::white.withAlpha(0.05f));
        g.fillPath(crystal);

        g.setColour(juce::Colours::black);
        g.strokePath(crystal, juce::PathStrokeType(1.0f));

        // Draw glowing "markers" on edges:
        // Edges to highlight:
        //   left edge: from top to left
        //   bottom edge: from bottomLeft to bottomRight
        //   right edge: from top to right

        drawGlowingMarkerOnEdge(g, top, left, pitches[0], intensities[0]);         // low pitch on left edge
        drawGlowingMarkerOnEdge(g, bottomLeft, bottomRight, pitches[1], intensities[1]); // mid pitch on bottom edge
        drawGlowingMarkerOnEdge(g, top, right, pitches[2], intensities[2]);       // high pitch on right edge
    }

private:
    float pitches[3] = { 0.f, 0.f, 0.f };
    float intensities[3] = { 0.f, 0.f, 0.f };

    void drawGlowingMarkerOnEdge(juce::Graphics& g,
        juce::Point<float> start,
        juce::Point<float> end,
        float positionNorm, // 0..1 along edge
        float intensity)    // 0..1 glow strength
    {
        if (intensity <= 0.01f)
            return;

        positionNorm = juce::jlimit(0.f, 1.f, positionNorm);

        juce::Point<float> pointOnEdge = start + (end - start) * positionNorm;

        juce::Point<float> edgeVec = end - start;
        juce::Point<float> perpVec(-edgeVec.y, edgeVec.x);
        perpVec = perpVec / perpVec.getDistanceFromOrigin();

        float markerLength = 10.0f + 15.0f * intensity;

        juce::Point<float> markerStart = pointOnEdge - perpVec * markerLength * 0.5f;
        juce::Point<float> markerEnd = pointOnEdge + perpVec * markerLength * 0.5f;

        // Draw glow
        juce::Path glowPath;
        glowPath.startNewSubPath(markerStart);
        glowPath.lineTo(markerEnd);

        g.setColour(juce::Colours::white.withAlpha(0.15f * intensity));
        g.strokePath(glowPath, juce::PathStrokeType(6.0f * intensity));

        // Draw inner bright line
        g.setColour(juce::Colours::white.withAlpha(0.9f * intensity));
        g.strokePath(glowPath, juce::PathStrokeType(2.0f));
    }
};
