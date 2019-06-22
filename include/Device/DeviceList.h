/**
 * Device/DeviceList.h
 * A list and a manager of audio devices.
 * 
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#ifndef DEVICE_DEVICELIST_H_
#define DEVICE_DEVICELIST_H_

#include <string>
#include <vector>
#include <portaudio.h>

#include "Device/AudioDevice.h"

class DeviceList {
	private:
	// Fields.
	std::vector<AudioDevice> list;
	
	// Utilities.
	void populateDevices();
	
	public:
	// Constructor.
	DeviceList();
	
	// Capacity.
	size_t size();
	
	// Element access.
	AudioDevice getDevice(size_t i);
};

#endif
