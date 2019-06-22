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
#include <fftw3.h>

#include "AudioInterface.h"
#include "Device/DeviceList.h"
#include "Device/AudioDevice.h"

using namespace std;

double cos_wave(double amplitude, unsigned int freq, unsigned int sample_num,
				unsigned int sample_size) {
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
	double in[N], out[N];
	ofstream csv;

	/* prepare a cosine wave */
	for (int i = 0; i < N; i++) {
		in[i] = cos_wave(4, 200, i, N) +
			cos_wave(3, 600, i, N) +
			cos_wave(2, 900, i, N);
	}

	/* forward Fourier transform, save the result in 'out' */
	fftw_plan p = fftw_plan_r2r_1d(N, in, out, FFTW_R2HC, FFTW_ESTIMATE);
	fftw_execute(p);
	
	csv.open("/home/nathan/fft.csv");
	for (int i = 0; i < (N / 2); i++) {
		// Normalize output.
		out[i] /= N / 2;
		
		// Print stuff.
		csv << i << ", " << out[i] << endl;
		cout << i << "Hz: " << out[i] << endl;
	}
	
	csv.close();
	fftw_destroy_plan(p);
	fftw_cleanup();
	
	return 0;
}
