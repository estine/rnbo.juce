#include "CustomAudioEditor.h"

// This is the constructor
CustomAudioEditor::CustomAudioEditor (RNBO::JuceAudioProcessor* const p, RNBO::CoreObject& rnboObject)
    : AudioProcessorEditor (p)
    , _rnboObject(rnboObject)
    , _audioProcessor(p)
{
    _audioProcessor->AudioProcessor::addListener(this);
    setSize (400, 300); // Make resizeable in the future

    // --- Title Label ---
    _titleLabel.setText("Crystallophon v.0.1", juce::dontSendNotification);
    _titleLabel.setJustificationType(juce::Justification::centredTop);
    _titleLabel.setFont(juce::Font(20.0f, juce::Font::bold));
    _titleLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    addAndMakeVisible(_titleLabel);

    // --- Creator Label ---
    _creatorLabel.setText("esmw 2025", juce::dontSendNotification);
    _creatorLabel.setJustificationType(juce::Justification::centredTop);
    _creatorLabel.setFont(juce::Font(14.0f, juce::Font::bold));
    _creatorLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    addAndMakeVisible(_creatorLabel);

    // --- GUI Elements ---

    // --- Attack ---
    _attackSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    _attackSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 80, 20);
    _attackSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    _attackSlider.setRange(0.10, 2000.0, 0.01);
    _attackSlider.setValue(0.10);
    _attackSlider.onValueChange = [this]() {
        if (auto index = _rnboObject.getParameterIndexForID("attack"); index >= 0) {
            _rnboObject.setParameterValue(index, (float)_attackSlider.getValue());
        }
        };
    addAndMakeVisible(_attackSlider);

    _attackLabel.setText("Attack (ms)", juce::NotificationType::dontSendNotification);
    _attackLabel.attachToComponent(&_attackSlider, true);
    addAndMakeVisible(_attackLabel);
    _attackLabel.setColour(juce::Label::textColourId, juce::Colours::black);

    // --- Decay ---
    _decaySlider.setSliderStyle(juce::Slider::LinearHorizontal);
    _decaySlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 80, 20);
    _decaySlider.setRange(0.10, 2000.0, 0.01);
    _decaySlider.setValue(0.10);
    _decaySlider.onValueChange = [this]() {
        if (auto index = _rnboObject.getParameterIndexForID("decay"); index >= 0) {
            _rnboObject.setParameterValue(index, (float)_decaySlider.getValue());
        }
        };
    _decaySlider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    _decaySlider.setColour(juce::Slider::textBoxBackgroundColourId, juce::Colours::white);
    _decaySlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::grey);
    addAndMakeVisible(_decaySlider);

    _decayLabel.setText("Decay (ms)", juce::dontSendNotification);
    _decayLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    _decayLabel.attachToComponent(&_decaySlider, true);
    addAndMakeVisible(_decayLabel);

    // --- Sustain ---
    _sustainSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    _sustainSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 80, 20);
    _sustainSlider.setRange(0.0, 1.0, 0.01);
    _sustainSlider.setValue(0.0);
    _sustainSlider.onValueChange = [this]() {
        if (auto index = _rnboObject.getParameterIndexForID("sustain"); index >= 0) {
            _rnboObject.setParameterValue(index, (float)_sustainSlider.getValue());
        }
        };
    _sustainSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    _sustainSlider.setColour(juce::Slider::textBoxBackgroundColourId, juce::Colours::white);
    _sustainSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::grey);
    addAndMakeVisible(_sustainSlider);

    _sustainLabel.setText("Sustain (gain)", juce::dontSendNotification);
    _sustainLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    _sustainLabel.attachToComponent(&_sustainSlider, true);
    addAndMakeVisible(_sustainLabel);

    // --- Release ---
    _releaseSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    _releaseSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 80, 20);
    _releaseSlider.setRange(0.10, 2000.0, 0.01);
    _releaseSlider.setValue(0.10);
    _releaseSlider.onValueChange = [this]() {
        if (auto index = _rnboObject.getParameterIndexForID("release"); index >= 0) {
            _rnboObject.setParameterValue(index, (float)_releaseSlider.getValue());
        }
        };
    _releaseSlider.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
    _releaseSlider.setColour(juce::Slider::textBoxBackgroundColourId, juce::Colours::white);
    _releaseSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::grey);
    addAndMakeVisible(_releaseSlider);

    _releaseLabel.setText("Release (ms)", juce::dontSendNotification);
    _releaseLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    _releaseLabel.attachToComponent(&_releaseSlider, true);
    addAndMakeVisible(_releaseLabel);

    // --- Partial Mode Label ---
    _partialModeLabel.setText("Partial Mode", juce::dontSendNotification);
    _partialModeLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    addAndMakeVisible(_partialModeLabel);

    _partialModeIndex = _rnboObject.getParameterIndexForID("partialMode");

    // --- Partial Mode ComboBox ---
    _partialModeComboBox.addItem("SemiToneMode", 1);
    _partialModeComboBox.addItem("RatioMode", 2);
    _partialModeComboBox.addItem("FreqOffsetMode", 3);
    _partialModeComboBox.setSelectedId(1); // Default
    _partialModeComboBox.onChange = [this]() {
        int selectedId = _partialModeComboBox.getSelectedId();
        if (_partialModeIndex != RNBO::INVALID_INDEX)
            _rnboObject.setParameterValue(_partialModeIndex, static_cast<float>(selectedId - 1));
        };
    addAndMakeVisible(_partialModeComboBox);

    // Look And Feel
    _attackSlider.setLookAndFeel(&facetedLookAndFeel);
    _decaySlider.setLookAndFeel(&facetedLookAndFeel);
    _sustainSlider.setLookAndFeel(&facetedLookAndFeel);
    _releaseSlider.setLookAndFeel(&facetedLookAndFeel);

    facetedLookAndFeel.registerSlider(&_attackSlider);
    facetedLookAndFeel.registerSlider(&_decaySlider);
    facetedLookAndFeel.registerSlider(&_sustainSlider);
    facetedLookAndFeel.registerSlider(&_releaseSlider);

    // Graphics Timer
    startTimerHz(30); // 30 fps

}

