/**
 * main.cpp
 * OpenAA main application.
 * 
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#include <cstdlib>
#include <iostream>
#include <portaudio.h>

//#include "Device/DeviceList.h"
#include "Device/AudioDevice.h"

using namespace std;

// Global variables.
PaError pa_err;

/**
 * Main entry-point for the application.
 * 
 * @param  argc Number of command-line arguments.
 * @param  argv Array of command-line arguments.
 * @return      Program return code.
 */
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
		// Get a new audio device.
		AudioDevice device(i, Pa_GetDeviceInfo(i));
		device.printInformation();
	}
	
	// Terminate PortAudio.
	Pa_Terminate();
	
	return 0;
}
