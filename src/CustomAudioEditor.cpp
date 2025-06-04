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
    _titleLabel.setText("crystallophon", juce::dontSendNotification);
    _titleLabel.setJustificationType(juce::Justification::topLeft);
    _titleLabel.setFont(juce::Font(20.0f, juce::Font::bold | juce::Font::italic));
    _titleLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    addAndMakeVisible(_titleLabel);

    // --- Creator Label ---
    _creatorLabel.setText("esmw", juce::dontSendNotification);
    _creatorLabel.setJustificationType(juce::Justification::topLeft);
    _creatorLabel.setFont(juce::Font(10.0f, juce::Font::bold));
    _creatorLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    addAndMakeVisible(_creatorLabel);

    // --- GUI Elements ---

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
    addAndMakeVisible(_decaySlider);

    _decayLabel.setText("d", juce::dontSendNotification);
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
    addAndMakeVisible(_sustainSlider);

    _sustainLabel.setText("s", juce::dontSendNotification);
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
    addAndMakeVisible(_releaseSlider);

    _releaseLabel.setText("r", juce::dontSendNotification);
    _releaseLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    _releaseLabel.attachToComponent(&_releaseSlider, true);
    addAndMakeVisible(_releaseLabel);

    // --- Partial Mode Label ---
    _partialModeLabel.setText("partial mode", juce::dontSendNotification);
    _partialModeLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    addAndMakeVisible(_partialModeLabel);

    _partialModeIndex = _rnboObject.getParameterIndexForID("partialMode");

    // --- Partial Mode ComboBox ---
    _partialModeComboBox.addItem("semi", 1);
    _partialModeComboBox.addItem("ratio", 2);
    _partialModeComboBox.addItem("freq", 3);
    _partialModeComboBox.setSelectedId(1); // Default
    _partialModeComboBox.onChange = [this]() {
        int selectedId = _partialModeComboBox.getSelectedId();
        if (_partialModeIndex != RNBO::INVALID_INDEX)
            _rnboObject.setParameterValue(_partialModeIndex, static_cast<float>(selectedId - 1));
        };
    addAndMakeVisible(_partialModeComboBox);

    // --- ADSR Display ---

    addAndMakeVisible(adsrDisplay);

    auto updateADSRDisplay = [this]()
        {
            adsrDisplay.setEnvelope((float)juce::jmap((float)_attackSlider.getValue(), 0.1f, 2000.0f, 0.0f, 1.0f),
                (float)juce::jmap((float)_decaySlider.getValue(), 0.1f, 2000.0f, 0.0f, 1.0f),
                (float)_sustainSlider.getValue(),
                (float)juce::jmap((float)_releaseSlider.getValue(), 0.1f, 2000.0f, 0.0f, 1.0f));
        };

    _attackSlider.onValueChange = updateADSRDisplay;
    _decaySlider.onValueChange = updateADSRDisplay;
    _sustainSlider.onValueChange = updateADSRDisplay;
    _releaseSlider.onValueChange = updateADSRDisplay;

    // Initial update to set visual correctly at launch
    updateADSRDisplay();

    // --- Button Group ---

    auto* partialModeButtons = new EsmwButtonGroup({ "semi", "ratio", "freq" });
    addAndMakeVisible(partialModeButtons);
    partialModeButtons->setBounds(20, 400, 300, 30);

    // --- Crystal Pitch Visualizer

    addAndMakeVisible(pitchViz);

    // Set position in resized():
    pitchViz.setBounds(20, 500, 200, 200);

    // Update values dynamically:
    pitchViz.setPitches(
        0.5f,  // low pitch position on left edge (middle)
        0.5f,  // mid pitch position on bottom edge (middle)
        0.5f,  // high pitch position on right edge (middle)
        1.0f,  // low intensity (full glow)
        1.0f,  // mid intensity
        1.0f   // high intensity
    );

    // Look And Feel
    _attackSlider.setLookAndFeel(&customLookAndFeel);
    _decaySlider.setLookAndFeel(&customLookAndFeel);
    _sustainSlider.setLookAndFeel(&customLookAndFeel);
    _releaseSlider.setLookAndFeel(&customLookAndFeel);

    _partialModeComboBox.setLookAndFeel(&customLookAndFeel);

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
    int sliderHeight = 20;
    int y = 50;

    _attackSlider.setBounds(margin + labelWidth, y, sliderWidth, sliderHeight);
    y += sliderHeight;

    _decaySlider.setBounds(margin + labelWidth, y, sliderWidth, sliderHeight);
    y += sliderHeight;

    _sustainSlider.setBounds(margin + labelWidth, y, sliderWidth, sliderHeight);
    y += sliderHeight;

    _releaseSlider.setBounds(margin + labelWidth, y, sliderWidth, sliderHeight);

    _partialModeLabel.setBounds(20, 200, 100, 24);       // Label on the left
    _partialModeComboBox.setBounds(130, 200, 50, 24);   // ComboBox to the right

    adsrDisplay.setBounds(20, 250, 300, 100);

}

// This is the destructor
CustomAudioEditor::~CustomAudioEditor()
{
    _audioProcessor->AudioProcessor::removeListener(this);

    _attackSlider.setLookAndFeel(nullptr);
    _decaySlider.setLookAndFeel(nullptr);
    _sustainSlider.setLookAndFeel(nullptr);
    _releaseSlider.setLookAndFeel(nullptr);

    _partialModeComboBox.setLookAndFeel(nullptr);
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
        int id = static_cast<int>(newValue) + 1; // combo IDs start at 1
        _partialModeComboBox.setSelectedId(id, juce::dontSendNotification);
    }
        });
}

void CustomAudioEditor::timerCallback()
{
    _pulseCounter++;

    // Pulsing alpha using sine wave
    float pulse = 0.2f + 0.8f * std::abs(std::sin(_pulseCounter * 0.1f));
    juce::Colour pulsingColour = juce::Colours::black.withAlpha(pulse);

    _titleLabel.setColour(juce::Label::textColourId, pulsingColour);
}
