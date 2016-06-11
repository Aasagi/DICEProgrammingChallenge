#include "NetworkEngine.h"

#include "RakNet\BitStream.h"
#include "RakNet\GetTime.h"
#include "RakNet\MessageIdentifiers.h"
#include "RakNet\RakNetTypes.h"  // MessageID
#include "RakNet\RakPeerInterface.h"

#include "InputMessage.h"
#include "PositionMessage.h"
#include "SystemAddressMessage.h"
#include "GameObjectPosition.h"
#include "ProjectileMessage.h"
#include "MouseInputMessage.h"
#include "KillProjectile.h"

#include "CommonUtilities\XMLReader.h"

#include <string>
#include <mutex>


#define MAX_CLIENTS 10
#define SERVER_PORT 60000

NetworkEngine* NetworkEngine::myInstance = nullptr;

bool NetworkEngine::Create()
{
	if(myInstance == nullptr)
	{
		myInstance = new NetworkEngine();
		myInstance->Init();
	}
	return true;
}

NetworkEngine::NetworkEngine()
{
	myServerPeer = nullptr;
	myClientPeer = nullptr;
	myServerPacket = nullptr;
	myClientPacket = nullptr;
	myHost.myIsHost.store(false);
}

NetworkEngine::~NetworkEngine()
{
}

