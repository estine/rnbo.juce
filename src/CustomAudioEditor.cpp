#include "CustomAudioEditor.h"

// This is the constructor
CustomAudioEditor::CustomAudioEditor (RNBO::JuceAudioProcessor* const p, RNBO::CoreObject& rnboObject)
    : AudioProcessorEditor (p)
    , _rnboObject(rnboObject)
    , _audioProcessor(p)
{
    _audioProcessor->AudioProcessor::addListener(this);
    setSize (400, 450); // Make resizeable in the future

    // --- GUI Elements ---

    // --- Title Label ---
    _titleLabel.setText("crystallophon", juce::dontSendNotification);
    _titleLabel.setJustificationType(juce::Justification::topLeft);
    _titleLabel.setFont(juce::Font(30.0f, juce::Font::italic));
    _titleLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    addAndMakeVisible(_titleLabel);

    // --- Creator Label ---
    _creatorLabel.setText("esmw", juce::dontSendNotification);
    _creatorLabel.setJustificationType(juce::Justification::topLeft);
    _creatorLabel.setFont(juce::Font(12.0f));
    _creatorLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    addAndMakeVisible(_creatorLabel);

    // --- ADSR Display ---

    _adsrLabel.setText("input shape", juce::NotificationType::dontSendNotification);
    _adsrLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    _adsrLabel.setFont(juce::Font(26.0f));
    addAndMakeVisible(_adsrLabel);

    addAndMakeVisible(_adsrDisplay);

    // --- Attack ---
    _attackSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    _attackSlider.setRotaryParameters(juce::MathConstants<float>::pi * 0.75f,
        juce::MathConstants<float>::pi * 2.25f, 
        true); 
    _attackSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
    _attackSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    _attackSlider.setRange(0.10, 2000.0, 0.01);
    _attackSlider.setValue(0.10);
    _attackSlider.onValueChange = [this]() {
        if (auto index = _rnboObject.getParameterIndexForID("attack"); index >= 0) {
            _rnboObject.setParameterValue(index, (float)_attackSlider.getValue());
        }
        };
    addAndMakeVisible(_attackSlider);

    _attackLabel.setText("a", juce::NotificationType::dontSendNotification);
    _attackLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    _attackLabel.attachToComponent(&_attackSlider, false);
    addAndMakeVisible(_attackLabel);

    // --- Decay ---
    _decaySlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    _decaySlider.setRotaryParameters(juce::MathConstants<float>::pi * 0.75f,
        juce::MathConstants<float>::pi * 2.25f,
        true);
    _decaySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    _decaySlider.setRange(0.10, 2000.0, 0.01);
    _decaySlider.setValue(0.10);
    _decaySlider.onValueChange = [this]() {
        if (auto index = _rnboObject.getParameterIndexForID("decay"); index >= 0) {
            _rnboObject.setParameterValue(index, (float)_decaySlider.getValue());
        }
        };
    _decaySlider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    addAndMakeVisible(_decaySlider);

    _decayLabel.setText("d", juce::dontSendNotification);
    _decayLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    _decayLabel.attachToComponent(&_decaySlider, false);
    addAndMakeVisible(_decayLabel);

    // --- Sustain ---
    _sustainSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    _sustainSlider.setRotaryParameters(juce::MathConstants<float>::pi * 0.75f,
        juce::MathConstants<float>::pi * 2.25f,
        true);
    _sustainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    _sustainSlider.setRange(0.0, 1.0, 0.01);
    _sustainSlider.setValue(0.0);
    _sustainSlider.onValueChange = [this]() {
        if (auto index = _rnboObject.getParameterIndexForID("sustain"); index >= 0) {
            _rnboObject.setParameterValue(index, (float)_sustainSlider.getValue());
        }
        };
    _sustainSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    addAndMakeVisible(_sustainSlider);

    _sustainLabel.setText("s", juce::dontSendNotification);
    _sustainLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    _sustainLabel.attachToComponent(&_sustainSlider, false);
    addAndMakeVisible(_sustainLabel);

    // --- Release ---
    _releaseSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    _releaseSlider.setRotaryParameters(juce::MathConstants<float>::pi * 0.75f,
        juce::MathConstants<float>::pi * 2.25f,
        true);
    _releaseSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    _releaseSlider.setRange(0.10, 2000.0, 0.01);
    _releaseSlider.setValue(0.10);
    _releaseSlider.onValueChange = [this]() {
        if (auto index = _rnboObject.getParameterIndexForID("release"); index >= 0) {
            _rnboObject.setParameterValue(index, (float)_releaseSlider.getValue());
        }
        };
    _releaseSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    addAndMakeVisible(_releaseSlider);

    _releaseLabel.setText("r", juce::dontSendNotification);
    _releaseLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    _releaseLabel.attachToComponent(&_releaseSlider, false);
    addAndMakeVisible(_releaseLabel);

    // --- Partial Mode Label ---
    _partialModeLabel.setText("partial mode", juce::dontSendNotification);
    _partialModeLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    _partialModeLabel.setFont(juce::Font(26.0f));
    addAndMakeVisible(_partialModeLabel);

    // --- Partial Mode Selector ---

    addAndMakeVisible(_partialButtonGroup);

    _partialModeIndex = _rnboObject.getParameterIndexForID("partialMode");

    // This changes the combobox contents based on an enum ???
    _partialButtonGroup.onChange = [this]() {
        int selected = _partialButtonGroup.getSelectedIndex(); // should be 0, 1, or 2
        if (_partialModeIndex != RNBO::INVALID_INDEX) {
            _rnboObject.setParameterValue(_partialModeIndex, static_cast<float>(selected));
        }
        };

    // make visible different knobs based on mode
    _partialButtonGroup.onSelectionChanged = [this](int selectedIndex)
        {
            _secondPartialSemitone.setVisible(selectedIndex == 0);
            _thirdPartialSemitone.setVisible(selectedIndex == 0);
            _secondPartialRatio.setVisible(selectedIndex == 1);
            _thirdPartialRatio.setVisible(selectedIndex == 1);
            _secondPartialFreq.setVisible(selectedIndex == 2);
            _thirdPartialFreq.setVisible(selectedIndex == 2);

        };

    // --- Second Partial Label ---
    _secondPartialLabel.setText("second partial", juce::dontSendNotification);
    _secondPartialLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    _secondPartialLabel.setFont(juce::Font(26.0f));
    addAndMakeVisible(_secondPartialLabel);

    // --- Second Partial Semitone ---
    _secondPartialSemitone.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    _secondPartialSemitone.setRotaryParameters(juce::MathConstants<float>::pi * 0.75f,
        juce::MathConstants<float>::pi * 2.25f,
        true);
    _secondPartialSemitone.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    _secondPartialSemitone.setRange(0, 36, 1);
    _secondPartialSemitone.setValue(12);
    _secondPartialSemitone.onValueChange = [this]() {
        if (auto index = _rnboObject.getParameterIndexForID("secondPartialSemitoneOffset"); index >= 0) {
            _rnboObject.setParameterValue(index, (float)_secondPartialSemitone.getValue());
        }
        };
    _secondPartialSemitone.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    addAndMakeVisible(_secondPartialSemitone);

    _secondPartialSemitoneLabel.setText("semi", juce::dontSendNotification);
    _secondPartialSemitoneLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    _secondPartialSemitoneLabel.attachToComponent(&_secondPartialSemitone, false);
    addAndMakeVisible(_secondPartialSemitoneLabel);

    // --- Second Partial Ratio ---

    _secondPartialRatio.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    _secondPartialRatio.setRotaryParameters(juce::MathConstants<float>::pi * 0.75f,
        juce::MathConstants<float>::pi * 2.25f,
        true);
    _secondPartialRatio.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    _secondPartialRatio.setRange(1, 7, 0.01);
    _secondPartialRatio.setValue(1.3);
    _secondPartialRatio.onValueChange = [this]() {
        if (auto index = _rnboObject.getParameterIndexForID("secondPartialRatio"); index >= 0) {
            _rnboObject.setParameterValue(index, (float)_secondPartialRatio.getValue());
        }
        };
    _secondPartialRatio.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    addAndMakeVisible(_secondPartialRatio);

    _secondPartialRatioLabel.setText("ratio", juce::dontSendNotification);
    _secondPartialRatioLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    _secondPartialRatioLabel.attachToComponent(&_secondPartialRatio, false);
    addAndMakeVisible(_secondPartialRatioLabel);

    // --- Second Partial Freq ---

    _secondPartialFreq.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    _secondPartialFreq.setRotaryParameters(juce::MathConstants<float>::pi * 0.75f,
        juce::MathConstants<float>::pi * 2.25f,
        true);
    _secondPartialFreq.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    _secondPartialFreq.setRange(1, 10000, 1);
    _secondPartialFreq.setValue(1500);
    _secondPartialFreq.onValueChange = [this]() {
        if (auto index = _rnboObject.getParameterIndexForID("secondPartialFrequencyOffset"); index >= 0) {
            _rnboObject.setParameterValue(index, (float)_secondPartialFreq.getValue());
        }
        };
    _secondPartialFreq.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    addAndMakeVisible(_secondPartialFreq);

    _secondPartialFreqLabel.setText("freq", juce::dontSendNotification);
    _secondPartialFreqLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    _secondPartialFreqLabel.attachToComponent(&_secondPartialFreq, false);
    addAndMakeVisible(_secondPartialFreqLabel);

    // Initially only show one of them
    _secondPartialSemitone.setVisible(true);
    _secondPartialRatio.setVisible(false);
    _secondPartialFreq.setVisible(false);

    // --- Second Partial Decay ---

    _secondPartialDecay.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    _secondPartialDecay.setRotaryParameters(juce::MathConstants<float>::pi * 0.75f,
        juce::MathConstants<float>::pi * 2.25f,
        true);
    _secondPartialDecay.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    _secondPartialDecay.setRange(0.01, 1, 0.01);
    _secondPartialDecay.setValue(0.15);
    _secondPartialDecay.onValueChange = [this]() {
        if (auto index = _rnboObject.getParameterIndexForID("secondPartialDecayMultiplier"); index >= 0) {
            _rnboObject.setParameterValue(index, (float)_secondPartialDecay.getValue());
        }
        };
    _secondPartialDecay.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    addAndMakeVisible(_secondPartialDecay);

    _secondPartialDecayLabel.setText("decay", juce::dontSendNotification);
    _secondPartialDecayLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    _secondPartialDecayLabel.attachToComponent(&_secondPartialDecay, false);
    addAndMakeVisible(_secondPartialDecayLabel);

    // --- Second Partial Amp ---

    _secondPartialAmp.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    _secondPartialAmp.setRotaryParameters(juce::MathConstants<float>::pi * 0.75f,
        juce::MathConstants<float>::pi * 2.25f,
        true);
    _secondPartialAmp.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    _secondPartialAmp.setRange(0.0, 1, 0.01);
    _secondPartialAmp.setValue(0.9);
    _secondPartialAmp.onValueChange = [this]() {
        if (auto index = _rnboObject.getParameterIndexForID("secondPartialAmpMultiplier"); index >= 0) {
            _rnboObject.setParameterValue(index, (float)_secondPartialAmp.getValue());
        }
        };
    _secondPartialAmp.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    addAndMakeVisible(_secondPartialAmp);

    _secondPartialAmpLabel.setText("amp", juce::dontSendNotification);
    _secondPartialAmpLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    _secondPartialAmpLabel.attachToComponent(&_secondPartialAmp, false);
    addAndMakeVisible(_secondPartialAmpLabel);

    // Third Partial Controls

    // --- third Partial Label ---
    _thirdPartialLabel.setText("third partial", juce::dontSendNotification);
    _thirdPartialLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    _thirdPartialLabel.setFont(juce::Font(26.0f));
    addAndMakeVisible(_thirdPartialLabel);

    // --- third Partial Semitone ---
    _thirdPartialSemitone.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    _thirdPartialSemitone.setRotaryParameters(juce::MathConstants<float>::pi * 0.75f,
        juce::MathConstants<float>::pi * 2.25f,
        true);
    _thirdPartialSemitone.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    _thirdPartialSemitone.setRange(0, 36, 1);
    _thirdPartialSemitone.setValue(24);
    _thirdPartialSemitone.onValueChange = [this]() {
        if (auto index = _rnboObject.getParameterIndexForID("thirdPartialSemitoneOffset"); index >= 0) {
            _rnboObject.setParameterValue(index, (float)_thirdPartialSemitone.getValue());
        }
        };
    _thirdPartialSemitone.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    addAndMakeVisible(_thirdPartialSemitone);

    _thirdPartialSemitoneLabel.setText("semi", juce::dontSendNotification);
    _thirdPartialSemitoneLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    _thirdPartialSemitoneLabel.attachToComponent(&_thirdPartialSemitone, false);
    addAndMakeVisible(_thirdPartialSemitoneLabel);

    // --- third Partial Ratio ---

    _thirdPartialRatio.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    _thirdPartialRatio.setRotaryParameters(juce::MathConstants<float>::pi * 0.75f,
        juce::MathConstants<float>::pi * 2.25f,
        true);
    _thirdPartialRatio.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    _thirdPartialRatio.setRange(1, 7, 0.01);
    _thirdPartialRatio.setValue(1.3);
    _thirdPartialRatio.onValueChange = [this]() {
        if (auto index = _rnboObject.getParameterIndexForID("thirdPartialRatio"); index >= 0) {
            _rnboObject.setParameterValue(index, (float)_thirdPartialRatio.getValue());
        }
        };
    _thirdPartialRatio.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    addAndMakeVisible(_thirdPartialRatio);

    _thirdPartialRatioLabel.setText("ratio", juce::dontSendNotification);
    _thirdPartialRatioLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    _thirdPartialRatioLabel.attachToComponent(&_thirdPartialRatio, false);
    addAndMakeVisible(_thirdPartialRatioLabel);

    // --- third Partial Freq ---

    _thirdPartialFreq.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    _thirdPartialFreq.setRotaryParameters(juce::MathConstants<float>::pi * 0.75f,
        juce::MathConstants<float>::pi * 2.25f,
        true);
    _thirdPartialFreq.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    _thirdPartialFreq.setRange(1, 10000, 1);
    _thirdPartialFreq.setValue(1500);
    _thirdPartialFreq.onValueChange = [this]() {
        if (auto index = _rnboObject.getParameterIndexForID("thirdPartialFrequencyOffset"); index >= 0) {
            _rnboObject.setParameterValue(index, (float)_thirdPartialFreq.getValue());
        }
        };
    _thirdPartialFreq.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    addAndMakeVisible(_thirdPartialFreq);

    _thirdPartialFreqLabel.setText("freq", juce::dontSendNotification);
    _thirdPartialFreqLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    _thirdPartialFreqLabel.attachToComponent(&_thirdPartialFreq, false);
    addAndMakeVisible(_thirdPartialFreqLabel);

    // Initially only show one of them
    _thirdPartialSemitone.setVisible(true);
    _thirdPartialRatio.setVisible(false);
    _thirdPartialFreq.setVisible(false);

    // --- third Partial Decay ---

    _thirdPartialDecay.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    _thirdPartialDecay.setRotaryParameters(juce::MathConstants<float>::pi * 0.75f,
        juce::MathConstants<float>::pi * 2.25f,
        true);
    _thirdPartialDecay.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    _thirdPartialDecay.setRange(0.01, 1, 0.01);
    _thirdPartialDecay.setValue(0.3);
    _thirdPartialDecay.onValueChange = [this]() {
        if (auto index = _rnboObject.getParameterIndexForID("thirdPartialDecayMultiplier"); index >= 0) {
            _rnboObject.setParameterValue(index, (float)_thirdPartialDecay.getValue());
        }
        };
    _thirdPartialDecay.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    addAndMakeVisible(_thirdPartialDecay);

    _thirdPartialDecayLabel.setText("decay", juce::dontSendNotification);
    _thirdPartialDecayLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    _thirdPartialDecayLabel.attachToComponent(&_thirdPartialDecay, false);
    addAndMakeVisible(_thirdPartialDecayLabel);

    // --- third Partial Amp ---

    _thirdPartialAmp.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    _thirdPartialAmp.setRotaryParameters(juce::MathConstants<float>::pi * 0.75f,
        juce::MathConstants<float>::pi * 2.25f,
        true);
    _thirdPartialAmp.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    _thirdPartialAmp.setRange(0.0, 1, 0.01);
    _thirdPartialAmp.setValue(0.8);
    _thirdPartialAmp.onValueChange = [this]() {
        if (auto index = _rnboObject.getParameterIndexForID("thirdPartialAmpMultiplier"); index >= 0) {
            _rnboObject.setParameterValue(index, (float)_thirdPartialAmp.getValue());
        }
        };
    _thirdPartialAmp.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    addAndMakeVisible(_thirdPartialAmp);

    _thirdPartialAmpLabel.setText("amp", juce::dontSendNotification);
    _thirdPartialAmpLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    _thirdPartialAmpLabel.attachToComponent(&_thirdPartialAmp, false);
    addAndMakeVisible(_thirdPartialAmpLabel);


    // --- Crystal Pitch Visualizer

    // TODO: make this take in MIDI
    // addAndMakeVisible(pitchViz); 

    // Update values dynamically:
    pitchViz.setPitchAndIntensity(0, 0.3f, 0.8f); // left
    pitchViz.setPitchAndIntensity(1, 0.5f, 1.0f); // center
    pitchViz.setPitchAndIntensity(2, 0.7f, 0.6f); // right

    // Look And Feel
    _attackSlider.setLookAndFeel(&customLookAndFeel);
    _decaySlider.setLookAndFeel(&customLookAndFeel);
    _sustainSlider.setLookAndFeel(&customLookAndFeel);
    _releaseSlider.setLookAndFeel(&customLookAndFeel);

    _secondPartialSemitone.setLookAndFeel(&customLookAndFeel);
    _secondPartialRatio.setLookAndFeel(&customLookAndFeel);
    _secondPartialFreq.setLookAndFeel(&customLookAndFeel);
    _secondPartialDecay.setLookAndFeel(&customLookAndFeel);
    _secondPartialAmp.setLookAndFeel(&customLookAndFeel);

    _thirdPartialSemitone.setLookAndFeel(&customLookAndFeel);
    _thirdPartialRatio.setLookAndFeel(&customLookAndFeel);
    _thirdPartialFreq.setLookAndFeel(&customLookAndFeel);
    _thirdPartialDecay.setLookAndFeel(&customLookAndFeel);
    _thirdPartialAmp.setLookAndFeel(&customLookAndFeel);

    // Graphics Timer
    startTimerHz(30); // 30 fps

}

