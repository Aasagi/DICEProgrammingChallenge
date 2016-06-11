#include "stdafx.h"
#include "GameObject.h"

GameObject::GameObject() { }

GameObject::~GameObject() { }

void GameObject::SetValue(const std::string& aKey, const float aValue)
{
	myValues[aKey] = aValue;
}

float GameObject::GetValue(const std::string& aKey)
{
	return myValues[aKey];
}