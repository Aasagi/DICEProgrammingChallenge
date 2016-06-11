#include "stdafx.h"
#include "Sound.h"

Sound::Sound(void)
{
	mySound = nullptr;
	myChannel = nullptr;
	myVolume = 1.0f;
}


Sound::~Sound(void)
{
}


bool Sound::Load(const std::string aFilePath, eChannelGroup aChannelGroup, bool aIs3D)
{
	myChannelGroup = aChannelGroup;
	myIs3D = aIs3D;
	if (!myAudioSystem->LoadSound(aFilePath, &mySound)) 
	{
		return false;
	}
	return true;
}
void Sound::SetSound(FMOD::Sound* aSound, eChannelGroup aChannelGroup, bool aIs3D)
{
	myChannelGroup = aChannelGroup;
	mySound = aSound;
	myIs3D = aIs3D;
}
void Sound::Play()
{
	if (mySound != nullptr)
	{
		myAudioSystem->PlaySound(mySound, &myChannel, myPosition, myChannelGroup);
		if (myIs3D == false)
		{
			myChannel->set3DLevel(0);
		}
		myChannel->setVolume(myVolume);
	}
}
void Sound::SetPosition(const FMOD_VECTOR& aVector)
{
	myPosition = aVector;
}
void Sound::SetPosition(float aX, float aY, float aZ)
{
	FMOD_VECTOR vector;
	vector.x = aX;
	vector.y = aY;
	vector.z = aZ;
	SetPosition(vector);
}
void Sound::SetMinMaxDistance(float aMin, float aMax)
{
	if (mySound != nullptr)
	{
		mySound->set3DMinMaxDistance(aMin, aMax);
	}
}
bool Sound::Get3D()
{
	return myIs3D;
}
void Sound::Set3D(bool aIs3D)
{
	myIs3D = aIs3D;
}

//DEFAULT = 1.0
void Sound::SetPitch(float aPitch)
{
	if (myChannel != nullptr)
	{
		myChannel->setPitch(aPitch);
	}
}