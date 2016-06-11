#ifndef _INPUT_MESSAGE_H_
#define _INPUT_MESSAGE_H_

#include "NetworkMessage.h"

class InputMessage : public NetworkMessage
{
public:
	inline InputMessage()
	{
		myMessage = eNetworkMessages::eInputMessage;
	}

	inline ~InputMessage()
	{
	}

	char myKeyCode;
	char myDownState; //Up = 0, Down = 1
	std::string myAddress;//We do not send the address with the packet

	inline void WriteToBitStream(RakNet::BitStream& aBitStream)		override;
	inline void ReadFromBitStream(RakNet::BitStream& aBitStream)	override;
};

inline void InputMessage::WriteToBitStream(RakNet::BitStream& aBitStream)
{
	aBitStream.Write(myKeyCode);
	aBitStream.Write(myDownState);
}

inline void InputMessage::ReadFromBitStream(RakNet::BitStream& aBitStream)
{
	aBitStream.Read(myKeyCode);
	aBitStream.Read(myDownState);
}

#endif