void CustomAudioEditor::resized()
{

    int knobWidth = 45;
    float knobWidthMod = 1.0f;

    // todo: redo this as resizeable

    _titleLabel.setBounds(20, 10, getWidth(), 30);
    _creatorLabel.setBounds(20, 40, getWidth(), 30);

    _adsrLabel.setBounds(20, 55, getWidth(), 30);

    _adsrDisplay.setBounds(25, 85, 180, 70);

    _attackSlider.setBounds(20, 180, knobWidth * knobWidthMod, knobWidth);
    _decaySlider.setBounds(70, 180, knobWidth * knobWidthMod, knobWidth);
    _sustainSlider.setBounds(120, 180, knobWidth * knobWidthMod, knobWidth);
    _releaseSlider.setBounds(170, 180, knobWidth * knobWidthMod, knobWidth);

    _partialModeLabel.setBounds(20, 240, getWidth(), 30);
    _partialButtonGroup.setBounds(20, 280, 160, 30);

    // second partial

    _secondPartialLabel.setBounds(20, 330, getWidth(), 30);

    _secondPartialSemitone.setBounds(20, 380, knobWidth*knobWidthMod, knobWidth);
    _secondPartialRatio.setBounds(20, 380, knobWidth*knobWidthMod, knobWidth);
    _secondPartialFreq.setBounds(20, 380, knobWidth*knobWidthMod, knobWidth);

    _secondPartialDecay.setBounds(70, 380, knobWidth * knobWidthMod, knobWidth);
    _secondPartialAmp.setBounds(120, 380, knobWidth * knobWidthMod, knobWidth);

    // third partial

    _thirdPartialLabel.setBounds(200, 330, getWidth(), 30);

    _thirdPartialSemitone.setBounds(200, 380, knobWidth * knobWidthMod, knobWidth);
    _thirdPartialRatio.setBounds(200, 380, knobWidth * knobWidthMod, knobWidth);
    _thirdPartialFreq.setBounds(200, 380, knobWidth * knobWidthMod, knobWidth);

    _thirdPartialDecay.setBounds(250, 380, knobWidth * knobWidthMod, knobWidth);
    _thirdPartialAmp.setBounds(300, 380, knobWidth * knobWidthMod, knobWidth);

    // later
    pitchViz.setBounds(190, 30, 200, 270);

}

