/**
 * AudioInterface.cpp
 * Basically a wrapper around PortAudio.
 * 
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#include "AudioInterface.h"

#include <iostream>
#include <portaudio.h>

using namespace std;

/**
 * PortAudio wrapper constructor.
 */
AudioInterface::AudioInterface() {
}

/**
 * Initializes the audio interface.
 */
void AudioInterface::initialize() {
	PaError err;
	
	// Initialize PortAudio.
	cout << "Initializing PortAudio..." << endl;
	err = Pa_Initialize();
	if (err != paNoError) {
		cerr << "An error occurred when trying to initialize PortAudio: ";
		printError(err, true);
	}
	
	// Print some PortAudio information.
	cout << Pa_GetVersionText() << endl;
}

/**
 * Terminates the audio interface.
 */
void AudioInterface::terminate() {
	// Terminate PortAudio.
	cout << "Terminating PortAudio..." << endl;
	Pa_Terminate();
}

/**
 * Prints a detailed PortAudio error message and exits if required.
 * 
 * @param err     PortAudio error code.
 * @param do_exit Exit after displaying the error.
 */
void AudioInterface::printError(PaError err, bool do_exit) {
	// Print error.
	cerr << "[" << err << "] " << Pa_GetErrorText(err) << endl;
	
	// Exit if required.
	if (do_exit) {
		terminate();
		exit(EXIT_FAILURE);
	}
}
