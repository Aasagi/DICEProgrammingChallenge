#ifndef AUDIOSYSTEM_SOUND_H
#define AUDIOSYSTEM_SOUND_H

#include "SoundBase.h"

class Sound : public SoundBase
{
public:
	Sound(void);
	~Sound(void); 

	bool Load(const std::string aFilePath, eChannelGroup aChannelGroup, bool aIs3D = true);
	void SetSound(FMOD::Sound* aSound, eChannelGroup aChannelGroup, bool aIs3D = true);
	void Play();
	void SetPosition(const FMOD_VECTOR& aVector);
	void SetPosition(float aX, float aY, float aZ);
	void SetMinMaxDistance(float aMin, float aMax);
	bool Get3D();
	void Set3D(bool aIs3D);
	void SetPitch(float aPitch);
private:
	bool myIs3D;
	FMOD_VECTOR myPosition;
};

#endif