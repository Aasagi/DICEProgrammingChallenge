#include "Timer.h"

using namespace CommonUtilities;

Timer::Timer(void)
{	
	myIsPaused = false;
	myFrequency.QuadPart = 0;
	myStart.QuadPart = 0;
	myCurrent.QuadPart = 0;
	myPauseStart.QuadPart = 0;
	myLastFrame.QuadPart = 0;
	myTotalPause.QuadPart = 0;
}

Timer::~Timer(void)
{
}

void Timer::UpdateFrequency()
{
	QueryPerformanceFrequency(&myFrequency);
}
void Timer::UpdateStart()
{
	QueryPerformanceCounter(&myStart);
}
void Timer::UpdateCurrent()
{
	myLastFrame.QuadPart = myCurrent.QuadPart;
	QueryPerformanceCounter(&myCurrent);
}
void Timer::SetFrequency(int aInt)
{
	myFrequency.QuadPart = aInt;
}
void Timer::SetStart(int aInt)
{
	myStart.QuadPart = aInt;
}
void Timer::SetCurrent(int aInt)
{
	myCurrent.QuadPart = aInt;
}	
void Timer::SetPauseStart(LARGE_INTEGER aTime)
{
	myPauseStart = aTime;
}
void Timer::SetTotalPause(int aTime)
{
	myTotalPause.QuadPart = aTime;
}
void Timer::SetLastFrame(LARGE_INTEGER aTime)
{
	myLastFrame = aTime;
}

LARGE_INTEGER Timer::GetFrequency()
{
	return myFrequency;
}
LARGE_INTEGER Timer::GetStart()
{
	return myStart;
}
LARGE_INTEGER Timer::GetCurrent()
{
	return myCurrent;
}
LARGE_INTEGER Timer::GetPauseStart()
{
	return myPauseStart;
}
LARGE_INTEGER Timer::GetTotalPause()
{
	if (myIsPaused == false)
	{
		return myTotalPause;
	}
	myTotalPause.QuadPart += (myCurrent.QuadPart - myPauseStart.QuadPart);
	myPauseStart.QuadPart = myCurrent.QuadPart;

	return myTotalPause;
}


void Timer::Start()
{
	UpdateFrequency();
	UpdateStart();
	UpdateCurrent();
}
void Timer::Pause()
{
	myIsPaused = true;
	myPauseStart.QuadPart = myCurrent.QuadPart;
}
void Timer::Resume()
{
	if (myIsPaused == true)
	{
		myTotalPause.QuadPart += (myCurrent.QuadPart - myPauseStart.QuadPart);
		myIsPaused = false;
	}
}
Time Timer::GetTotalTime()
{
	return Time((myCurrent.QuadPart - myStart.QuadPart) / static_cast<double>(myFrequency.QuadPart));
}
Time Timer::GetTime()
{
	return Time((myCurrent.QuadPart - myStart.QuadPart - GetTotalPause().QuadPart) / static_cast<double>(myFrequency.QuadPart));
}
Time Timer::GetTotalPauseTime()
{
	return Time(GetTotalPause().QuadPart / static_cast<double>(myFrequency.QuadPart));
}
Time Timer::GetFrameTime()
{
	return Time((myCurrent.QuadPart - myLastFrame.QuadPart) / static_cast<double>(myFrequency.QuadPart));
}
double Timer::GetFramesPerSecond()
{
	return static_cast<double>(myFrequency.QuadPart) / (myCurrent.QuadPart - myLastFrame.QuadPart);
}