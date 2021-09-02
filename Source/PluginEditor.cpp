/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ImageGlowEffectPluginExAudioProcessorEditor::ImageGlowEffectPluginExAudioProcessorEditor (ImageGlowEffectPluginExAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 600);
        
    eff.setGlowProperties (1.0f, juce::Colours::white, {5, 5});
    //setComponentEffect(&eff);

    background = juce::ImageCache::getFromMemory(BinaryData::akiba_jpg, BinaryData::akiba_jpgSize);
    
}

ImageGlowEffectPluginExAudioProcessorEditor::~ImageGlowEffectPluginExAudioProcessorEditor()
{
}

//==============================================================================
void ImageGlowEffectPluginExAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    
    eff.applyEffect(background, g, 1.0f, 0.5);
    g.drawImageAt(background, 10, 10);
    
}

void ImageGlowEffectPluginExAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
