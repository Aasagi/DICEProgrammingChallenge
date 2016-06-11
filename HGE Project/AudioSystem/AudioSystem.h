#ifndef AUDIOSYSTEM_AUDIOSYSTEM_H
#define AUDIOSYSTEM_AUDIOSYSTEM_H

#include "../Libraries/fmod/inc/fmod.hpp"
#include "../Libraries/fmod/inc/fmod_errors.h"
#include <string>

enum class eChannelGroup
{
	eMusic,
	eAmbient,
	eVoices,
	eEffects,
	eMaster,
};

class Sound;

class AudioSystem
{
	public:
		friend class Megaton;

		bool Init(short aNumberOfChannels = 32, float aDistanceFactor = 1.f);
		void Shutdown();
		void Update();
		void UpdatePosition(float aX, float aY, float aZ);

		bool LoadSound(const std::string& aFilePath, FMOD::Sound** aSound);
		bool LoadStream(const std::string& aFilePath, FMOD::Sound** aSound);
		void PlaySound(FMOD::Sound* aSound, FMOD::Channel** aChannel, const FMOD_VECTOR& aPosition = FMOD_VECTOR(), eChannelGroup aChannelGroup = eChannelGroup::eEffects);
		void PlaySound(FMOD::Sound* aSound, FMOD::Channel** aChannel, float aX = 0, float aY = 0, float aZ = 0, eChannelGroup aChannelGroup = eChannelGroup::eEffects);
		void PlayStream(FMOD::Sound* aSound, FMOD::Channel** aChannel, eChannelGroup aChannelGroup = eChannelGroup::eMusic);
		void StopSound(FMOD::Channel** aChannel);
		void PauseSound(FMOD::Channel** aChannel);
		void SetLoop(FMOD::Sound* aSound, bool aBool);
		void SetVolume(eChannelGroup aChannelGroup, float aVolume);
		float GetVolume(eChannelGroup aChannelGroup);
		FMOD::ChannelGroup* GetChannelGroup(eChannelGroup aGroup);

	private:
		AudioSystem(void);
		~AudioSystem(void);

		void InitChannels();
		FMOD::ChannelGroup* AssignGroup(eChannelGroup aChannelGroup);
		bool ErrorCheck(FMOD_RESULT aResult);

		FMOD::System* mySystem;
		FMOD::ChannelGroup* myMaster;
		FMOD::ChannelGroup* myMusic;
		FMOD::ChannelGroup* myAmbient;
		FMOD::ChannelGroup* myVoices;
		FMOD::ChannelGroup* myEffects;
		FMOD_VECTOR myPosition;
		float myDistanceFactor;
};

#endif