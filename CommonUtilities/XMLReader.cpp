#include "XMLReader.h"
#include "DL_Assert.h"
#include "DL_Debug.h"
#include <assert.h>

XMLReader::XMLReader(void)
{
}


XMLReader::~XMLReader(void)
{
}

tinyxml2::XMLElement* XMLReader::LoadFile(const std::string &aFilePath)
{
	DL_PRINT("    Opening " + aFilePath);
	myRootElement = nullptr;
	myDocument.LoadFile(aFilePath.c_str());
	if (myDocument.ErrorID() != tinyxml2::XMLError::XML_NO_ERROR)
	{
		//DL_PRINT("!!! ERROR! couldn't read " + aFilePath);
		//DL_PRINT(myDocument.GetErrorStr1());
		//bool errorReading = false;
		//assert(errorReading == true && "Could not load xml");
	}
	else
	{
		myRootElement = myDocument.RootElement();
	}

	return myRootElement;
}

tinyxml2::XMLElement* XMLReader::GetElementWithName(const std::string &aChildName)
{
	CheckIfChildExistsForElement(myRootElement, aChildName);
	return myRootElement->FirstChildElement(aChildName.c_str());
}

tinyxml2::XMLElement* XMLReader::GetChildElementWithName(tinyxml2::XMLElement* aElement, const std::string &aChildName)
{
	CheckIfChildExistsForElement(aElement, aChildName);
	return aElement->FirstChildElement(aChildName.c_str());
}


void XMLReader::TraverseToSiblingElement(tinyxml2::XMLElement* &anElement, const std::string &anElementName)
{
	if (anElement->NextSiblingElement(anElementName.c_str()) != nullptr)
	{
		anElement = anElement->NextSiblingElement(anElementName.c_str());
	}
	else
	{
		anElement = nullptr;
	}
}



//attributes

std::string	XMLReader::ReadElementName(tinyxml2::XMLElement* aElement)
{
	return std::string(aElement->Value());
}

std::string XMLReader::ReadStringAttributeForElement(tinyxml2::XMLElement* aElement, const std::string &aAttribute)
{
	CheckIfAttributeExistsForElement(aElement, aAttribute);
	return aElement->Attribute(aAttribute.c_str());
}

float XMLReader::ReadFloatAttributeForElement(tinyxml2::XMLElement* aElement, const std::string &aAttribute)
{
	CheckIfAttributeExistsForElement(aElement, aAttribute);
	return aElement->FloatAttribute(aAttribute.c_str());
}

char XMLReader::ReadCharAttributeForElement(tinyxml2::XMLElement* aElement, const std::string &aAttribute)
{
	CheckIfAttributeExistsForElement(aElement, aAttribute);
	return static_cast<char>(aElement->IntAttribute(aAttribute.c_str()));
}

int XMLReader::ReadIntAttributeForElement(tinyxml2::XMLElement* aElement, const std::string &aAttribute)
{
	CheckIfAttributeExistsForElement(aElement, aAttribute);
	return aElement->IntAttribute(aAttribute.c_str());
}

short XMLReader::ReadShortAttributeForElement(tinyxml2::XMLElement* aElement, const std::string &aAttribute)
{
	CheckIfAttributeExistsForElement(aElement, aAttribute);
	return static_cast<short>(aElement->IntAttribute(aAttribute.c_str()));
}

unsigned int XMLReader::ReadUnsignedIntAttributeForElement(tinyxml2::XMLElement* aElement, const std::string &aAttribute)
{
	CheckIfAttributeExistsForElement(aElement, aAttribute);
	return aElement->UnsignedAttribute(aAttribute.c_str());
}

unsigned short XMLReader::ReadUnsignedShortAttributeForElement(tinyxml2::XMLElement* aElement, const std::string &aAttribute)
{
	CheckIfAttributeExistsForElement(aElement, aAttribute);
	return static_cast<unsigned short>(aElement->UnsignedAttribute(aAttribute.c_str()));
}

unsigned long XMLReader::ReadUnsignedLongAttributeForElement(tinyxml2::XMLElement* aElement, const std::string &aAttribute)
{
	CheckIfAttributeExistsForElement(aElement, aAttribute);
	return static_cast<unsigned long>(aElement->UnsignedAttribute(aAttribute.c_str()));
}

bool XMLReader::ReadBoolAttributeForElement(tinyxml2::XMLElement* aElement, const std::string &aAttribute)
{
	CheckIfAttributeExistsForElement(aElement, aAttribute);
	return aElement->BoolAttribute(aAttribute.c_str());
}
//end attributes

//values
std::string XMLReader::ReadStringValueForElement(tinyxml2::XMLElement* aElement)
{
	CheckIfValueIsNull(aElement);
	return aElement->GetText();
}

float XMLReader::ReadFloatValueForElement(tinyxml2::XMLElement* aElement)
{
	CheckIfValueIsNull(aElement);
	return static_cast<float>(std::stof(aElement->GetText()));
}

char XMLReader::ReadCharValueForElement(tinyxml2::XMLElement* aElement)
{
	CheckIfValueIsNull(aElement);
	return static_cast<char>(std::stoi(aElement->GetText()));
}

int XMLReader::ReadIntValueForElement(tinyxml2::XMLElement* aElement)
{
	CheckIfValueIsNull(aElement);
	return static_cast<int>(std::stoi(aElement->GetText()));
}

short XMLReader::ReadShortValueForElement(tinyxml2::XMLElement* aElement)
{
	CheckIfValueIsNull(aElement);
	return static_cast<short>(std::stoi(aElement->GetText()));
}

unsigned int XMLReader::ReadUnsignedIntValueForElement(tinyxml2::XMLElement* aElement)
{
	CheckIfValueIsNull(aElement);
	return static_cast<unsigned int>(std::stol(aElement->GetText()));
}

unsigned short XMLReader::ReadUnsignedShortValueForElement(tinyxml2::XMLElement* aElement)
{
	CheckIfValueIsNull(aElement);
	return static_cast<unsigned short>(std::stol(aElement->GetText()));
}

bool XMLReader::ReadBoolValueForElement(tinyxml2::XMLElement* aElement)
{
	CheckIfValueIsNull(aElement);
	if (std::strcmp(aElement->GetText(), "true") != 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//end values

void XMLReader::CheckIfChildExistsForElement(const tinyxml2::XMLElement* aRootElement, const std::string& aElementName)
{
	if (aRootElement->FirstChildElement(aElementName.c_str()) == nullptr)
	{
		std::string error = "!!! ERROR! Couldn't find child element with name '" + aElementName + "'. in element '" + aRootElement->Value() + "'.";
		DL_PRINT(error);
		bool errorReading = false;
		assert(errorReading == true && "Could not find element");
	}
}

void XMLReader::CheckIfAttributeExistsForElement(const tinyxml2::XMLElement* aElement, const std::string &aAttribute)
{
	if (aElement->FindAttribute(aAttribute.c_str()) == 0)
	{
		std::string error = "!!! ERROR! Couldn't read attribute '" + aAttribute + "' in element '" + aElement->Value() + "'.";
		DL_PRINT(error);
		bool errorReading = false;
		assert(errorReading == true && "Could not read attribute for element");
	}
}

void XMLReader::CheckIfValueIsNull(const tinyxml2::XMLElement* aElement)
{
	if (aElement->GetText() == NULL)
	{
		std::string error1 = aElement->Value();
		std::string error = "!!! ERROR! Couldn't read value for element '" + error1 + "'.";
		DL_PRINT(error);
		bool errorReading = false;
		assert(errorReading == true && "Could not read value for element");
	}
}
