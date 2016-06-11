#include "stdafx.h"
#include "SoundBase.h"

AudioSystem* SoundBase::myAudioSystem;

SoundBase::SoundBase(void)
{
}


SoundBase::~SoundBase(void)
{
}

//ONLY CALL THIS IN AUDIOSYSTEM::INIT()
void SoundBase::Init(AudioSystem* aAudioSystem)
{
	myAudioSystem = aAudioSystem;
}


void SoundBase::Pause()
{
	if (mySound != nullptr)
	{
		myAudioSystem->PauseSound(&myChannel);
	}
}
void SoundBase::Stop()
{
	if (mySound != nullptr)
	{
		myAudioSystem->StopSound(&myChannel);
	}
}
void SoundBase::SetLoop(bool aBool)
{
	if (mySound != nullptr)
	{
		myAudioSystem->SetLoop(mySound, aBool);
	}
}
void SoundBase::SetVolume(float aVolume)
{
	myVolume = aVolume;
}
bool SoundBase::IsPlaying()
{
	bool playing = false;
	if (myChannel != nullptr)
	{
		myChannel->isPlaying(&playing);
	}
	return playing;
}