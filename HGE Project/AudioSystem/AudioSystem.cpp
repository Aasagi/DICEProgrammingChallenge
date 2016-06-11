#include "AudioSystem.h"
#include "Sound.h"
#include "CommonUtilities/DL_Assert.h"


AudioSystem::AudioSystem(void)
{
	mySystem = nullptr;
}
AudioSystem::~AudioSystem(void) { }

bool AudioSystem::Init(short aNumberOfChannels, float aDistanceFactor)
{
	myDistanceFactor = aDistanceFactor; // Units per meter. I.e centimeters would = 100.
	FMOD_RESULT result = FMOD::System_Create(&mySystem);
	if (!ErrorCheck(result)) return false;

	unsigned int version = 0;
	result = mySystem->getVersion(&version);
	if (!ErrorCheck(result)) return false;
	if (version < FMOD_VERSION)
	{
		DL_DEBUG("%s", "You are using and older version of FMOD, please update");
		bool versionTooOld = true;
		assert(versionTooOld == false && "FMOD version too old!");
	}

	int numdrivers = 0;
	result = mySystem->getNumDrivers(&numdrivers);
	if (!ErrorCheck(result)) return false;
	if (numdrivers == 0)
	{
		result = mySystem->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
		if (!ErrorCheck(result)) return false;
	}

	result = mySystem->init(aNumberOfChannels, FMOD_INIT_NORMAL, 0);
	if (!ErrorCheck(result)) return false;
	result = mySystem->set3DSettings(1.0f, myDistanceFactor, 1.0f);
	if (!ErrorCheck(result)) return false;

	SoundBase::Init(this);
	InitChannels();

	myMaster->setVolume(1);
	myMusic->setVolume(1);
	myEffects->setVolume(1);

	return true;
}
void AudioSystem::InitChannels()
{
	FMOD_RESULT result;

	result = mySystem->createChannelGroup("Master", &myMaster);
	if (!ErrorCheck(result)) return;
	result = mySystem->createChannelGroup("Ambient", &myAmbient);
	if (!ErrorCheck(result)) return;
	result = mySystem->createChannelGroup("Music", &myMusic);
	if (!ErrorCheck(result)) return;
	result = mySystem->createChannelGroup("Voices", &myVoices);
	if (!ErrorCheck(result)) return;
	result = mySystem->createChannelGroup("Effects", &myEffects);
	if (!ErrorCheck(result)) return;

	result = myMaster->addGroup(myAmbient);
	if (!ErrorCheck(result)) return;
	result = myMaster->addGroup(myMusic);
	if (!ErrorCheck(result)) return;
	result = myMaster->addGroup(myVoices);
	if (!ErrorCheck(result)) return;
	result = myMaster->addGroup(myEffects);
	if (!ErrorCheck(result)) return;
}
void AudioSystem::Shutdown()
{
	if (mySystem != nullptr)
	{
		FMOD_RESULT result;
		result = mySystem->close();
		ErrorCheck(result);
		result = mySystem->release();
		ErrorCheck(result);
	}
}
void AudioSystem::Update()
{
	mySystem->update();
}
void AudioSystem::UpdatePosition(float aX, float aY, float aZ)
{	
	myPosition.x = aX;
	myPosition.y = aY;
	myPosition.z = aZ;
	FMOD_RESULT result = mySystem->set3DListenerAttributes(0, &myPosition, 0, 0, 0);
	ErrorCheck(result);
}