bool NetworkEngine::Init()
{
	myServerQueueToSend.Init(512 * 512);
	myClientQueueToSend.Init(512 * 512);
	myServerFirstMessageQueue.Init(512 * 512);
	myServerSecondMessageQueue.Init(512 * 512);
	myClientFirstMessageQueue.Init(512 * 512);
	myClientSecondMessageQueue.Init(512 * 512);

	myServerMessagesToFill = &myServerFirstMessageQueue;
	myServerActiveMessages = &myServerSecondMessageQueue;
	myClientMessagesToFill = &myClientFirstMessageQueue;
	myClientActiveMessages = &myClientSecondMessageQueue;

	//myServerMemoryContainerToUse = &myServerFirstMemoryContainer;
	//myServerActiveMemoryContainer = &myServerSecondMemoryContainer;
	//myClientMemoryContainerToUse = &myClientFirstMemoryContainer;
	//myClientActiveMemoryContainer = &myClientSecondMemoryContainer;

	std::function<void(bool)> setPosition = [this](bool aIsServer)
	{
		RakNet::Packet* packet = GetClientPacket();
		if(aIsServer == true)
		{
			packet = GetServerPacket();
		}

		RakNet::BitStream bsIn(packet->data, packet->length, false);
		bsIn.IgnoreBytes(sizeof(RakNet::MessageID));

		PositionMessage* pos;
		pos = new PositionMessage();

		NetworkMessage* msg = pos;

		msg->ReadTimeStamp(bsIn);
		msg->ReadFromBitStream(bsIn);

		if(aIsServer == true)
		{
			myServerMessagesToFill->Add(msg);
		}
		else
		{
			myClientMessagesToFill->Add(msg);
		}

		if(myHost.myIsHost.load() == true)
		{
			SendMessageToClients(msg, packet->systemAddress);
		}
	};

	std::function<void(bool)> input = [this](bool aIsServer)
	{
		RakNet::Packet* packet = GetClientPacket();
		if(aIsServer == true)
		{
			packet = GetServerPacket();
		}

		RakNet::BitStream bsIn(packet->data, packet->length, false);
		bsIn.IgnoreBytes(sizeof(RakNet::MessageID));

		InputMessage* inputMsg;
		inputMsg = new InputMessage();


		NetworkMessage* msg = inputMsg;

		msg->ReadTimeStamp(bsIn);
		msg->ReadFromBitStream(bsIn);

		inputMsg->myAddress = packet->systemAddress.ToString();

		if(aIsServer == true)
		{
			myServerMessagesToFill->Add(msg);
		}
		else
		{
			myClientMessagesToFill->Add(msg);
		}
	};

	std::function<void(bool)> setGameObjectPosition = [this](bool aIsServer)
	{
		RakNet::Packet* packet = GetClientPacket();
		if(aIsServer == true)
		{
			packet = GetServerPacket();
		}

		RakNet::BitStream bsIn(packet->data, packet->length, false);
		bsIn.IgnoreBytes(sizeof(RakNet::MessageID));

		GameObjectPositionMessage* pos;
		pos = new GameObjectPositionMessage();


		pos->ReadTimeStamp(bsIn);
		pos->ReadFromBitStream(bsIn);

		if(aIsServer == true)
		{
			myServerMessagesToFill->Add(pos);
		}
		else
		{
			myClientMessagesToFill->Add(pos);
		}

		if(myHost.myIsHost.load() == true)
		{
			SendMessageToClients(pos, packet->systemAddress);
		}
	};

	std::function<void(bool)> projectileMessage = [this](bool aIsServer)
	{
		RakNet::Packet* packet = GetClientPacket();
		if(aIsServer == true)
		{
			packet = GetServerPacket();
		}

		RakNet::BitStream bsIn(packet->data, packet->length, false);
		bsIn.IgnoreBytes(sizeof(RakNet::MessageID));

		ProjectileMessage* pos;
		pos = new ProjectileMessage();

		NetworkMessage* msg = pos;

		msg->ReadTimeStamp(bsIn);
		msg->ReadFromBitStream(bsIn);

		if(aIsServer == true)
		{
			myServerMessagesToFill->Add(msg);
		}
		else
		{
			myClientMessagesToFill->Add(msg);
		}

		if(myHost.myIsHost.load() == true)
		{
			SendMessageToClients(msg, packet->systemAddress);
		}
	};

	std::function<void(bool)> mouseInput = [this](bool aIsServer)
	{
		RakNet::Packet* packet = GetClientPacket();
		if(aIsServer == true)
		{
			packet = GetServerPacket();
		}

		RakNet::BitStream bsIn(packet->data, packet->length, false);
		bsIn.IgnoreBytes(sizeof(RakNet::MessageID));

		MouseInputMessage* inputMsg;
		inputMsg = new MouseInputMessage();

		NetworkMessage* msg = inputMsg;

		msg->ReadTimeStamp(bsIn);
		msg->ReadFromBitStream(bsIn);

		inputMsg->myAddress = packet->systemAddress.ToString();

		if(aIsServer == true)
		{
			myServerMessagesToFill->Add(msg);
		}
		else
		{
			myClientMessagesToFill->Add(msg);
		}
	};

	std::function<void(bool)> killProjectile = [this](bool aIsServer)
	{
		RakNet::Packet* packet = GetClientPacket();
		if(aIsServer == true)
		{
			packet = GetServerPacket();
		}

		RakNet::BitStream bsIn(packet->data, packet->length, false);
		bsIn.IgnoreBytes(sizeof(RakNet::MessageID));

		KillProjectileMessage* inputMsg;
		inputMsg = new KillProjectileMessage();

		NetworkMessage* msg = inputMsg;

		msg->ReadTimeStamp(bsIn);
		msg->ReadFromBitStream(bsIn);

		if(aIsServer == true)
		{
			myServerMessagesToFill->Add(msg);
		}
		else
		{
			myClientMessagesToFill->Add(msg);
		}

		if(myHost.myIsHost.load() == true)
		{
			SendMessageToClients(msg, packet->systemAddress);
		}
	};

	myLookupTable[eNetworkMessages::ePositionMessage] = setPosition;
	myLookupTable[eNetworkMessages::eInputMessage] = input;
	myLookupTable[eNetworkMessages::eGameObjectPositionMessage] = setGameObjectPosition;
	myLookupTable[eNetworkMessages::eProjectileMessage] = projectileMessage;
	myLookupTable[eNetworkMessages::eMouseInputMessage] = mouseInput;
	myLookupTable[eNetworkMessages::eKillProjectileMessage] = killProjectile;

	std::function<void(bool)> incomingConnection = [this](bool aIsServer)
	{
		printf("Connection is incoming\n");

		RakNet::Packet* packet = GetClientPacket();
		if(aIsServer == true)
		{
			packet = GetServerPacket();
		}

		RakNet::BitStream bsIn(packet->data, packet->length, false);
		bsIn.IgnoreBytes(sizeof(RakNet::MessageID));

		SystemAddressMessage* sys;
		sys = new SystemAddressMessage();


		sys->myTimeStamp = RakNet::GetTime();
		sys->myAdress = packet->systemAddress.ToString();

		if(aIsServer == true)
		{
			myServerMessagesToFill->Add(sys);
		}
		else
		{
			myClientMessagesToFill->Add(sys);
		}
	};
	myLookupTable[ID_NEW_INCOMING_CONNECTION] = incomingConnection;

	std::function<void(bool)> remoteDisconnectionNotification = [this](bool aIsServer)
	{
		printf("Remote disconnection\n");
	};
	myLookupTable[ID_REMOTE_DISCONNECTION_NOTIFICATION] = remoteDisconnectionNotification;

	std::function<void(bool)> remoteConnectionLost = [this](bool aIsServer)
	{
		printf("Remote connection lost\n");
	};
	myLookupTable[ID_REMOTE_CONNECTION_LOST] = remoteConnectionLost;

	std::function<void(bool)> remoteNewIncoming = [this](bool aIsServer)
	{
		printf("Remote new incoming\n");
	};
	myLookupTable[ID_REMOTE_NEW_INCOMING_CONNECTION] = remoteNewIncoming;

	std::function<void(bool)> connectionRequestAccept = [this](bool aIsServer)
	{
		printf("Connection request Accept\n");
	};
	myLookupTable[ID_CONNECTION_REQUEST_ACCEPTED] = connectionRequestAccept;

	/*std::function<void(bool)> createPlayer = [this](bool aIsServer)
	{
	RakNet::Packet* packet = GetClientPacket();
	if(GetServerPacket() != nullptr)
	{
	packet = GetServerPacket();
	}

	RakNet::BitStream bsIn(packet->data, packet->length, false);
	bsIn.IgnoreBytes(sizeof(RakNet::MessageID));

	SystemAddressMessage* sys;
	if(aIsServer == true)
	{
	sys = this->GetServerMemoryBucket().GetData<SystemAddressMessage>();
	}
	else
	{
	sys = this->GetClientMemoryBucket().GetData<SystemAddressMessage>();
	}
	sys->ReadTimeStamp(bsIn);
	sys->myAdress = packet->systemAddress;
	if(aIsServer == true)
	{
	myServerMessagesToFill->Add(sys);
	}
	else
	{
	myClientMessagesToFill->Add(sys);
	}
	};
	myLookupTable[eNetworkMessages::eCreatePlayerMessage] = createPlayer;*/

	std::function<void(bool)> nofreeIncomingConnections = [this](bool aIsServer)
	{
		printf("no free Incoming Connections\n");
	};
	myLookupTable[ID_NO_FREE_INCOMING_CONNECTIONS] = nofreeIncomingConnections;

	std::function<void(bool)> disconnection = [this](bool aIsServer)
	{
		printf("disconnection\n");
	};
	myLookupTable[ID_DISCONNECTION_NOTIFICATION] = disconnection;

	std::function<void(bool)> connectionLost = [this](bool aIsServer)
	{
		printf("connection Lost\n");
	};
	myLookupTable[ID_CONNECTION_LOST] = connectionLost;

	myServerPeer = RakNet::RakPeerInterface::GetInstance();
	myClientPeer = RakNet::RakPeerInterface::GetInstance();

	myUpdateIsDone.store(false);
	myServerUpdateIsDone.store(false);
	myClientUpdateIsDone.store(false);
	/*myServerHasReceivedMesssages.store(true);
	myClientHasReceivedMesssages.store(true);*/
	myServerHasReceivedMesssages.store(false);
	myClientHasReceivedMesssages.store(false);

	return true;
}

