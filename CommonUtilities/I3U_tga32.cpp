#include "I3U_TGA32.h"
#include <assert.h>
#include "I3U_Enums.h"
#include <iostream>

I3U_TGA32::I3U_TGA32()
{
}

I3U_TGA32::~I3U_TGA32()
{
}

void I3U_TGA32::Save(const char* aName,int aWidth,int aHeight,int aBitDepth,unsigned char* myData)
{
	FILE* fp;
	unsigned char* buffer;
	I3U_TgaHeader header;
	unsigned char* source;
	unsigned char* scanlineSource;
	unsigned char* destination;
	int x,y;

	header.myIdLength=0;				//0
	header.myColorMapType=0;			//0
	header.myImageType=2;				//2 (24 bit type)
	header.myColorMapOrigin=0;			//0
	header.myColorMapLength=0;		//0
	header.myColorMapEntrySize=0;		//0
	header.myImageOriginX=0;			//0
	header.myImageOriginY=0;			//0
	header.myWidth=aWidth;					//width of image
	header.myHeight=aHeight;				//height of image
	header.myBpp=aBitDepth;					//24 bits
	header.myImageDescriptor=0;		//bit 5 is 0 if origin is lower left, 1 if origin is upper left

	fopen_s(&fp, aName, "wb");
	//fp = fopen(aName, "wb");

	fwrite(&header,sizeof(header),1,fp);

	if(aBitDepth==24) {
		buffer = new unsigned char [aHeight*aWidth*3];
		source = myData + header.myWidth * (header.myHeight - 1) * 3; //flip image
		destination = buffer;
		for(y=0;y<header.myHeight;y++)
		{
			scanlineSource = source;
			for(x=0; x<header.myWidth; x++)
			{
				destination[0] = source[2]; // convert BGRA to RGBA
				destination[1] = source[1];
				destination[2] = source[0];
			
				source += 3;
				destination += 3;
			}
			source = scanlineSource - header.myWidth * 3;
		}

		fwrite(buffer,aHeight*aWidth*3,1,fp); // loads the image

		delete [] (buffer);
	}
	else
	{
	}

	fclose(fp);
	

}


I3U_ImageStruct* I3U_TGA32::Load(const char* aName)
{
	FILE* fp=NULL;
	I3U_ImageStruct* myImage;
	unsigned char* buffer;
	I3U_TgaHeader header;
	unsigned char* source;
	unsigned char* scanlineSource;
	unsigned char* destination;
	int x,y;
	
	myImage= new I3U_ImageStruct(); //allocates return object

	fopen_s(&fp, aName, "rb");
	//fp = fopen(aName, "rb");

	fread(&header,sizeof(header),1,fp); // loads the header



	myImage->myWidth = header.myWidth;
	myImage->myHeight = header.myHeight;

	if(header.myBpp==24) {
		myImage->myImage = new unsigned char [myImage->myHeight*myImage->myWidth*3];
		buffer = new unsigned char [myImage->myHeight*myImage->myWidth*3];

		fread(buffer,myImage->myHeight*myImage->myWidth*3,1,fp); // loads the image

		fclose (fp);

		source = buffer + header.myWidth * (header.myHeight - 1) * 3; //flip image
		destination = myImage->myImage;
		for(y=0;y<header.myHeight;y++)
		{
			scanlineSource = source;
			for(x=0; x<header.myWidth; x++)
			{
				destination[0] = source[2]; // convert BGRA to RGBA
				destination[1] = source[1];
				destination[2] = source[0];
				
				source += 3;
				destination += 3;
			}

			source = scanlineSource - header.myWidth * 3;
		}

		delete [] (buffer);

		myImage->myBitDepth=24;
		return(myImage);
	}
	else
	if(header.myBpp==32) {
		myImage->myImage = new unsigned char [myImage->myHeight*myImage->myWidth*4];
		buffer = new unsigned char [myImage->myHeight*myImage->myWidth*4];

		fread(buffer,myImage->myHeight*myImage->myWidth*4,1,fp); // loads the image

		fclose (fp);

		source = buffer + header.myWidth * (header.myHeight - 1) * 4; //flip image
		destination = myImage->myImage;
		for(y=0;y<header.myHeight;y++)
		{
			scanlineSource = source;
			for(x=0; x<header.myWidth; x++)
			{
				destination[0] = source[2]; // convert BGRA to RGBA
				destination[1] = source[1];
				destination[2] = source[0];
				destination[3] = source[3];
				
				source += 4;
				destination += 4;
			}

			source = scanlineSource - header.myWidth * 4;
		}

		delete [] (buffer);

		myImage->myBitDepth=32;
		return(myImage);
	}

	return(NULL);
}