bool AudioSystem::LoadSound(const std::string& aFilePath, FMOD::Sound** aSound)
{
	FMOD_RESULT result = mySystem->createSound(aFilePath.c_str(), FMOD_3D, 0, &*aSound);
	if (!ErrorCheck(result)) return false;
	result = (*aSound)->set3DMinMaxDistance(600, 10000);
	if (!ErrorCheck(result)) return false;
	result = (*aSound)->setMode(FMOD_LOOP_OFF);
	if (!ErrorCheck(result)) return false;

	return true;
}
bool AudioSystem::LoadStream(const std::string& aFilePath, FMOD::Sound** aSound)
{
	FMOD_RESULT result = mySystem->createStream(aFilePath.c_str(), FMOD_HARDWARE | FMOD_2D, 0, &*aSound);
	if (!ErrorCheck(result)) return false;
	return true;
}
void AudioSystem::PlaySound(FMOD::Sound* aSound, FMOD::Channel** aChannel, const FMOD_VECTOR& aPosition, eChannelGroup aChannelGroup)
{
	FMOD_RESULT result = mySystem->playSound(aSound, AssignGroup(aChannelGroup), true, &*aChannel);
	ErrorCheck(result);
	result = (*aChannel)->set3DAttributes(&aPosition, 0);
	ErrorCheck(result);
	result = (*aChannel)->setPaused(false);
	ErrorCheck(result);
}
void AudioSystem::PlaySound(FMOD::Sound* aSound, FMOD::Channel** aChannel, float aX, float aY, float aZ, eChannelGroup aChannelGroup)
{
	FMOD_VECTOR vector;
	vector.x = aX;
	vector.y = aY;
	vector.z = aZ;

	PlaySound(aSound, aChannel, vector, aChannelGroup);
}
void AudioSystem::PlayStream(FMOD::Sound* aSound, FMOD::Channel** aChannel, eChannelGroup aChannelGroup)
{
	FMOD_RESULT result = mySystem->playSound(aSound, AssignGroup(aChannelGroup), false, &*aChannel);
	(*aChannel)->setPriority(0);
	ErrorCheck(result);
}
void AudioSystem::StopSound(FMOD::Channel** aChannel)
{
	(*aChannel)->stop();
}
void AudioSystem::PauseSound(FMOD::Channel** aChannel)
{
	bool pause = false;
	(*aChannel)->getPaused(&pause);
	(*aChannel)->setPaused(!pause);
}
void AudioSystem::SetLoop(FMOD::Sound* aSound, bool aBool)
{
	int loop = 0;
	if (aBool == true){
		loop = FMOD_LOOP_NORMAL;
	}
	else {
		loop = FMOD_LOOP_OFF;
	}
	aSound->setMode(loop);
}

FMOD::ChannelGroup* AudioSystem::AssignGroup(eChannelGroup aChannelGroup)
{
	switch (aChannelGroup)
	{
	case eChannelGroup::eMusic:
		return myMusic;
		break;
	case eChannelGroup::eAmbient:
		return myAmbient;
		break;
	case eChannelGroup::eVoices:
		return myVoices;
		break;
	case eChannelGroup::eEffects:
		return myEffects;
		break;
	default:
		return nullptr;
		break;
	}
}
bool AudioSystem::ErrorCheck(FMOD_RESULT aResult)
{
	if (aResult != FMOD_OK)
	{
		DL_DEBUG("%s", FMOD_ErrorString(aResult));
		bool failedToLoad = true;
		assert(failedToLoad == false && "FMOD failed too load!");
	}
	return true;
}
void AudioSystem::SetVolume(eChannelGroup aChannelGroup, float aVolume)
{
	switch (aChannelGroup)
	{
	case eChannelGroup::eMaster:
		myMaster->setVolume(aVolume);
		break;
	case eChannelGroup::eMusic:
		myMusic->setVolume(aVolume);
		break;
	case eChannelGroup::eAmbient:
		myAmbient->setVolume(aVolume);
		break;
	case eChannelGroup::eVoices:
		myVoices->setVolume(aVolume);
		break;
	case eChannelGroup::eEffects:
		myEffects->setVolume(aVolume);
		break;
	default:
		break;
	}
}
float AudioSystem::GetVolume(eChannelGroup aChannelGroup)
{
	float volume = -1.f;
	switch (aChannelGroup)
	{
	case eChannelGroup::eMaster:
		myMaster->getVolume(&volume);
		break;
	case eChannelGroup::eMusic:
		myMusic->getVolume(&volume);
		break;
	case eChannelGroup::eAmbient:
		myAmbient->getVolume(&volume);
		break;
	case eChannelGroup::eVoices:
		myVoices->getVolume(&volume);
		break;
	case eChannelGroup::eEffects:
		myEffects->getVolume(&volume);
		break;
	default:
		break;
	}
	return volume;
}
FMOD::ChannelGroup* AudioSystem::GetChannelGroup(eChannelGroup aGroup)
{
	switch (aGroup)
	{
	case eChannelGroup::eMusic:
		return myMusic;
		break;
	case eChannelGroup::eAmbient:
		return myAmbient;
		break;
	case eChannelGroup::eVoices:
		return myVoices;
		break;
	case eChannelGroup::eEffects:
		return myEffects;
		break;
	case eChannelGroup::eMaster:
		return myMaster;
		break;
	default:
		return nullptr;
		break;
	}
}