#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include <map>
#include <string>

class GameObject
{
public:
	GameObject();
	~GameObject();

	void SetValue(const std::string& aKey, const float aValue);
	float GetValue(const std::string& aKey);

	std::string myScriptName;
	int myId;

private:
	std::map<std::string, float> myValues;
};

#endif