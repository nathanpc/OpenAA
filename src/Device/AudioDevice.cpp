/**
 * Device/AudioDevice.cpp
 * Abstract class to represent a audio device.
 * 
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#include "Device/AudioDevice.h"

#include <iostream>
#include <string>
#include <vector>
#include <portaudio.h>

using namespace std;

/**
 * AudioDevice constructor.
 * 
 * @param _id          Device ID.
 * @param _device_info  PortAudio device information pointer.
 */
AudioDevice::AudioDevice(const int _id, const PaDeviceInfo *_device_info) {
	// Populate simple fields.
	id = _id;
	device_info = _device_info;
	name = device_info->name;
	host_api = Pa_GetHostApiInfo(device_info->hostApi)->name;
	max_input_channels = device_info->maxInputChannels;
	max_output_channels = device_info->maxOutputChannels;
	
	// Check if default input device.
	if (Pa_GetDefaultInputDevice() == id) {
		default_input = true;
	} else {
		default_input = false;
	}
	
	// Check if default output device.
	if (Pa_GetDefaultOutputDevice() == id) {
		default_output = true;
	} else {
		default_output = false;
	}
	
	
	// Setup the input device parameters.
	PaStreamParameters input_param;
	input_param.device = id;
	input_param.channelCount = device_info->maxInputChannels;
	input_param.sampleFormat = paInt16;
	input_param.suggestedLatency = 0;
	input_param.hostApiSpecificStreamInfo = NULL;
	
	// TODO: Investigate sampleFormat for 32 bit HD audio maybe?
	
	// Setup the output device parameters.
	PaStreamParameters output_param;
	output_param.device = id;
	output_param.channelCount = device_info->maxOutputChannels;
	output_param.sampleFormat = paInt16;
	output_param.suggestedLatency = 0;
	output_param.hostApiSpecificStreamInfo = NULL;
	
	// Populate supported sample rates.
	populateSampleRates(&input_param, &output_param);
}

/**
 * Prints all of the information about the device.
 */
void AudioDevice::printInformation() {
	cout << "Device #" << id << " ";
		
	// Check if current device is the default input.
	if (default_input) {
		cout << "[Default Input] ";
	}
		
	// Check if current device is the default output.
	if (default_output) {
		cout << "[Default Output] ";
	}
		
	// Print main information about the device.
	cout << endl << "[" << host_api << "] " << name << endl;
	cout << "Max Inputs: " << max_input_channels << " - Max Outputs: " <<
		max_output_channels << endl;
	cout << "Default Sample Rate: " << device_info->defaultSampleRate << endl;
	cout << "Supported Sample Rates: ";
	for (size_t i = 0; i < sample_rates.size(); i++) {
		cout << sample_rates[i] << " ";
	}
	
	cout << endl << endl;
}

/**
 * Populates the supported sample rates vector.
 * 
 * @param input_params  Input device parameters.
 * @param output_params Output device parameters.
 */
void AudioDevice::populateSampleRates(const PaStreamParameters *input_params,
									  const PaStreamParameters *output_params) {
	PaError err;
	const double standard_sample_rates[] = {
		8000.0, 9600.0, 11025.0, 12000.0, 16000.0, 22050.0, 24000.0, 32000.0,
		44100.0, 48000.0, 88200.0, 96000.0, 192000.0, 0.0
	};
	
	// Get the supported standard sample rates for full-duplex.
	if (input_params->channelCount > 0 && output_params->channelCount > 0) {	
		// Loop through sample rates and determine if they are supported.
		for (int i = 0; standard_sample_rates[i] > 0; i++) {
			err = Pa_IsFormatSupported(input_params, output_params,
									   standard_sample_rates[i]);
			if (err == paFormatIsSupported) {
				sample_rates.push_back(standard_sample_rates[i]);
			}
		}
	}
}
