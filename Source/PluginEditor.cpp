/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <math.h>

//==============================================================================
ImageGlowEffectPluginExAudioProcessorEditor::ImageGlowEffectPluginExAudioProcessorEditor (ImageGlowEffectPluginExAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), frame_count(0)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setOpaque (true);
    startTimerHz (30);
    
    setSize (800, 600);
    
    /**
    setGlowPropertiesの第一引数が大きいと処理が重くなるる
     */
    //eff.setGlowProperties (1.0f, juce::Colours::white, {0, 0});
    eff.setGlowProperties (1.0f, juce::Colours::white, {5, 5});
    //eff.setGlowProperties (1.0f, juce::Colours::red, {25, 25});
    //setComponentEffect(&eff);

    background = juce::ImageCache::getFromMemory(BinaryData::akiba_jpg, BinaryData::akiba_jpgSize);
    
}

ImageGlowEffectPluginExAudioProcessorEditor::~ImageGlowEffectPluginExAudioProcessorEditor()
{
}

void ImageGlowEffectPluginExAudioProcessorEditor::timerCallback()
{
    ++frame_count;
    
    repaint();
}

//==============================================================================
void ImageGlowEffectPluginExAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    
    //float alpha = 0.4f*sin((float)(frame_count)/180*M_PI) + 0.5f;
    float alpha = 0.5f*sin((float)(frame_count)/30*M_PI) + 0.5f;
    g.setFont (14.0f);
    juce::String str;
    str << "alpha:" << alpha << ":frame_count:" << frame_count;
    
    g.drawText (str, getLocalBounds(), juce::Justification::centredBottom, true);

    eff.applyEffect(background, g, 1.0f, alpha);
    
    /* 第３引数の数が大きくなると、処理が重くなる
     */
    //eff.applyEffect(background, g, 10.0f*sin((float)(frame_count)/30*M_PI), alpha);

    //g.drawImageAt(background, 10, 10);
    g.drawImageAt(background, 0, 0);
    
}

void ImageGlowEffectPluginExAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
