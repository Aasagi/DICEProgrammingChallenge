#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include "CommonUtilities\Vector2decl.h"

class Settings
{
public:
	friend class Megaton;

	Settings(const CU::Vector2f& aResolution)
	{
		myWindowResolution = aResolution;
	}

	CU::Vector2f myWindowResolution;
};



#endif