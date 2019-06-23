/**
 * Computation/FFT.cpp
 * Computes a Fast Fourier Transform.
 *
 * @author: Nathan Campos <nathan@innoveworkshop.com>
 */

#include "Computation/FFT.h"

#include <iostream>
#include <vector>
#include <stdexcept>
#include <fftw3.h>

using namespace std;

/**
 * FFT constructor.
 */
FFT::FFT() {
	sample_size = 0;
}

/**
 * Loads the input data samples to be used in the FFT.
 * 
 * @param data Input samples.
 */
void FFT::loadData(vector<double> data) {
	// Check if the sampled data is divisible by 2.
	sample_size = data.size();
	if ((sample_size % 2) != 0) {
		throw invalid_argument("Sampled data size must be a power of 2");
	}
	
	// Load the data and allocate the space required for the output vector.
	input_data = data;
	output_data = vector<double>(sample_size / 2, 0.0);
}

/**
 * Runs the FFT function and returns the non-normalized computed data.
 * 
 * @return Non-normalized FFT output data.
 */
vector<double> FFT::execute() {
	double *out = fftw_alloc_real(sample_size);
	
	// Check if there is any input data loaded.
	if ((sample_size == 0) || input_data.empty()) {
		throw length_error("No input data loaded to execute the FFT function");
	}
	
	// Create a FFTW plan and execute it.
	plan = fftw_plan_r2r_1d(sample_size, input_data.data(), out,
							FFTW_R2HC, FFTW_ESTIMATE);
	fftw_execute(plan);
	
	// Copy the contents of the output array into our output vector.
	for (size_t i = 0; i < (sample_size / 2); i++) {
		output_data[i] = out[i];
	}
	
	// Free up the output data.
	fftw_free(out);
	
	return output_data;
}

/**
 * Cleans up the mess left by the FFTW library.
 */
void FFT::clean() {
	fftw_destroy_plan(plan);
	fftw_cleanup();
}

/**
 * Gets the normalized output FFT data.
 * 
 * @return Normalized output data. 
 */
vector<double> FFT::getNormalizedOutput() {
	vector<double> norm = output_data;
	
	// Loop through each sample and normalize it.
	for (size_t i = 0; i < norm.size(); i++) {
		norm[i] /= sample_size / 2;
	}
	
	return norm;
}
