#ifndef AUDIOSYSTEM_SOUNDSTREAM_H
#define AUDIOSYSTEM_SOUNDSTREAM_H

#include "SoundBase.h"

class Stream : public SoundBase
{
public:
	Stream(void);
	~Stream(void);

	bool Load(const std::string aFilePath, eChannelGroup aChannelGroup);
	void SetSound(FMOD::Sound* aSound, eChannelGroup aChannelGroup);
	void Play();
};

#endif