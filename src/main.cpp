/**
 * main.cpp
 * OpenAA main application.
 * 
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#include <cstdlib>
#include <iostream>
#include <portaudio.h>

#include "AudioInterface.h"
#include "Device/DeviceList.h"
#include "Device/AudioDevice.h"

using namespace std;

/**
 * Main entry-point for the application.
 * 
 * @param  argc Number of command-line arguments.
 * @param  argv Array of command-line arguments.
 * @return      Program return code.
 */
int main(int argc, char **argv) {
	AudioInterface interface;
	
	// Initialize PortAudio.
	interface.initialize();
	
	// Get available devices list.
	DeviceList device_list;
	
	// Iterate over each device and get information about it.
	for (size_t i = 0; i < device_list.size(); i++) {
		// Get a new audio device.
		AudioDevice device = device_list.getDevice(i);
		device.printInformation();
	}
	
	// Terminate PortAudio.
	interface.terminate();
	
	return 0;
}