bool NetworkEngine::InitClient(const std::string& aIP)
{
	RakNet::SocketDescriptor sd;
	myClientPeer->Startup(1, &sd, 1);
	RakNet::ConnectionAttemptResult result = myClientPeer->Connect(aIP.c_str(), SERVER_PORT, 0, 0);
	if(result == RakNet::ConnectionAttemptResult::CONNECTION_ATTEMPT_STARTED)
	{
		RakNet::Packet* packet = nullptr;
		time_t currentTime = time(0);
		while(time(0) - currentTime < 5)
		{
			packet = myClientPeer->Receive();
			if(packet != nullptr)
			{
				break;
			}
		}
		if(packet == nullptr)
		{
			printf("Connection timed out...");
			printf("Press anything to exit...");
			std::cin.get();
			return 0;
		}
		else
		{
			if(packet->data[0] == ID_CONNECTION_REQUEST_ACCEPTED)
			{
				printf("Connection succeeded!\n");
			}
			else
			{
				printf("Denied!");
				printf("Press anything to exit...");
				std::cin.get();
				return 0;
			}
		}
	}
	else
	{
		std::cout << "failed to connect" << std::endl;
	}
	RakNet::SystemAddress serverAddress;
	serverAddress = RakNet::SystemAddress(aIP.c_str(), SERVER_PORT);
	myHost.myHostAddress = serverAddress;
	myHost.myIsHost.store(false);

	RakNet::RakPeerInterface::DestroyInstance(myServerPeer);

	return true;
}

