#ifndef _XML_READER_H_
#define _XML_READER_H_

#include <string>

#include "tinyxml2.h"

class XMLReader
{
	public:
		XMLReader(void);
		~XMLReader(void);

		tinyxml2::XMLElement*	LoadFile(const std::string &aFilePath);

		tinyxml2::XMLElement*	GetElementWithName(const std::string &aChildName);
		tinyxml2::XMLElement*	GetChildElementWithName(tinyxml2::XMLElement* aElement, const std::string &aChildName);
		void					TraverseToSiblingElement(tinyxml2::XMLElement* &anElement, const std::string &anElementName);

		std::string				ReadStringAttributeForElement(tinyxml2::XMLElement* aElement, const std::string &aAttribute);
		float					ReadFloatAttributeForElement(tinyxml2::XMLElement* aElement, const std::string &aAttribute);
		char					ReadCharAttributeForElement(tinyxml2::XMLElement* aElement, const std::string &aAttribute);
		int						ReadIntAttributeForElement(tinyxml2::XMLElement* aElement, const std::string &aAttribute);
		short					ReadShortAttributeForElement(tinyxml2::XMLElement* aElement, const std::string &aAttribute);
		unsigned int			ReadUnsignedIntAttributeForElement(tinyxml2::XMLElement* aElement, const std::string &aAttribute);
		unsigned short			ReadUnsignedShortAttributeForElement(tinyxml2::XMLElement* aElement, const std::string &aAttribute);
		unsigned long			ReadUnsignedLongAttributeForElement(tinyxml2::XMLElement* aElement, const std::string &aAttribute);
		bool					ReadBoolAttributeForElement(tinyxml2::XMLElement* aElement, const std::string &aAttribute);
		std::string				ReadElementName(tinyxml2::XMLElement* aElement);

		std::string				ReadStringValueForElement(tinyxml2::XMLElement* aElement);
		float					ReadFloatValueForElement(tinyxml2::XMLElement* aElement);
		char					ReadCharValueForElement(tinyxml2::XMLElement* aElement);
		int						ReadIntValueForElement(tinyxml2::XMLElement* aElement);
		short					ReadShortValueForElement(tinyxml2::XMLElement* aElement);
		unsigned int			ReadUnsignedIntValueForElement(tinyxml2::XMLElement* aElement);
		unsigned short			ReadUnsignedShortValueForElement(tinyxml2::XMLElement* aElement);
		bool					ReadBoolValueForElement(tinyxml2::XMLElement* aElement);

	protected:
		void					CheckIfChildExistsForElement(const tinyxml2::XMLElement* aRootElement, const std::string& aElementName);
		void					CheckIfAttributeExistsForElement(const tinyxml2::XMLElement* aElement, const std::string &aAttribute);
		void					CheckIfValueIsNull(const tinyxml2::XMLElement* aElement);

		tinyxml2::XMLDocument	myDocument;
		tinyxml2::XMLElement*	myRootElement;
};

#endif