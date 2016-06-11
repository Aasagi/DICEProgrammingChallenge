#ifndef AUDIOSYSTEM_SOUNDBASE_H
#define AUDIOSYSTEM_SOUNDBASE_H

#include "AudioSystem.h"
#include <string>


class SoundBase
{
public:
	SoundBase(void);
	virtual ~SoundBase(void);
	virtual void Play() = 0;
	void SetSound(FMOD::Sound* aSound, eChannelGroup aChannelGroup);
	void Pause();
	void Stop();
	void SetLoop(bool aBool);
	void SetVolume(float aVolume);
	bool IsPlaying();
	static void Init(AudioSystem* aAudioSystem);

protected:
	eChannelGroup myChannelGroup;
	static AudioSystem* myAudioSystem;
	FMOD::Sound* mySound;
	FMOD::Channel* myChannel;
	float myVolume;
};

#endif