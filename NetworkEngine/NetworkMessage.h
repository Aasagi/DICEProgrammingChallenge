#ifndef _INTERFACE_NETWORK_MESSAGE_H_
#define _INTERFACE_NETWORK_MESSAGE_H_

#include "RakNet\MessageIdentifiers.h"
#include "CommonUtilities\Vector3decl.h"
#include "RakNet\RakNetTypes.h"  // MessageID
#include "RakNet\BitStream.h"


enum eNetworkMessages
{
	eNO_MESSAGE = ID_USER_PACKET_ENUM,
	eInputMessage,
	ePositionMessage,
	eGameObjectPositionMessage,
	eCreatePlayerMessage,
	eProjectileMessage,
	eMouseInputMessage,
	eKillProjectileMessage,
	eNR_OF_MESSAGES
};

class NetworkMessage
{
public:
	friend class NetworkEngine;

	inline NetworkMessage();
	inline ~NetworkMessage();

	inline void ReadTimeStamp(RakNet::BitStream& aBitStream);

	inline void SetTime(const RakNet::Time& aTime);

	inline eNetworkMessages GetType();
	inline RakNet::Time GetTime();

	eNetworkMessages myMessage;
	RakNet::Time myTimeStamp;

private:
	inline virtual void WriteToBitStream(RakNet::BitStream& aBitStream) = 0;
	inline virtual void ReadFromBitStream(RakNet::BitStream& aBitStream) = 0;
};

inline void NetworkMessage::ReadTimeStamp(RakNet::BitStream& aBitStream)
{
	aBitStream.Read(myTimeStamp);
}

inline void NetworkMessage::SetTime(const RakNet::Time& aTime)
{
	myTimeStamp = aTime;
}

inline NetworkMessage::NetworkMessage()
{
}

inline NetworkMessage::~NetworkMessage()
{
}

inline eNetworkMessages NetworkMessage::GetType()
{
	return myMessage;
}

inline RakNet::Time NetworkMessage::GetTime()
{
	return myTimeStamp;
}

#endif