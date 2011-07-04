#include "LatencyAnalyzer.h"
#include <math.h>

void LatencyAnalyzer::audioDeviceIOCallback(const float **inputChannelData, int numInputChannels, float **outputChannelData, int numOutputChannels, 
											int numSamples)
{
    inRms = 0.f;
    for (int i=0; i<numSamples; i++)
        inRms += powf(inputChannelData[0][i],2.f);
    inRms /= (float)numSamples;
    inRms = powf(inRms,0.5f);

    for (int i=0; i<numOutputChannels; i++) {
        zeromem(outputChannelData[i], sizeof(float)*numSamples);
    }
	

}


void LatencyAnalyzer::buttonClicked (Button* button) {

	if(button == toggleButton) {					// start recording
		
        recording = !recording;
        if(recording) {
            audioDeviceManager.addAudioCallback(this);
            toggleButton->setButtonText("Stop recording");
        }
        else {
            audioDeviceManager.removeAudioCallback(this);
            toggleButton->setButtonText("Start recording");
        }
        
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

    repaint();
    
}

void LatencyAnalyzer::paint(Graphics &g) {
    
    float w = 100 * inRms;
    //g.setColour(Colour::getGreen());
    g.fillEllipse((float)getWidth()/2, (float)getHeight()/2, w, w);

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