bool NetworkEngine::InitHost()
{
	RakNet::SocketDescriptor sd(SERVER_PORT, 0);
	myServerPeer->Startup(MAX_CLIENTS, &sd, 1);
	myServerPeer->SetMaximumIncomingConnections(MAX_CLIENTS);
	RakNet::SystemAddress serverAddress = RakNet::SystemAddress("127.0.0.1", SERVER_PORT);
	myHost.myHostAddress = serverAddress;
	myHost.myIsHost.store(true);
	RakNet::SocketDescriptor clientSD;
	myClientPeer->Startup(1, &clientSD, 1);
	myClientPeer->Connect("127.0.0.1", SERVER_PORT, 0, 0);

	LoadLagFromXML();

	return true;
}

void NetworkEngine::LoadLagFromXML()
{
	XMLReader reader;

	tinyxml2::XMLElement* root = reader.LoadFile("lag.xml");

	myLatency = root->FirstChildElement("latency")->FloatAttribute("ms");
	myJitterMin = root->FirstChildElement("jitter")->FloatAttribute("min");
	myJitterMax = root->FirstChildElement("jitter")->FloatAttribute("max");
	myServerFPS = root->FirstChildElement("server")->IntAttribute("FPS");

}

void NetworkEngine::Update()
{
	while(myUpdateIsDone.load() == false);

	SwapMessageQueue();
}

void NetworkEngine::ThreadedUpdate(std::atomic_bool& aGameIsOverFlag)
{
	while(aGameIsOverFlag.load() == false)
	{
		while(myUpdateIsDone.load() == true)
		{
			Sleep(1);
		}

		if(myHost.myIsHost.load() == true)
		{
			for(myServerPacket = myServerPeer->Receive(); myServerPacket; myServerPeer->DeallocatePacket(myServerPacket), myServerPacket = myServerPeer->Receive())
			{
				unsigned char id = myServerPacket->data[0];
				if(myLookupTable.count(id) == 1)
				{
					myLookupTable[id](true);
				}
			}
		}

		for(myClientPacket = myClientPeer->Receive(); myClientPacket; myClientPeer->DeallocatePacket(myClientPacket), myClientPacket = myClientPeer->Receive())
		{
			unsigned char id = myClientPacket->data[0];
			if(myLookupTable.count(id) == 1)
			{
				myLookupTable[id](false);
			}
		}

		myUpdateIsDone.store(true);
	}
	if(myHost.myIsHost.load() == true)
	{
		RakNet::RakPeerInterface::DestroyInstance(myServerPeer);
	}
	RakNet::RakPeerInterface::DestroyInstance(myClientPeer);
}

void NetworkEngine::AddServerMessage(NetworkMessage* aMessage)
{
	aMessage->SetTime(RakNet::GetTime());
	myServerQueueToSend.Add(aMessage);
}

