/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
WaveStormAudioProcessorEditor::WaveStormAudioProcessorEditor (WaveStormAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    
     setSize(480, 320);
     
     
     addAndMakeVisible(bypassButton);
     bypassButton.setButtonText("Bypass");

     addAndMakeVisible (textLabel);
     textLabel.setFont (textFont);
     addAndMakeVisible (oscillatorComboBox);
     oscillatorComboBox.addItem ("sine",  1);
     oscillatorComboBox.addItem ("sawtooth",   2);
     oscillatorComboBox.addItem ("triangle", 3);
     oscillatorComboBox.addItem ("square", 4);
     oscillatorComboBox.setSelectedId (1);



     addAndMakeVisible(feedbackLabel);
     addAndMakeVisible(delayTimeLabel);
     addAndMakeVisible(dryWetLabel);
     feedbackLabel.setText("Feedback", juce::NotificationType::dontSendNotification);
     addAndMakeVisible(feedbackSlider);


     delayTimeLabel.setText("DelayTime", juce::NotificationType::dontSendNotification);
     addAndMakeVisible(delayTimeKnob);



     dryWetLabel.setText("Wetness(%)", juce::NotificationType::dontSendNotification);
     addAndMakeVisible(dryWetKnob);




     //paraEQ knobs
     addAndMakeVisible(eqFcenterLabel);
     addAndMakeVisible(eqQKnobLabel);
     addAndMakeVisible(eqGainKnobLabel);

     eqFcenterLabel.setText("F Center", juce::NotificationType::dontSendNotification);
     addAndMakeVisible(eqFcenterKnob);



     eqQKnobLabel.setText("Q Factor", juce::NotificationType::dontSendNotification);
     addAndMakeVisible(eqQKnob);


     eqGainKnobLabel.setText("EQ Gain", juce::NotificationType::dontSendNotification);
     addAndMakeVisible(eqGainKnob);


     //outputgain
     addAndMakeVisible(outputGainLabel);
     outputGainLabel.setText("Output Gain", juce::NotificationType::dontSendNotification);
     addAndMakeVisible(outputGainSlider);


     //feedback styling

     feedbackSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
     //feedbackSlider.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::grey);
     feedbackSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::purple);
     feedbackSlider.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::white);
     feedbackSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 30, 20);

     //label

     feedbackLabel.attachToComponent(&feedbackSlider, false);
     feedbackLabel.setFont(juce::Font(15.0f, juce::Font::plain));
     feedbackLabel.setJustificationType(juce::Justification::centredTop);
     feedbackLabel.setColour(juce::Label::textColourId, juce::Colours::whitesmoke);
     feedbackLabel.setColour(juce::Label::backgroundColourId, juce::Colour(juce::Colours::transparentBlack));
     //Delay time knob styling

     delayTimeKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
     delayTimeKnob.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::purple);
     delayTimeKnob.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::white);
     delayTimeKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 30, 20);
     //label


     delayTimeLabel.attachToComponent(&delayTimeKnob, false);
     delayTimeLabel.setFont(juce::Font(15.0f, juce::Font::plain));
     delayTimeLabel.setJustificationType(juce::Justification::centredTop);
     delayTimeLabel.setColour(juce::Label::textColourId, juce::Colours::whitesmoke);
     delayTimeLabel.setColour(juce::Label::backgroundColourId, juce::Colour(juce::Colours::transparentBlack));

     // Dry/Wet Knob Styling
     dryWetKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
     dryWetKnob.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::purple);
     dryWetKnob.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::white);
     dryWetKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 40, 20);
     //label


     dryWetLabel.attachToComponent(&dryWetKnob, false);
     dryWetLabel.setFont(juce::Font(15.0f, juce::Font::plain));
     dryWetLabel.setJustificationType(juce::Justification::centredTop);
     dryWetLabel.setColour(juce::Label::textColourId, juce::Colours::whitesmoke);
     dryWetLabel.setColour(juce::Label::backgroundColourId, juce::Colour(juce::Colours::transparentBlack));


     //eq knob styling
     //
     eqFcenterKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
     eqFcenterKnob.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::purple);
     eqFcenterKnob.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::white);
     eqFcenterKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 25);


     eqFcenterLabel.attachToComponent(&eqFcenterKnob, false);
     eqFcenterLabel.setFont(juce::Font(15.0f, juce::Font::plain));
     eqFcenterLabel.setJustificationType(juce::Justification::centredTop);
     eqFcenterLabel.setColour(juce::Label::textColourId, juce::Colours::whitesmoke);
     eqFcenterLabel.setColour(juce::Label::backgroundColourId, juce::Colour(juce::Colours::transparentBlack));

     //
     eqQKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
     eqQKnob.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::purple);
     eqQKnob.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::white);
     eqQKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 30, 25);
     //label


     eqQKnobLabel.attachToComponent(&eqQKnob, false);
     eqQKnobLabel.setFont(juce::Font(15.0f, juce::Font::plain));
     eqQKnobLabel.setJustificationType(juce::Justification::centredTop);
     eqQKnobLabel.setColour(juce::Label::textColourId, juce::Colours::whitesmoke);
     eqQKnobLabel.setColour(juce::Label::backgroundColourId, juce::Colour(juce::Colours::transparentBlack));


     //EQ Gain Knob
     eqGainKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
     eqGainKnob.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::purple);
     eqGainKnob.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::white);
     eqGainKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 40, 25);
     //label


     eqGainKnobLabel.attachToComponent(&eqGainKnob, false);
     eqGainKnobLabel.setFont(juce::Font(15.0f, juce::Font::plain));
     eqGainKnobLabel.setJustificationType(juce::Justification::centredTop);
     eqGainKnobLabel.setColour(juce::Label::textColourId, juce::Colours::whitesmoke);
     eqGainKnobLabel.setColour(juce::Label::backgroundColourId, juce::Colour(juce::Colours::transparentBlack));


     //

     //outputGainSlider styling
      //feedback styling

     outputGainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
     outputGainSlider.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::black.contrasting(0.1));
     outputGainSlider.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::purple);
     outputGainSlider.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::white.darker(0.2));
     outputGainSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 30, 20);

     //label

     outputGainLabel.attachToComponent(&outputGainSlider, false);
     outputGainLabel.setFont(juce::Font(15.0f, juce::Font::plain));
     outputGainLabel.setJustificationType(juce::Justification::centredTop);
     outputGainLabel.setColour(juce::Label::textColourId, juce::Colours::whitesmoke);
     outputGainLabel.setColour(juce::Label::backgroundColourId, juce::Colour(juce::Colours::transparentBlack));
    
    
    //bypass

    
