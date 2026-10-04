#include "SoundDevice.h"
#include <stdio.h>

SoundDevice* SoundDevice::get() {
	static SoundDevice* snd_device = new SoundDevice();
	return snd_device;
}


SoundDevice::SoundDevice() {
	p_ALCDevice = alcOpenDevice(nullptr); // nullptr = get default device
	if (!p_ALCDevice)
		throw ("Failed to get sound device");

	p_ALCContext = alcCreateContext(p_ALCDevice, nullptr); // Create context
	if (!p_ALCContext)
		throw ("Failed to set sound context");

	if (!alcMakeContextCurrent(p_ALCContext)) // make context current
		throw("Failed to make context current");

	const ALCchar* name = nullptr;
	if (alcIsExtensionPresent(p_ALCDevice, "ALC_ENUMERABLE_ALL_EXT"))
		name = alcGetString(p_ALCDevice, ALC_ALL_DEVICES_SPECIFIER);
	if (!name || alcGetError(p_ALCDevice) != ALC_NO_ERROR)
		name = alcGetString(p_ALCDevice, ALC_DEVICE_SPECIFIER);
	std::cout << "Opened " << name << std::endl;
}