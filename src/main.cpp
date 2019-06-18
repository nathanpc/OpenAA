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

// Global variables.
PaError pa_err;

/**
 * Print a list of supported standard sample rates for a given audio device.
 * 
 * @param input_params  Input device parameters.
 * @param output_params Output device parameters.
 */
void printSupportedSampleRates(const PaStreamParameters *input_params,
							   const PaStreamParameters *output_params) {
	const double standard_sample_rates[] = {
		8000.0, 9600.0, 11025.0, 12000.0, 16000.0, 22050.0, 24000.0, 32000.0,
		44100.0, 48000.0, 88200.0, 96000.0, 192000.0
	};
	
	// Loop through sample rates and determine if they are supported.
	cout << "Supported Sample Rates: ";
	for (int i = 0; standard_sample_rates[i] > 0; i++) {
		pa_err = Pa_IsFormatSupported(input_params, output_params,
								   standard_sample_rates[i]);
		if (pa_err == paFormatIsSupported) {
			cout << standard_sample_rates[i] << " ";
		}
	}
	
	cout << endl;
}

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
		
		// Print main information about the device.
		cout << endl << "[" << Pa_GetHostApiInfo(info->hostApi)->name << "] " << info->name << endl;
		cout << "Max Inputs: " << info->maxInputChannels << " - Max Outputs: " <<
			info->maxOutputChannels << endl;
		cout << "Default Sample Rate: " << info->defaultSampleRate << endl;
		
		// Setup the input device parameters.
		PaStreamParameters input_param;
		input_param.device = i;
		input_param.channelCount = info->maxInputChannels;
		input_param.sampleFormat = paInt16;
		input_param.suggestedLatency = 0;
        input_param.hostApiSpecificStreamInfo = NULL;
		
		// TODO: Investifate sampleFormat for 32 bit hi def audio maybe?

		// Setup the output device parameters.
		PaStreamParameters output_param;
        output_param.device = i;
        output_param.channelCount = info->maxOutputChannels;
		output_param.sampleFormat = paInt16;
		output_param.suggestedLatency = 0;
		output_param.hostApiSpecificStreamInfo = NULL;
		
		// Print the supported standard sample rates for full-duplex.
		if (input_param.channelCount > 0 && output_param.channelCount > 0) {
			printSupportedSampleRates(&input_param, &output_param);
		}
		
		cout << endl;
	}
	
	// Terminate PortAudio.
	Pa_Terminate();
	
	return 0;
}