void CustomAudioEditor::resized()
{

    _titleLabel.setBounds(0, 10, getWidth(), 30);
    _creatorLabel.setBounds(0, 30, getWidth(), 30);

    // GUI Elements
    int margin = 10;
    int labelWidth = 120;
    int sliderWidth = getWidth() - labelWidth - 2 * margin;
    int sliderHeight = 30;
    int y = 50;

    _attackSlider.setBounds(margin + labelWidth, y, sliderWidth, sliderHeight);
    y += sliderHeight;

    _decaySlider.setBounds(margin + labelWidth, y, sliderWidth, sliderHeight);
    y += sliderHeight;

    _sustainSlider.setBounds(margin + labelWidth, y, sliderWidth, sliderHeight);
    y += sliderHeight;

    _releaseSlider.setBounds(margin + labelWidth, y, sliderWidth, sliderHeight);

    _partialModeLabel.setBounds(20, 200, 100, 24);       // Label on the left
    _partialModeComboBox.setBounds(130, 200, 200, 24);   // ComboBox to the right
}

// This is the destructor
CustomAudioEditor::~CustomAudioEditor()
{
    _audioProcessor->AudioProcessor::removeListener(this);

    _attackSlider.setLookAndFeel(nullptr);
    _decaySlider.setLookAndFeel(nullptr);
    _sustainSlider.setLookAndFeel(nullptr);
    _releaseSlider.setLookAndFeel(nullptr);
}

void CustomAudioEditor::paint (Graphics& g)
{
    g.fillAll(Colours::white);
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
        int id = static_cast<int>(newValue) + 1; // combo IDs start at 1
        _partialModeComboBox.setSelectedId(id, juce::dontSendNotification);
    }
        });
}

void CustomAudioEditor::timerCallback()
{
    _pulseCounter++;

    // Pulsing alpha using sine wave
    float pulse = 0.4f + 0.6f * std::abs(std::sin(_pulseCounter * 0.06f)); // 0.4 to 1.0
    juce::Colour pulsingColour = _baseTitleColour.withAlpha(pulse);

    _titleLabel.setColour(juce::Label::textColourId, pulsingColour);

    // Paint our sliders
    _attackSlider.repaint();
    _decaySlider.repaint();
    _sustainSlider.repaint();
    _releaseSlider.repaint();
}