//     // Step 1: Use the getParameters() function to get the audio parameter tree
    
    
//
     auto parameterTree = audioProcessor.getParameters();
//
//     /*
//         Step 2: Use the function getUnchecked() to get the pointer to the specific parameter for your knob and slider and we cast it to a AudioParameterFloat
//     */
     feedbackSliderParameter = (juce::AudioParameterFloat*)parameterTree.getUnchecked(0);
     delayTimeKnobParameter = (juce::AudioParameterFloat*)parameterTree.getUnchecked(1);
     dryWetKnobParameter = (juce::AudioParameterFloat*)parameterTree.getUnchecked(2);
     eqFcenterKnobParameter = (juce::AudioParameterFloat*)parameterTree.getUnchecked(3);
     eqQKnobParameter = (juce::AudioParameterFloat*)parameterTree.getUnchecked(4);
     eqGainKnobParameter = (juce::AudioParameterFloat*)parameterTree.getUnchecked(5);
     outputGainParameter = (juce::AudioParameterFloat*)parameterTree.getUnchecked(6);
     oscillatorTypeParameter = (juce::AudioParameterInt*)parameterTree.getUnchecked(7);
     bypassParameter = (juce::AudioParameterBool*)parameterTree.getUnchecked(8);
//     /*
//         Step 3: Use the function setRange() to set the Ranges of your knob and slider
//     */
     feedbackSlider.setRange(feedbackSliderParameter->range.start, feedbackSliderParameter->range.end, feedbackSliderParameter->range.interval);

     delayTimeKnob.setRange(delayTimeKnobParameter->range.start, delayTimeKnobParameter->range.end, delayTimeKnobParameter->range.interval);

     dryWetKnob.setRange(dryWetKnobParameter->range.start, dryWetKnobParameter->range.end, dryWetKnobParameter->range.interval);

     eqFcenterKnob.setRange(eqFcenterKnobParameter->range.start, eqFcenterKnobParameter->range.end, eqFcenterKnobParameter->range.interval);

     eqQKnob.setRange(eqQKnobParameter->range.start, eqQKnobParameter->range.end, eqQKnobParameter->range.interval);

     eqGainKnob.setRange(eqGainKnobParameter->range.start, eqGainKnobParameter->range.end, eqGainKnobParameter->range.interval);

     outputGainSlider.setRange(outputGainParameter->range.start, outputGainParameter->range.end, outputGainParameter->range.interval);
