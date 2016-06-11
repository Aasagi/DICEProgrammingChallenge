#include "DL_Debug.h"
#include "DL_StackWalker.h"
#include "DL_Assert.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <assert.h>

DL_Debug::Debug* DL_Debug::Debug::myInstance = nullptr;

DL_Debug::Debug::Debug(void)
{
}

DL_Debug::Debug::~Debug(void)
{
}

bool DL_Debug::Debug::Create(std::string aFileName)
{
	myInstance = new DL_Debug::Debug();
	if(myInstance->Init(aFileName) == false)
	{
		return false;
	}

	return true;
}
bool DL_Debug::Debug::Init(std::string aFileName)
{
	myDebugFile.open("DebugLogger.txt", std::ios::out | std::ios::trunc);
	//myThisInstance->myDebugFile.close();

	if(myDebugFile.is_open() == false)
	{
		return false;
	}

	return true;
}
bool DL_Debug::Debug::Destroy()
{
	myInstance->myDebugFile.close();
	if(myInstance->myDebugFile.fail() == false)
	{
		SAFE_DELETE(myInstance);
	}
	if(myInstance == nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}

DL_Debug::Debug* DL_Debug::Debug::GetInstance()
{
	return myInstance;
}

void DL_Debug::Debug::AssertMessage(wchar_t* aErrorFile, int aLineNumber, wchar_t* aFunctionName, wchar_t* aErrorMessage)
{
	myDebugFile << "---===ASSERT MESSAGE===---" << std::endl;
	myDebugFile << "File: " << aErrorFile << "\n" << "Line: " << aLineNumber << "\n" << "Function: " << aFunctionName << "\n" << "Error: " << aErrorMessage << std::endl;
	
	DL_Debug::StackWalker sw;
	DL_PRINT("\nCallstack:");
	sw.ShowCallstack();
	
	std::wcout.flush();
	myDebugFile.flush();
	
	_wassert(aErrorMessage, aErrorFile, aLineNumber);
}

void DL_Debug::Debug::PrintMessage(std::string aErrorMessage)
{
	std::wstring string(aErrorMessage.begin(), aErrorMessage.end());
	myDebugFile << string << std::endl;
	
	std::wcout.flush();
	myDebugFile.flush();
}

void DL_Debug::Debug::DebugMessage(wchar_t* aErrorFile, int aLineNumber, wchar_t* aFunctionName, char* aFormat, ...)
{
	myDebugFile << "---===DEBUG MESSSAGE===---" << std::endl;
	const unsigned short bufferSize = 256;
	char messageBuffer[bufferSize];

	va_list arguments;
	va_start(arguments, aFormat);
	vsnprintf_s(messageBuffer, bufferSize, aFormat, arguments);
	va_end(arguments);
	
	myDebugFile << "File: " << aErrorFile << "\n" << "Line: " << aLineNumber << "\n" << "Function: " << aFunctionName << "\n" << "Messages: " << messageBuffer << std::endl;

	std::wcout.flush();
	myDebugFile.flush();
}

void DL_Debug::Debug::WriteLog(char* aName, char* aFormat, ...)
{
	if(myLogs.find(aName) != myLogs.end())
	{
		const unsigned short bufferSize = 256;
		char messageBuffer[bufferSize];

		va_list arguments;
		va_start(arguments, aFormat);
		vsnprintf_s(messageBuffer, bufferSize, aFormat, arguments);
		va_end(arguments);

		SYSTEMTIME time;

		GetLocalTime(&time);

		int milliSecond = time.wMilliseconds;
		int milliSecondsZeros = 3;

		if(milliSecond <= 0)
		{
			milliSecondsZeros = 2;
		}
		while(milliSecond > 0)
		{
			--milliSecondsZeros;
			milliSecond /= 10;
		}
		
		myDebugFile << "[" << time.wHour << ":" << time.wMinute << ":" << time.wSecond << ":";
		for(int i = 0; i < milliSecondsZeros; ++i)
		{
			myDebugFile << 0;
		}
		myDebugFile << time.wMilliseconds << "]" << "[" << aName << "]";
		myDebugFile << "Message sent by " << aName << ": " << messageBuffer << std::endl;

		std::wcout.flush();
		myDebugFile.flush();
	}
}

void DL_Debug::Debug::ActivateFilterLog(const std::string& aLogName)
{
	if(myLogs.find(aLogName) == myLogs.end())
	{
		myLogs.insert(aLogName);
	}
}

void DL_Debug::Debug::DeActivateFilterLog(const std::string& aLogName)
{
	if(myLogs.find(aLogName) != myLogs.end())
	{
		myLogs.erase(aLogName);
	}
}