void NetworkEngine::AddClientMessage(NetworkMessage* aMessage)
{
	aMessage->SetTime(RakNet::GetTime());
	myClientQueueToSend.Add(aMessage);
}

void NetworkEngine::SendMessageToClients(NetworkMessage* aMessage, RakNet::SystemAddress& aSourceAddress)
{
	unsigned short numberOfSystems = myServerPeer->NumberOfConnections();
	for(unsigned short i = 0; i < numberOfSystems; ++i)
	{
		//IGNORE THIS IF YOU HAVE NOT COMMENTED OUT THE IF STATEMENT
		//This prevents the host to send to itself, thus not seeing the "clients" side of the game
		if(myServerPeer->GetSystemAddressFromIndex(i) != aSourceAddress)
		{
			RakNet::BitStream bsOut;
			bsOut.Write((RakNet::MessageID)aMessage->GetType());
			bsOut.Write(RakNet::GetTime());
			aMessage->WriteToBitStream(bsOut);
			myServerPeer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, myServerPeer->GetSystemAddressFromIndex(i), false);
		}
	}
}

void NetworkEngine::SwapMessageQueue()
{
	if(myHost.myIsHost.load() == true)
	{
		for(int index = 0; index < myServerQueueToSend.Size(); ++index)
		{
			NetworkMessage* message = myServerQueueToSend[index];

			//if(myHost.myIsHost.load() == true)
			//{
			//	//while(RakNet::GetTime() - message->GetTime() < latency + (jittermin + (rand() % 1000) / 1000.0f *(jittermax - jittermin)))
			//	while(RakNet::GetTime() - message->GetTime() < 500.0f)
			//	{
			//		Sleep(1);
			//	}
			//}	
			if(RakNet::GetTime() - message->GetTime() > myLatency + (myJitterMin + (rand() % 1000) / 1000.0f *(myJitterMax - myJitterMin)))
			{
				RakNet::BitStream bsOut;
				bsOut.Write((RakNet::MessageID)message->GetType());
				bsOut.Write(RakNet::GetTime());
				message->WriteToBitStream(bsOut);

				myClientPeer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, myHost.myHostAddress, false);


				delete message;


				myServerQueueToSend.RemoveCyclicAtIndex(index);

				--index;
			}
		}

		if(myServerHasReceivedMesssages.load() == true)
		{
			if(myServerMessagesToFill == &myServerFirstMessageQueue)
			{
				myServerActiveMessages = &myServerFirstMessageQueue;
				myServerMessagesToFill = &myServerSecondMessageQueue;
			}
			else if(myServerMessagesToFill == &myServerSecondMessageQueue)
			{
				myServerActiveMessages = &myServerSecondMessageQueue;
				myServerMessagesToFill = &myServerFirstMessageQueue;
			}

			myServerMessagesToFill->RemoveAll();
			myServerHasReceivedMesssages.store(false);
		}
	}

	for(int index = 0; index < myClientQueueToSend.Size(); ++index)
	{
		NetworkMessage* message = myClientQueueToSend[index];

		RakNet::BitStream bsOut;
		bsOut.Write((RakNet::MessageID)message->GetType());
		bsOut.Write(RakNet::GetTime());
		message->WriteToBitStream(bsOut);

		myClientPeer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, myHost.myHostAddress, false);


		delete message;


		myClientQueueToSend.RemoveCyclicAtIndex(index);

		--index;
	}

	if(myClientHasReceivedMesssages.load() == true)
	{
		if(myClientMessagesToFill == &myClientFirstMessageQueue)
		{
			myClientActiveMessages = &myClientFirstMessageQueue;
			myClientMessagesToFill = &myClientSecondMessageQueue;
		}
		else if(myClientMessagesToFill == &myClientSecondMessageQueue)
		{
			myClientActiveMessages = &myClientSecondMessageQueue;
			myClientMessagesToFill = &myClientFirstMessageQueue;
		}

		myClientMessagesToFill->RemoveAll();
		myClientHasReceivedMesssages.store(false);
	}
	/*myServerHasReceivedMesssages.store(true);
	myClientHasReceivedMesssages.store(true);*/
	myUpdateIsDone.store(false);
}