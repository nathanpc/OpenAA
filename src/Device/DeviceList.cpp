/**
 * Device/DeviceList.cpp
 * A list and a manager of audio devices.
 * 
 * @author Nathan Campos <nathan@innoveworkshop.com>
 */

#include "Device/DeviceList.h"

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <portaudio.h>

#include "AudioInterface.h"
#include "Device/AudioDevice.h"

using namespace std;

/**
 * Device list constructor.
 */
DeviceList::DeviceList() {
	// Populate the device list.
	populateDevices();
}

/**
 * Populates the internal device vector.
 */
void DeviceList::populateDevices() {
	// Get number of devices available.
	int dev_count = Pa_GetDeviceCount();
	if (dev_count < 0) {
		PaError err = dev_count;
		
		cout << "Unable to get the list of audio devices available: ";
		AudioInterface::printError(err, true);
	}

	// Iterate over each device.
	for (int i = 0; i < dev_count; i++) {
		// Get a new audio device.
		AudioDevice device(i, Pa_GetDeviceInfo(i));
		list.push_back(device);
	}
}

/**
 * Gets the size of the list.
 * 
 * @return List size.
 */
size_t DeviceList::size() {
	return list.size();
}

/**
 * Gets a device from the list at a specific position.
 * 
 * @param  i List index.
 * @return   Desired device.
 */
AudioDevice DeviceList::getDevice(size_t i) {
	return list[i];
}
