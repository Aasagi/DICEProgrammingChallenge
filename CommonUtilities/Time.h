#ifndef time_h
#define time_h

namespace CommonUtilities
{
	class Time
	{
	public:
		Time(double);
		Time();
		~Time(void);

		double AsMicroseconds();
		double AsMilliseconds();
		float AsSeconds();
		double AsMinutes();
		double AsHours();

	private:
		double myTime;
	};
}

inline CommonUtilities::Time::Time(double aTime)
{
	myTime = aTime;
}
inline CommonUtilities::Time::Time()
{
}

inline CommonUtilities::Time::~Time()
{
}

inline double CommonUtilities::Time::AsMicroseconds()
{
	return myTime * 1000000.0;
}
inline double CommonUtilities::Time::AsMilliseconds()
{
	return myTime * 1000.0;
}
inline float CommonUtilities::Time::AsSeconds()
{
	return static_cast<float>(myTime);
}
inline double CommonUtilities::Time::AsMinutes()
{
	return myTime / 60.0;
}
inline double CommonUtilities::Time::AsHours()
{
	return myTime / 3600.0;
}
#endif