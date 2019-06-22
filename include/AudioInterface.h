/**
 * AudioInterface.h
 * Basically a wrapper around PortAudio.
 * 
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#ifndef AUDIOINTERFACE_H_
#define AUDIOINTERFACE_H_

#include <portaudio.h>

class AudioInterface {	
	public:
	// Constructor.
	AudioInterface();
	
	// Initialization and destruction.
	void initialize();
	void terminate();
	
	// Errors.
	void printError(PaError err, bool do_exit);
};

#endif
