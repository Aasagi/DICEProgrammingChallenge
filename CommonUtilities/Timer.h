#ifndef timer_h
#define timer_h

#include <Windows.h>
#include "Time.h"

namespace CommonUtilities
{
	class Timer
	{
	public:
		Timer(void);
		~Timer(void);

		void UpdateFrequency();
		void UpdateStart();
		void UpdateCurrent();
		void SetFrequency(int);
		void SetStart(int);
		void SetCurrent(int);
		void SetPauseStart(LARGE_INTEGER);
		void SetTotalPause(int);
		void SetLastFrame(LARGE_INTEGER);

		LARGE_INTEGER GetFrequency();
		LARGE_INTEGER GetStart();
		LARGE_INTEGER GetCurrent();
		LARGE_INTEGER GetPauseStart();
		LARGE_INTEGER GetTotalPause();
		Time GetTotalTime();
		Time GetTime();
		Time GetTotalPauseTime();
		Time GetFrameTime();
		double GetFramesPerSecond();

		void Start();
		void Pause();
		void Resume();
	private:
		bool myIsPaused;
		LARGE_INTEGER myFrequency;
		LARGE_INTEGER myStart;
		LARGE_INTEGER myCurrent;
		LARGE_INTEGER myPauseStart;
		LARGE_INTEGER myTotalPause;
		LARGE_INTEGER myLastFrame;
	};
}

#endif