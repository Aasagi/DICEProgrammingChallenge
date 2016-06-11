#ifndef _MOUSE_INPUT_MESSAGE_H_
#define _MOUSE_INPUT_MESSAGE_H_

#include "NetworkMessage.h"
#include <string>

class MouseInputMessage : public NetworkMessage
{
public:
	inline MouseInputMessage()
	{
		myMessage = eNetworkMessages::eMouseInputMessage;
	}

	inline ~MouseInputMessage()
	{
	}

	char myKeyCode;
	char myDownState; //Up = 0, Down = 1
	float myPositionX;
	float myPositionY;
	std::string myAddress;//We do not send the address with the packet

	inline void WriteToBitStream(RakNet::BitStream& aBitStream)		override;
	inline void ReadFromBitStream(RakNet::BitStream& aBitStream)	override;
};

inline void MouseInputMessage::WriteToBitStream(RakNet::BitStream& aBitStream)
{
	aBitStream.Write(myKeyCode);
	aBitStream.Write(myDownState);
	aBitStream.Write(myPositionX);
	aBitStream.Write(myPositionY);
}

inline void MouseInputMessage::ReadFromBitStream(RakNet::BitStream& aBitStream)
{
	aBitStream.Read(myKeyCode);
	aBitStream.Read(myDownState);
	aBitStream.Read(myPositionX);
	aBitStream.Read(myPositionY);
}

#endif