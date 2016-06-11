#ifndef I3U_TGA32_HEADER
#define I3U_TGA32_HEADER

#include "I3U_Enums.h"

struct I3U_TgaHeader {
	unsigned char myIdLength;				//0
	unsigned char myColorMapType;			//0
	unsigned char myImageType;				//2 (24 bit type)
	unsigned char myColorMapOrigin;			//0
	unsigned short myColorMapLength;		//0
	unsigned char myColorMapEntrySize;		//0
	unsigned short myImageOriginX;			//0
	unsigned short myImageOriginY;			//0
	unsigned short myWidth;					//width of image
	unsigned short myHeight;				//height of image
	unsigned char myBpp;					//24 bits
	unsigned char myImageDescriptor;		//bit 5 is 0 if origin is lower left, 1 if origin is upper left
};

class I3U_TGA32 {
public:
	I3U_TGA32();
	~I3U_TGA32();

	static I3U_ImageStruct* Load(const char* aName);
	static void Save(const char* aName,int myWidth,int myHeight,int myBitDepth,unsigned char* myData);
};

#endif