// This is the destructor
CustomAudioEditor::~CustomAudioEditor()
{
    _audioProcessor->AudioProcessor::removeListener(this);

    _attackSlider.setLookAndFeel(nullptr);
    _decaySlider.setLookAndFeel(nullptr);
    _sustainSlider.setLookAndFeel(nullptr);
    _releaseSlider.setLookAndFeel(nullptr);

    _secondPartialSemitone.setLookAndFeel(nullptr);
    _secondPartialRatio.setLookAndFeel(nullptr);
    _secondPartialFreq.setLookAndFeel(nullptr);
    _secondPartialDecay.setLookAndFeel(nullptr);
    _secondPartialAmp.setLookAndFeel(nullptr);

    _thirdPartialSemitone.setLookAndFeel(nullptr);
    _thirdPartialRatio.setLookAndFeel(nullptr);
    _thirdPartialFreq.setLookAndFeel(nullptr);
    _thirdPartialDecay.setLookAndFeel(nullptr);
    _thirdPartialAmp.setLookAndFeel(nullptr);


}

void CustomAudioEditor::paint (Graphics& g)
{
    g.fillAll(juce::Colours::white); // White background
}

void CustomAudioEditor::audioProcessorParameterChanged(juce::AudioProcessor*, int parameterIndex, float newValue)
{
    juce::String paramId = _rnboObject.getParameterId(parameterIndex);

    juce::MessageManager::callAsync([this, paramId, newValue]() {
        if (paramId == "attack") {
            _attackSlider.setValue(newValue, juce::dontSendNotification);
        }
        else if (paramId == "decay") {
            _decaySlider.setValue(newValue, juce::dontSendNotification);
        }
        else if (paramId == "sustain") {
            _sustainSlider.setValue(newValue, juce::dontSendNotification);
        }
        else if (paramId == "release") {
            _releaseSlider.setValue(newValue, juce::dontSendNotification);
        } else if (paramId == "partialMode")
    {
        int id = static_cast<int>(newValue); // combo IDs start at 1
        //_partialModeComboBox.setSelectedId(id, juce::dontSendNotification);
        // This is needed
    }
        });
}

void CustomAudioEditor::timerCallback()
{
    _pulseCounter++;

    // Pulsing alpha using sine wave
    float pulse = 0.2f + 0.8f * std::abs(std::sin(_pulseCounter * 0.05f));
    juce::Colour pulsingColour = juce::Colours::black.withAlpha(pulse);

    _titleLabel.setColour(juce::Label::textColourId, pulsingColour);

    // ADSR Visualization - do this somewhere else in the future
    _adsrDisplay.setEnvelope((float)juce::jmap((float)_attackSlider.getValue(), 0.1f, 2000.0f, 0.0f, 1.0f),
        (float)juce::jmap((float)_decaySlider.getValue(), 0.1f, 2000.0f, 0.0f, 1.0f),
        (float)_sustainSlider.getValue(),
        (float)juce::jmap((float)_releaseSlider.getValue(), 0.1f, 2000.0f, 0.0f, 1.0f));

    // Crystal Visualization
    /*int note = processor.lastMidiNote.load();
    int velocity = processor.lastVelocity.load();

    if (note >= 0) {
        pitchViz.setNote(0, note, velocity);
    }*/
}
