#include "stdafx.h"
#include "TriggerManager.h"
#include "TriggerObserver.h"

TriggerManager* TriggerManager::myInstance = nullptr;

TriggerManager::TriggerManager(void)
{
	//myMessages.Init(100);
}

TriggerManager::~TriggerManager(void)
{
}

void TriggerManager::Update()
{
	//This for loop checks every individual message that has been sent to postmaster and compares it with each of the multimap keys
	//the if statement then checks if the key is identical to the multimap observers eMsgType, if it is then that observer will be notified
	//with the object and message from the message.
	std::pair<eTriggerType, void*> message;
	while(myMessages.Size() > 0)
	{
		message = myMessages.Pop();
		for(auto it = myObservers.begin(); it != myObservers.end(); ++it)
		{
			if(it->second != nullptr)
			{
				if(message.first == it->first)
				{
					it->second->Notify(message.first, message.second);
					//delete myMessages[index].second;
				}
			}
		}
		delete message.second;
	}
	//for(unsigned short index = 0; index < myMessages.Count(); ++index)
	//{
	//	for(auto it = myObservers.begin(); it != myObservers.end(); ++it)
	//	{
	//		if(it->second != nullptr)
	//		{
	//			if(myMessages[index].first == it->first)
	//			{
	//				it->second->Notify(myMessages[index].first, myMessages[index].second);
	//				//delete myMessages[index].second;
	//			}
	//		}
	//	}

	//	delete myMessages[index].second;
	//}
	//myMessages.RemoveAll();
}

void TriggerManager::RecieveMsg(eTriggerType aTriggerType, void* aTrigger)
{
	myMessages.Push(std::pair<eTriggerType, void*>(aTriggerType, aTrigger));
	//myMessages.Add(std::pair<eTriggerType, void*>(aTriggerType, aTrigger));
}

void TriggerManager::AddObserver(eTriggerType aTriggerType, TriggerObserver* anObserver)
{
	myObservers.insert(std::pair<eTriggerType, TriggerObserver*>(aTriggerType, anObserver));
}

void TriggerManager::DeleteObserver(eTriggerType aTriggerType, TriggerObserver* anObserver)
{
	for(auto it = myObservers.begin(); it != myObservers.end(); ++it)
	{
		if(it->first == aTriggerType && it->second == anObserver)
		{
			myObservers.erase(it);
			break;
		}
	}
}