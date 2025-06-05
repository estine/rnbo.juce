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
    EsmwADSRDisplay _adsrDisplay;
    
    CrystalPitchVisualizer pitchViz;

    // Title

    juce::Label _titleLabel;
    juce::Label _creatorLabel;

    // GUI Elements

    // ADSR

    juce::Label _adsrLabel;

    juce::Slider _attackSlider;
    juce::Label _attackLabel;

    juce::Slider _decaySlider;
    juce::Label _decayLabel;

    juce::Slider _sustainSlider;
    juce::Label _sustainLabel;

    juce::Slider _releaseSlider;
    juce::Label _releaseLabel;

    // Partial Modes
    EsmwButtonGroup _partialButtonGroup{ { "semi", "ratio", "freq" } };
    RNBO::ParameterIndex _partialModeIndex = RNBO::INVALID_INDEX;
    juce::Label _partialModeLabel;

    // second partial

    juce::Label _secondPartialLabel;

    // todo: labels for these, too
    juce::Slider _secondPartialSemitone;
    juce::Label _secondPartialSemitoneLabel;

    juce::Slider _secondPartialRatio;
    juce::Label _secondPartialRatioLabel;

    juce::Slider _secondPartialFreq;
    juce::Label _secondPartialFreqLabel;

    juce::Slider _secondPartialAmp;
    juce::Label _secondPartialAmpLabel;

    juce::Slider _secondPartialDecay;
    juce::Label _secondPartialDecayLabel;

    // third partial

    juce::Label _thirdPartialLabel;

    // todo: labels for these, too
    juce::Slider _thirdPartialSemitone;
    juce::Label _thirdPartialSemitoneLabel;

    juce::Slider _thirdPartialRatio;
    juce::Label _thirdPartialRatioLabel;

    juce::Slider _thirdPartialFreq;
    juce::Label _thirdPartialFreqLabel;

    juce::Slider _thirdPartialAmp;
    juce::Label _thirdPartialAmpLabel;

    juce::Slider _thirdPartialDecay;
    juce::Label _thirdPartialDecayLabel;

    // Timer Stuff

    int _pulseCounter = 0;

protected:
    AudioProcessor                              *_audioProcessor;
    RNBO::CoreObject&                           _rnboObject; 
    Label                                       _label;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CustomAudioEditor)
};