//
//
//
//     // Step 4: Set the default Value of the sliderand knob
//
     feedbackSlider.setValue(5.0f, juce::NotificationType::dontSendNotification);

     delayTimeKnob.setValue(1.0f, juce::NotificationType::dontSendNotification);

     dryWetKnob.setValue(50.0f, juce::NotificationType::dontSendNotification);

     eqFcenterKnob.setValue(500.0f, juce::NotificationType::dontSendNotification);

     eqQKnob.setValue(0.0f, juce::NotificationType::dontSendNotification);

     eqGainKnob.setValue(0.0f, juce::NotificationType::dontSendNotification);

     outputGainSlider.setValue(0.0f, juce::NotificationType::dontSendNotification);
 
     /*
         Step 5 : Use the lamda function to setValue of the audio processor parameters
     */
     feedbackSlider.onValueChange = [this]
     {
         *feedbackSliderParameter = feedbackSlider.getValue();
     };

     delayTimeKnob.onValueChange = [this]
     {
         *delayTimeKnobParameter = delayTimeKnob.getValue();
     };


     dryWetKnob.onValueChange = [this]
     {
         *dryWetKnobParameter = dryWetKnob.getValue();
     };


     eqFcenterKnob.onValueChange = [this]
     {
         *eqFcenterKnobParameter = eqFcenterKnob.getValue();
     };

     eqQKnob.onValueChange = [this]
     {
         *eqQKnobParameter = eqQKnob.getValue();
     };

     eqGainKnob.onValueChange = [this]
     {
         *eqGainKnobParameter = eqGainKnob.getValue();
     };
     outputGainSlider.onValueChange = [this]
     {
         *outputGainParameter = outputGainSlider.getValue();
     };

     oscillatorComboBox.onChange = [this](){
         DBG(oscillatorComboBox.getSelectedId());
         int selectedItemId = oscillatorComboBox.getSelectedId();

          // Update the plugin processor's parameter here based on the selected item

         *oscillatorTypeParameter = selectedItemId;

     };
     bypassButton.setToggleState(*bypassParameter, juce::NotificationType::dontSendNotification);

     bypassButton.onStateChange = [this]
             {

                 const bool isBypassed = bypassButton.getToggleState();
//                     if (isBypassed)
//                     {
//                         bypassButton.setColour(<#int colourID#>, <#Colour newColour#>);
//                     }
//                     else
//                     {
//                         bypassButton.setColour(juce::TextButton::buttonColourId,juce::Colours::grey);
//                     }

                     *bypassParameter = isBypassed;
             //   DBG(juce::String(bypassParameter));


             };
}

WaveStormAudioProcessorEditor::~WaveStormAudioProcessorEditor()
{
}

//==============================================================================
void WaveStormAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    //g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

