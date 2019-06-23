/**
 * main.cpp
 * OpenAA main application.
 * 
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <fstream>
#include <portaudio.h>
#include <vector>
#include <fftw3.h>

#include "AudioInterface.h"
#include "Device/DeviceList.h"
#include "Device/AudioDevice.h"
#include "Computation/FFT.h"

using namespace std;

double cos_wave(double amplitude, unsigned int freq, size_t sample_num,
				size_t sample_size) {
	return amplitude * cos(freq * 2 * M_PI * sample_num / sample_size);
}

/**
 * Main entry-point for the application.
 * 
 * @param  argc Number of command-line arguments.
 * @param  argv Array of command-line arguments.
 * @return      Program return code.
 */
int main(int argc, char **argv) {
	/*	AudioInterface interface;
	
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
	interface.terminate();*/
	
	// FFTW3 tests.
	#define N 2000
	vector<double> samples;
	ofstream csv;

	// Generate some signals.
	for (size_t i = 0; i < N; i++) {
		samples.push_back(cos_wave(4, 200, i, N) +
						  cos_wave(3, 600, i, N) +
						  cos_wave(2, 900, i, N));
	}
	
	// Compute the FFT.
	FFT fft;
	fft.loadData(samples);
	fft.execute();
	vector<double> out = fft.getNormalizedOutput();
	
	csv.open("/home/nathan/fft.csv");
	for (size_t i = 0; i < (N / 2); i++) {
		// Print stuff.
		csv << i << ", " << out[i] << endl;
		cout << i << "Hz: " << out[i] << endl;
	}
	
	csv.close();
	fft.clean();
	
	return 0;
}
