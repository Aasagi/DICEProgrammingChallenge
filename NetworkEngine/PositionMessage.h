#ifndef _POSITION_MESSAGE_H_
#define _POSITION_MESSAGE_H_

#include "NetworkMessage.h"

class PositionMessage : public NetworkMessage
{
public:
	inline PositionMessage()
	{
		myMessage = eNetworkMessages::ePositionMessage;
	}

	inline ~PositionMessage()
	{
	}

	char myPlayerID;
	float myPositionX;
	float myPositionY;

private:
	inline void WriteToBitStream(RakNet::BitStream& aBitStream)		override;
	inline void ReadFromBitStream(RakNet::BitStream& aBitStream)	override;
};

inline void PositionMessage::WriteToBitStream(RakNet::BitStream& aBitStream)
{
	aBitStream.Write(myPlayerID);
	aBitStream.Write(myPositionX);
	aBitStream.Write(myPositionY);
}

inline void PositionMessage::ReadFromBitStream(RakNet::BitStream& aBitStream)
{
	aBitStream.Read(myPlayerID);
	aBitStream.Read(myPositionX);
	aBitStream.Read(myPositionY);
}

#endif