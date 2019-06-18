/**
 * main.cpp
 * OpenAA main application.
 * 
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#include <cstdlib>
#include <iostream>
#include <portaudio.h>

using namespace std;

PaError pa_err;

int main(int argc, char **argv) {
	// Initialize PortAudio.
	cout << "Initializing PortAudio..." << endl;
	pa_err = Pa_Initialize();
	if (pa_err != paNoError) {
		cout << "An error occurred when trying to initialize PortAudio: [" <<
			pa_err << "] " << Pa_GetErrorText(pa_err) << endl;
		return EXIT_FAILURE;
	}
	
	// Print some PortAudio information.
	cout << Pa_GetVersionText() << endl;
	
	// Get number of devices available.
	int dev_count = Pa_GetDeviceCount();
	if (dev_count < 0) {
		pa_err = dev_count;
		cout << "Unable to get the list of audio devices available: [" <<
			pa_err << "] " << Pa_GetErrorText(pa_err) << endl;
		return EXIT_FAILURE;
	}
	
	// Iterate over each device and get information about it.
	for (int i = 0; i < dev_count; i++) {
		// Get device information structure.
		const PaDeviceInfo *info = Pa_GetDeviceInfo(i);
		
		cout << "Device #" << i << " ";
		
		// Check if current device is the default input.
		if (Pa_GetDefaultInputDevice() == i) {
			cout << "[Default Input] ";
		}
		
		// Check if current device is the default output.
		if (Pa_GetDefaultOutputDevice() == i) {
			cout << "[Default Output] ";
		}
		
		cout << endl << "[" << Pa_GetHostApiInfo(info->hostApi)->name << "] " << info->name << endl;
		cout << "Max Inputs: " << info->maxInputChannels << " - Max Outputs: " <<
			info->maxOutputChannels << endl;
		cout << "Default Sample Rate: " << info->defaultSampleRate << endl;
		cout << endl;
	}
	
	// Terminate PortAudio.
	Pa_Terminate();
	
	return 0;
}
