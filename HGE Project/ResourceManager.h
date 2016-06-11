#ifndef _RESOURCE_MANAGER_H_
#define _RESOURCE_MANAGER_H_

#include <map>
#include <string>
#include <hge.h>
#include <hgesprite.h>

class hgeFont;

class ResourceManager
{
	friend class Megaton;
public:
	inline hgeSprite* GetSprite(const std::string& aFileName);
	inline hgeFont* GetFont();

private:
	ResourceManager(HGE* aHGE);
	~ResourceManager();

	HGE* myHGE;
	std::map<std::string, hgeSprite*> mySprites;
	hgeFont* myFont;
};

inline hgeSprite* ResourceManager::GetSprite(const std::string& aFileName)
{
	if(mySprites[aFileName] == nullptr)
	{
		HTEXTURE texture = myHGE->Texture_Load(aFileName.c_str());
		mySprites[aFileName] = new hgeSprite(texture, 0.f, 0.f, static_cast<float>(myHGE->Texture_GetWidth(texture)), static_cast<float>(myHGE->Texture_GetHeight(texture)));
	}

	return mySprites[aFileName];
}

inline hgeFont* ResourceManager::GetFont()
{
	return myFont;
}

#endif