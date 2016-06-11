#ifndef _TRIGGER_OBSERVER_H
#define _TRIGGER_OBSERVER_H

#include "Trigger.h"

class TriggerObserver
{
public:
	TriggerObserver(void){};
	virtual ~TriggerObserver(void){};
	virtual void Notify(const eTriggerType& aTriggerType, void* aTrigger)=0;
};

#endif