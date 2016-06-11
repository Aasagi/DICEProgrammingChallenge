#ifndef _POST_MASTER_H_
#define _POST_MASTER_H_

#include <map>
#include "CommonUtilities/Stack.h"
#include "Trigger.h"

class TriggerObserver;
class TriggerManager
{
public:
	friend class Megaton;

	void					Update();

	void					RecieveMsg(eTriggerType aTriggerType, void* aTrigger);
	void					AddObserver(eTriggerType aTriggerType, TriggerObserver* anObserver);

	void					DeleteObserver(eTriggerType aTriggerType, TriggerObserver* anObserver);

private:
	TriggerManager(void);
	~TriggerManager(void);

	static TriggerManager* myInstance;

	std::multimap<eTriggerType, TriggerObserver*> myObservers;
	//CommonUtilities::GrowingArray<std::pair<eTriggerType, void*>> myMessages;
	CU::Stack<std::pair<eTriggerType, void*>> myMessages;
};



#endif