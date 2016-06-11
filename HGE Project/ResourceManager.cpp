#include "stdafx.h"
#include "ResourceManager.h"
#include <hgefont.h>
ResourceManager::ResourceManager(HGE* aHGE)
{
	myHGE = aHGE;
	myFont = new hgeFont("Data/font1.fnt");
}

ResourceManager::~ResourceManager()
{
}