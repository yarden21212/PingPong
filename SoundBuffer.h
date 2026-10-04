#pragma once

#include <AL\al.h>
#include <vector>

class SoundBuffer
{
public:
	static SoundBuffer* get();

	ALuint addSoundEffect(const char* filename);
	bool removeSoundEffect(const ALuint& buffer);
private:
	SoundBuffer();
	~SoundBuffer();
	std::vector<ALuint> p_SoundEffectBuffers; // Anytime we will add/remove a sound effect, we will add/remove it from here
};

