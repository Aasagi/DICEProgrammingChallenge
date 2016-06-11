#ifndef _NETWORK_ENGINE_H_
#define _NETWORK_ENGINE_H_

#include "CommonUtilities\GrowingArray.h"
#include "CommonUtilities\MemoryBucket.h"
#include "CommonUtilities\MemoryContainer.h"

#include "NetworkMessage.h"
#include "NetworkHost.h"

#include <functional>
#include <map>
#include <atomic>

namespace RakNet
{
	struct Packet;
	class RakPeerInterface;
};

class NetworkEngine
{
public:
	NetworkEngine();
	~NetworkEngine();

	static bool Create();
	static inline NetworkEngine* GetInstance();

	bool InitClient(const std::string& aIP);
	bool InitHost();

	void Update();
	void ThreadedUpdate(std::atomic_bool& aGameIsOverFlag);
	
	void AddServerMessage(NetworkMessage* aMessage);
	void AddClientMessage(NetworkMessage* aMessage);

	inline RakNet::RakPeerInterface* GetServerPeer();
	inline RakNet::RakPeerInterface* GetClientPeer();
	inline RakNet::Packet* GetServerPacket();
	inline RakNet::Packet* GetClientPacket();

	//inline CU::MemoryBucket& GetServerMemoryBucket();
	//inline CU::MemoryBucket& GetClientMemoryBucket();
	//inline CU::MemoryContainer<NetworkMessage, 262144>& GetServerMemoryContainer();
	//inline CU::MemoryContainer<NetworkMessage, 262144>& GetClientMemoryContainer();
	inline CU::GrowingArray<NetworkMessage*, UINT>& GetServerMessages();
	inline CU::GrowingArray<NetworkMessage*, UINT>& GetClientMessages();

	inline bool IsHost();

	inline short GetFPS();

private:
	void SendMessageToClients(NetworkMessage* aMessage, RakNet::SystemAddress& aSourceAddress);
	void BroadcastMessage(NetworkMessage* aMessage);
	void LoadLagFromXML();
	bool Init();

	void SwapMessageQueue();

	CU::GrowingArray<NetworkMessage*, UINT> myServerFirstMessageQueue;
	CU::GrowingArray<NetworkMessage*, UINT> myServerSecondMessageQueue;
	CU::GrowingArray<NetworkMessage*, UINT>* myServerMessagesToFill;
	CU::GrowingArray<NetworkMessage*, UINT>* myServerActiveMessages;

	CU::GrowingArray<NetworkMessage*, UINT> myClientFirstMessageQueue;
	CU::GrowingArray<NetworkMessage*, UINT> myClientSecondMessageQueue;
	CU::GrowingArray<NetworkMessage*, UINT>* myClientMessagesToFill;
	CU::GrowingArray<NetworkMessage*, UINT>* myClientActiveMessages;

	std::map<unsigned char, std::function<void(bool)>>  myLookupTable;

	//CU::MemoryBucket myServerFirstMessageBucket;
	//CU::MemoryBucket myServerSecondMessageBucket;
	//CU::MemoryBucket* myServerMessageBucketToUse;
	//CU::MemoryBucket* myServerActiveMessageBucket;
	//
	//CU::MemoryBucket myClientFirstMessageBucket;
	//CU::MemoryBucket myClientSecondMessageBucket;
	//CU::MemoryBucket* myClientMessageBucketToUse;
	//CU::MemoryBucket* myClientActiveMessageBucket;

	//CU::MemoryContainer<NetworkMessage, 262144>  myServerFirstMemoryContainer;
	//CU::MemoryContainer<NetworkMessage, 262144>  myServerSecondMemoryContainer;
	//CU::MemoryContainer<NetworkMessage, 262144>* myServerMemoryContainerToUse;
	//CU::MemoryContainer<NetworkMessage, 262144>* myServerActiveMemoryContainer;
	//
	//CU::MemoryContainer<NetworkMessage, 262144>  myClientFirstMemoryContainer;
	//CU::MemoryContainer<NetworkMessage, 262144>  myClientSecondMemoryContainer;
	//CU::MemoryContainer<NetworkMessage, 262144>* myClientMemoryContainerToUse;
	//CU::MemoryContainer<NetworkMessage, 262144>* myClientActiveMemoryContainer;

	CU::GrowingArray<NetworkMessage*, UINT> myServerQueueToSend;
	CU::GrowingArray<NetworkMessage*, UINT> myClientQueueToSend;

	RakNet::RakPeerInterface* myServerPeer;
	RakNet::RakPeerInterface* myClientPeer;
	RakNet::Packet* myServerPacket;
	RakNet::Packet* myClientPacket;

	NetworkHost myHost;

	std::atomic_bool myUpdateIsDone;
	std::atomic_bool myServerUpdateIsDone;
	std::atomic_bool myClientUpdateIsDone;

	std::atomic_bool myServerHasReceivedMesssages;
	std::atomic_bool myClientHasReceivedMesssages;

	float myLatency;
	float myJitterMin;
	float myJitterMax;
	short myServerFPS;

	static NetworkEngine* myInstance;
};

inline RakNet::RakPeerInterface* NetworkEngine::GetServerPeer()
{
	return myServerPeer;
}

inline RakNet::RakPeerInterface* NetworkEngine::GetClientPeer()
{
	return myClientPeer;
}

inline RakNet::Packet* NetworkEngine::GetServerPacket()
{
	return myServerPacket;
}

inline RakNet::Packet* NetworkEngine::GetClientPacket()
{
	return myClientPacket;
}

inline NetworkEngine* NetworkEngine::GetInstance()
{
	return myInstance;
}

//inline CU::MemoryBucket& NetworkEngine::GetServerMemoryBucket()
//{
//	return *myServerActiveMessageBucket;
//}
//
//inline CU::MemoryBucket& NetworkEngine::GetClientMemoryBucket()
//{
//	return *myClientActiveMessageBucket;
//}

//inline CU::MemoryContainer<NetworkMessage, 262144>& NetworkEngine::GetServerMemoryContainer()
//{
//	return *myServerMemoryContainerToUse;
//}
//
//inline CU::MemoryContainer<NetworkMessage, 262144>& NetworkEngine::GetClientMemoryContainer()
//{
//	return *myClientMemoryContainerToUse;
//}

inline CU::GrowingArray<NetworkMessage*, UINT>& NetworkEngine::GetServerMessages()
{
	myServerHasReceivedMesssages.store(true);
	return *myServerActiveMessages;
}

inline CU::GrowingArray<NetworkMessage*, UINT>& NetworkEngine::GetClientMessages()
{
	myClientHasReceivedMesssages.store(true);
	return *myClientActiveMessages;
}

inline bool NetworkEngine::IsHost()
{
	return myHost.myIsHost;
}

inline short NetworkEngine::GetFPS()
{
	return myServerFPS;
}
#endif