/**
 * Computation/FFT.h
 * Computes a Fast Fourier Transform.
 *
 * @author: Nathan Campos <nathan@innoveworkshop.com>
 */

#ifndef _FFT_H_
#define _FFT_H_

#include <vector>
#include <fftw3.h>

class FFT {
	private:
	size_t sample_size;
	std::vector<double> input_data;
	std::vector<double> output_data;
	fftw_plan plan;
		
	public:
	// Constructors and destructors.
	FFT();
	
	// Data manipulation.
	void loadData(std::vector<double> data);
	std::vector<double> getNormalizedOutput();
	
	// Computation.
	std::vector<double> execute();
	
	// Cleanup.
	void clean();
};

#endif /* _FFT_H_ */
