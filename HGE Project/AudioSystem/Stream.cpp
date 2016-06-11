#include "stdafx.h"
#include "Stream.h"


Stream::Stream(void)
{
	mySound = nullptr;
	myChannel = nullptr;
	myVolume = 1.0f;
}


Stream::~Stream(void)
{
	if (mySound != nullptr)
	{
		mySound->release();
	}
}

bool Stream::Load(const std::string aFilePath, eChannelGroup aChannelGroup)
{
	myChannelGroup = aChannelGroup;
	if (!myAudioSystem->LoadStream(aFilePath, &mySound)) 
	{
		return false;
	}
	return true;
}
void Stream::SetSound(FMOD::Sound* aSound, eChannelGroup aChannelGroup)
{
	myChannelGroup = aChannelGroup;
	mySound = aSound;
}
void Stream::Play()
{
	if (mySound != nullptr)
	{
		myAudioSystem->PlayStream(mySound, &myChannel, myChannelGroup);
		myChannel->setVolume(myVolume);
	}
}