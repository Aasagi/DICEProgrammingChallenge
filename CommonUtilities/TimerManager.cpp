#include "TimerManager.h"
#include <assert.h>
#include <string>

using namespace CommonUtilities;

TimerManager::TimerManager(void)
{
	myNumberOfTimers = 0;
	myMasterTimer.Start();
}

TimerManager::~TimerManager(void) { }

TimerHandle TimerManager::AddTimer()
{
	Timer timer;
	myTimers[myNumberOfTimers] = timer;
	++myNumberOfTimers;
	return myNumberOfTimers-1;
}
void TimerManager::StartTimer(TimerHandle aIndex)
{
	myTimers.at(aIndex).Start();
}
void TimerManager::PauseTimer(TimerHandle aIndex)
{
	myTimers.at(aIndex).Pause();
}
void TimerManager::ResumeTimer(TimerHandle aIndex)
{
	myTimers.at(aIndex).Resume();
}
void TimerManager::ResetTimer(TimerHandle aIndex)
{
	myTimers.at(aIndex).Resume();
	myTimers.at(aIndex).SetFrequency(0);
	myTimers.at(aIndex).SetStart(0);
	myTimers.at(aIndex).SetCurrent(0);
	myTimers.at(aIndex).SetTotalPause(0);
}
void TimerManager::RestartTimer(TimerHandle aIndex)
{
	std::string error("ERROR: RestartTimer: Timer with handle " + std::to_string(aIndex) + " was not found.");
	assert(myTimers.find(aIndex) != myTimers.end() && error.c_str());
	
	ResetTimer(aIndex);
	StartTimer(aIndex);
}
void TimerManager::Update()
{
	myMasterTimer.UpdateCurrent();
	for (std::map<TimerHandle, Timer>::iterator it = myTimers.begin(); it != myTimers.end(); ++it)
	{
		it->second.UpdateCurrent();
	}
}

unsigned int TimerManager::GetNumberOfTimers()
{
	return myTimers.size();
}
Timer& TimerManager::GetTimer(TimerHandle aIndex)
{
	std::string error("ERROR: GetTimer: Timer with handle " + std::to_string(aIndex) + " was not found.");
	assert(myTimers.find(aIndex) != myTimers.end() && error.c_str());

	return myTimers[aIndex];
}
Timer TimerManager::GetMasterTime()
{
	return myMasterTimer;
}
double TimerManager::GetFPS()
{
	return myMasterTimer.GetFramesPerSecond();
}
Time TimerManager::GetFrameTime()
{
	return myMasterTimer.GetFrameTime();
}