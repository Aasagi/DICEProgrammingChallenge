#ifndef _DL_DEBUG_H_
#define _DL_DEBUG_H_

#include <string>
#include <fstream>
#include <set>

#define DL_ASSERT(string)	DL_Debug::Debug::GetInstance()->AssertMessage(__FILEW__, __LINE__, __FUNCTIONW__, _CRT_WIDE(string));
#define DL_PRINT(string)	DL_Debug::Debug::GetInstance()->PrintMessage(string);
#define DL_DEBUG(...)		DL_Debug::Debug::GetInstance()->DebugMessage(__FILEW__, __LINE__, __FUNCTIONW__, __VA_ARGS__);

#define DL_WRITELOG(log, ...) DL_Debug::Debug::GetInstance()->WriteLog(log, __VA_ARGS__);

#define USE_FILTERLOG

#ifdef USE_FILTERLOG
#define DL_APP_LOG(...) DL_WRITELOG("App", __VA_ARGS__);
#define DL_ENGINE_LOG(...) DL_WRITELOG("Engine", __VA_ARGS__);
#define LUA_LOG(...) DL_WRITELOG("Lua", __VA_ARGS__);
#else
#define DL_APP_LOG(...)
#define DL_ENGINE_LOG(...)
#define LUA_LOG(...)
#endif

#define DL_ACTIVATE_LOG(string) DL_Debug::Debug::GetInstance()->ActivateFilterLog(string);
#define DL_DEACTIVATE_LOG(string) DL_Debug::Debug::GetInstance()->DeActivateFilterLog(string);


#ifndef SAFE_DELETE
#define SAFE_DELETE(aPtr) delete aPtr; aPtr = nullptr
#endif

namespace DL_Debug
{
	class Debug
	{
	public:
		static bool				Create(std::string aFileName = "DebugLogger.txt");
		static bool				Destroy();
		static Debug*			GetInstance();

		void					AssertMessage(wchar_t* aErrorFile, int aLineNumber, wchar_t* aFunctionName, wchar_t* aErrorMessage);
		void					PrintMessage(std::string aErrorMessage);
		void					DebugMessage(wchar_t* aErrorFile, int aLineNumber, wchar_t* aFunctionName, char* aFormat, ...);
		void					WriteLog(char* aName, char* aFormat, ...);

		void					ActivateFilterLog(const std::string& aLogName);
		void					DeActivateFilterLog(const std::string& aLogName);

	private:
		Debug(void);
		~Debug(void);

		bool					Init(std::string aFileName);

		static Debug*			myInstance;
		std::wofstream			myDebugFile;
		std::set<std::string>	myLogs;
	};
}

#endif