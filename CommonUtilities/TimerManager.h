#ifndef timermanager_h
#define timermanager_h

#include "Timer.h"
#include <map>

typedef unsigned int TimerHandle;

namespace CommonUtilities
{
	class TimerManager
	{
		friend class Megaton;
	public:
		TimerManager(void);
		~TimerManager(void);

		TimerHandle AddTimer();
		void StartTimer(TimerHandle);
		void PauseTimer(TimerHandle);
		void ResumeTimer(TimerHandle);
		void ResetTimer(TimerHandle);
		void RestartTimer(TimerHandle);
		void Update();

		unsigned int GetNumberOfTimers();
		Timer& GetTimer(TimerHandle);
		Timer GetMasterTime();
		Time GetFrameTime();
		double GetFPS();

	private:
		TimerHandle myNumberOfTimers;
		Timer myMasterTimer;
		std::map<TimerHandle, Timer> myTimers;
	};
}

namespace CU = CommonUtilities;

#endif