#include "JuceHeader.h"
#include "RNBO.h"
#include "RNBO_JuceAudioProcessor.h"
#include "EsmwLookAndFeel.h"
#include "EsmwADSRDisplay.h"
#include "EsmwButtonGroup.h"
#include "CrystalPitchVisualizer.h"

class CustomAudioEditor : public AudioProcessorEditor, private AudioProcessorListener, public juce::Timer
{
public:
    CustomAudioEditor(RNBO::JuceAudioProcessor* const p, RNBO::CoreObject& rnboObject);
    ~CustomAudioEditor() override;
    void paint (Graphics& g) override;
    void resized() override;
    void timerCallback() override;

private:
    void audioProcessorChanged (AudioProcessor*, const ChangeDetails&) override { }
    void audioProcessorParameterChanged(AudioProcessor*, int parameterIndex, float) override;

    // Look and Feel
    EsmwLookAndFeel customLookAndFeel;
    EsmwADSRDisplay adsrDisplay;
    EsmwButtonGroup buttonGroup;
    CrystalPitchVisualizer pitchViz;

    // Title

    juce::Label _titleLabel;
    juce::Label _creatorLabel;

    // GUI Elements
    juce::Slider _attackSlider;
    juce::Label _attackLabel;

    juce::Slider _decaySlider;
    juce::Label _decayLabel;

    juce::Slider _sustainSlider;
    juce::Label _sustainLabel;

    juce::Slider _releaseSlider;
    juce::Label _releaseLabel;

    RNBO::ParameterIndex _partialModeIndex = RNBO::INVALID_INDEX;
    juce::ComboBox _partialModeComboBox;
    juce::Label _partialModeLabel;

    // Timer Stuff

    int _pulseCounter = 0;

protected:
    AudioProcessor                              *_audioProcessor;
    RNBO::CoreObject&                           _rnboObject; 
    Label                                       _label;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CustomAudioEditor)
};
