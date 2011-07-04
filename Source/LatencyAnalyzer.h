#ifndef LATENCYANALYZER_H
#define LATENCYANALYZER_H

#include "../JuceLibraryCode/JuceHeader.h"

class LatencyAnalyzer : public Component,  public ButtonListener, public SliderListener, public AudioIODeviceCallback, public Timer {

private:

	TextButton *toggleButton;
	TextButton *measureLatencyBtn;
	TextButton *aConfigButton;
	ToggleButton *muteInput, *muteOutput;
	Slider *shiftSlider;

    bool recording;
    
	const int sampleRate;
	const int bufferLength;
	AudioDeviceManager audioDeviceManager;


public:
	LatencyAnalyzer() : sampleRate (44100), bufferLength (960)

	{
        
        setSize(500, 400);
        
        recording = false;

		// setup toggle-button
		toggleButton = new TextButton (T("Toggle Start"));
		toggleButton->setBounds ( 100, 200, 100, 30);
		toggleButton->addListener (this);
		addAndMakeVisible (toggleButton);

        // setup audio config button
		aConfigButton = new TextButton (T("Audio Config Button"));
		aConfigButton->setBounds (600, 200, 100, 30);
		aConfigButton->addListener (this);
		addAndMakeVisible (aConfigButton);

		// setup shift slider
		shiftSlider = new Slider (T("Align Slider"));
		shiftSlider->setBounds (50, 350, 450, 30);
		shiftSlider->addListener(this);
		addAndMakeVisible (shiftSlider);
		shiftSlider->setEnabled(false);

		// set up the Audio Device; with the required parameters.
		audioDeviceManager.initialise (2, 2, 0, true, String::empty, 0);
		AudioDeviceManager::AudioDeviceSetup myAudioDevice;
		audioDeviceManager.getAudioDeviceSetup(myAudioDevice);
		myAudioDevice.sampleRate = sampleRate;
		myAudioDevice.bufferSize = bufferLength;
		audioDeviceManager.setAudioDeviceSetup(myAudioDevice,true);
		AudioDeviceManager::AudioDeviceSetup newAudioDevice;
		audioDeviceManager.getAudioDeviceSetup(newAudioDevice);
        
		startTimer (1000 / 10);
	}

	~LatencyAnalyzer() {
		deleteAllChildren();
	}

	void buttonClicked (Button* button);
	void sliderValueChanged(Slider *slider);

	void audioDeviceIOCallback (const float** inputChannelData, int numInputChannels, float** outputChannelData,int numOutputChannels, int numSamples);

	void processO(float** outputChannelData, int totalNumOutputChannels, int numSamples, int currentTime);

	void audioDeviceAboutToStart (AudioIODevice* device);
	void audioDeviceStopped();
	void timerCallback();
	void showAudioConfigDialog();

};

#endif