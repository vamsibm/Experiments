#include "LatencyAnalyzer.h"

void LatencyAnalyzer::audioDeviceIOCallback(const float **inputChannelData, int numInputChannels, float **outputChannelData, int numOutputChannels, 
											int numSamples)
{

	

}


void LatencyAnalyzer::buttonClicked (Button* button) {

	if(button == toggleButton) {					// start recording
		
        recording = !recording;
        if(recording)
            audioDeviceManager.addAudioCallback(this);
        else
            audioDeviceManager.removeAudioCallback(this);
        
	}

	else if(button == aConfigButton) {
        
		showAudioConfigDialog();
        
	}

}

void LatencyAnalyzer::audioDeviceAboutToStart (AudioIODevice* device) {

}

void LatencyAnalyzer::audioDeviceStopped() {

}

void LatencyAnalyzer::timerCallback() {


}

void LatencyAnalyzer::sliderValueChanged(Slider *slider) {


}

void LatencyAnalyzer::showAudioConfigDialog()
{
	// JUCE dialog to let user config audio settings
	AudioDeviceSelectorComponent adsc(audioDeviceManager, 1, 2, 2, 2, false, false, false, true);
	adsc.setSize (600, 300);
	DialogWindow::showModalDialog ("Audio Settings",
		&adsc,
		0,
		Colours::azure,
		true);
}