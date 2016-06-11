#ifndef _GAME_OBJECT_POSITION_MESSAGE_H_
#define _GAME_OBJECT_POSITION_MESSAGE_H_

#include "NetworkMessage.h"

class GameObjectPositionMessage : public NetworkMessage
{
	friend class NetworkEngine;
public:
	GameObjectPositionMessage()
	{
		myMessage = eGameObjectPositionMessage;
	}

	~GameObjectPositionMessage()
	{
	}

	short myGameObjectID;
	float myPositionX;
	float myPositionY;

private:
	inline void WriteToBitStream(RakNet::BitStream& aBitStream)		override;
	inline void ReadFromBitStream(RakNet::BitStream& aBitStream)	override;
};

inline void GameObjectPositionMessage::WriteToBitStream(RakNet::BitStream& aBitStream)
{
	aBitStream.Write(myGameObjectID);
	aBitStream.Write(myPositionX);
	aBitStream.Write(myPositionY);
}

inline void GameObjectPositionMessage::ReadFromBitStream(RakNet::BitStream& aBitStream)
{
	aBitStream.Read(myGameObjectID);
	aBitStream.Read(myPositionX);
	aBitStream.Read(myPositionY);
}

#endif