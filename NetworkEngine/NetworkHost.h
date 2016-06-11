#ifndef _NETWORK_HOST_H_
#define _NETWORK_HOST_H_

#include "RakNet\RakNetTypes.h"
#include <atomic>

struct NetworkHost
{
	RakNet::SystemAddress myHostAddress;
	std::atomic_bool myIsHost;
};

#endif