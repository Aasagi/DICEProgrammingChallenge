#ifndef _PROJECTILE_MESSAGE_H_
#define _PROJECTILE_MESSAGE_H_

#include "NetworkMessage.h"

class ProjectileMessage : public NetworkMessage
{
public:
	inline ProjectileMessage()
	{
		myMessage = eNetworkMessages::eProjectileMessage;
	}

	inline ~ProjectileMessage()
	{
	}

	short myID;
	float myPositionX;
	float myPositionY;
	bool myIsAlive;

private:
	inline void WriteToBitStream(RakNet::BitStream& aBitStream)		override;
	inline void ReadFromBitStream(RakNet::BitStream& aBitStream)	override;

};

inline void ProjectileMessage::WriteToBitStream(RakNet::BitStream& aBitStream)
{
	aBitStream.Write(myID);
	aBitStream.Write(myPositionX);
	aBitStream.Write(myPositionY);
	aBitStream.Write(myIsAlive);
}

inline void ProjectileMessage::ReadFromBitStream(RakNet::BitStream& aBitStream)
{
	aBitStream.Read(myID);
	aBitStream.Read(myPositionX);
	aBitStream.Read(myPositionY);
	aBitStream.Read(myIsAlive);
}

#endif