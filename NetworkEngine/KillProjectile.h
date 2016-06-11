#ifndef _KILL_PROJECTILE_MESSAGE_H_
#define _KILL_PROJECTILE_MESSAGE_H_

#include "NetworkMessage.h"

class KillProjectileMessage : public NetworkMessage
{
public:
	inline KillProjectileMessage()
	{
		myMessage = eNetworkMessages::eKillProjectileMessage;
	}

	inline ~KillProjectileMessage()
	{
	}

	short myID;

private:
	inline void WriteToBitStream(RakNet::BitStream& aBitStream)		override;
	inline void ReadFromBitStream(RakNet::BitStream& aBitStream)	override;

};

inline void KillProjectileMessage::WriteToBitStream(RakNet::BitStream& aBitStream)
{
	aBitStream.Write(myID);
}

inline void KillProjectileMessage::ReadFromBitStream(RakNet::BitStream& aBitStream)
{
	aBitStream.Read(myID);
}

#endif