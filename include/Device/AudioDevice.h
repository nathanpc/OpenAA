/**
 * Device/AudioDevice.h
 * Abstract class to represent a audio device.
 * 
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#ifndef DEVICE_AUDIODEVICE_H_
#define DEVICE_AUDIODEVICE_H_

#include <string>
#include <vector>
#include <portaudio.h>

class AudioDevice {
	private:
	// Fields.
	int id;
	const PaDeviceInfo *device_info;
	std::string name;
	std::string host_api;
	int max_input_channels;
	int max_output_channels;
	bool default_input;
	bool default_output;
	std::vector<double> sample_rates;
	
	// Utilities.
	void populateSampleRates(const PaStreamParameters *input_params,
							 const PaStreamParameters *output_params);
	
	public:
	// Constructor.
	AudioDevice(const int _id, const PaDeviceInfo *_device_info);
	
	// Debug functions.
	void printInformation();
};

#endif
