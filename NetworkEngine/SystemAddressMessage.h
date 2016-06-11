#ifndef _SYSTEM_ADDRESS_MESSAGE_H_
#define _SYSTEM_ADDRESS_MESSAGE_H_

#include "NetworkMessage.h"

class SystemAddressMessage : public NetworkMessage
{
public:
	inline SystemAddressMessage()
	{
		myMessage = eNetworkMessages::eCreatePlayerMessage;
	}
	
	inline ~SystemAddressMessage()
	{
	}

	std::string myAdress;

private:
	inline void WriteToBitStream(RakNet::BitStream& aBitStream)		override;
	inline void ReadFromBitStream(RakNet::BitStream& aBitStream)	override;

};

inline void SystemAddressMessage::WriteToBitStream(RakNet::BitStream& aBitStream)
{
}

inline void SystemAddressMessage::ReadFromBitStream(RakNet::BitStream& aBitStream)
{
}

#endif