//    g.setColour (juce::Colours::white);
//    g.setFont (15.0f);
//    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
    background = juce::ImageCache::getFromMemory(BinaryData::background_png, BinaryData::background_pngSize);
    g.drawImageWithin(background, 0, 0, getWidth(), getHeight(), juce::RectanglePlacement::stretchToFit);
    //g.fillAll(juce::Colours::purple.darker(1.9)); // Dark gray background
    g.setColour (juce::Colours::whitesmoke);
    g.setFont(25.0f);
    
    g.setOpacity(0.9f);

    g.drawFittedText ("~ WaveStorm ~", getLocalBounds(), juce::Justification::centredTop, 1);
    // Define the background colors for the bordered divisions
    juce::Colour division1Color = juce::Colours::purple.darker(0.8);
    // Change this to your desired color
    juce::Colour division2Color = juce::Colours::purple.darker(0.8);  // Change this to your desired color

    
    auto x = getWidth() / 10;
    auto y = getHeight() / 10;
    
    juce::Rectangle<int> division1Bounds(0.2 * x, 0.9* y, 2.4 *x, 8.8* y);
    juce::Rectangle<int> division2Bounds(2.8 * x, 0.9 * y, 6.2 * x, 8.8 * y);

    // Set the background colors for the bordered divisions
    g.setColour(division1Color);
    g.fillRect(division1Bounds);

    g.setColour(division2Color);
    g.fillRect(division2Bounds);
    
    
    auto borderThickness = 4;
       auto borderColor = juce::Colours::darkviolet.darker(2.8);

      // juce::Rectangle<int> borderRect = feedbackSlider.getBounds().reduced(borderThickness);

       // Draw the border around the feedback slider
      // g.setColour(borderColor);

    //juce::BorderSize<int> innerBorder(2); // Adjust the border thickness as needed

       // Calculate the combined bounds for both the ComboBox and feedbackSlider
       juce::Rectangle<int> combinedBoundsOne = outputGainSlider.getBounds().getUnion(oscillatorComboBox.getBounds());
    combinedBoundsOne = combinedBoundsOne.expanded(10);
       // Apply the inner border to the combined bounds
    //combinedBounds = combinedBounds.withTrim
       // Draw the outer border around the combined components
       g.setColour(borderColor);
       g.drawRect(combinedBoundsOne, borderThickness);

    // Adjust the outer border thickness as needed
    juce::Rectangle<int> combinedBoundsTwo = delayTimeKnob.getBounds().getUnion(eqGainKnob.getBounds());
    combinedBoundsTwo = combinedBoundsTwo.expanded(30);
    // Apply the inner border to the combined bounds
 //combinedBounds = combinedBounds.withTrim
  //   Draw the outer border around the combined components
    g.setColour(borderColor);
    g.drawRect(combinedBoundsTwo, borderThickness);

//
}

void WaveStormAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
        auto x = getWidth() / 10;
        auto y = getHeight() / 10;

        /*
            Use the setBounds() function to position the GUI Components (x,y) and set the width and height (width,height)
         
        */
        oscillatorComboBox.setBounds(0.4 * x, 1.2 * y, 2 *x, 0.8 * y);
        outputGainSlider.setBounds(0.4 * x, 3.6 * y, 2 * x, 5.8 * y);
    
        delayTimeKnob.setBounds(3.4 * x, 1.8 * y, 2 * x, 3 * y);
    
        dryWetKnob.setBounds(6.4 * x, 1.8 * y, 2 * x, 3 * y);
    
        eqFcenterKnob.setBounds(3.4 * x, 5.8 * y, 2 * x, 3 * y);
    
        eqGainKnob.setBounds(6.4 * x, 5.8 * y, 2 * x, 3* y);
    
        eqQKnob.setBounds(4.9 * x, 5.8 * y, 2 * x, 3 * y);
    
        feedbackSlider.setBounds(4.9 * x, 1.8 * y, 2 * x, 3 * y);
    
        bypassButton.setBounds(4.9 * x, 8.8 * y, 1.4 * x, 1 * y);
//
}
