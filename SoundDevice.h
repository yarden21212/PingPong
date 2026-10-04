#pragma once

#include <iostream>
#include <AL\alc.h>

class SoundDevice {
private:
	//std::string path;

public:
	static SoundDevice* get();
	
private:
	SoundDevice();
	~SoundDevice();

	ALCdevice* p_ALCDevice;
	ALCcontext* p_ALCContext;

};