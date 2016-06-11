#include "stdafx.h"
#include "hge.h"
#include "GameLoop.h"
#include "CommonUtilities/DL_Assert.h"
#include "CommonUtilities/DL_Debug.h"
#include "CommonUtilities/Vector.h"

CU::Vector2i FindResolution()
{
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);

#ifdef NDEBUG
	CU::Vector2i resolution(desktop.right, desktop.bottom);
#else
	CU::Vector2i resolution(1280, 720);
#endif

	DL_PRINT("    Found resolution: " + std::to_string(resolution.x) + " x " + std::to_string(resolution.y));

	return resolution;
}

void HGEShutdown(HGE* aHGE)
{
	aHGE->System_Shutdown();
	aHGE->Release();
}

HGE* HGEInit(const CU::Vector2i& aResolution)
{
	HGE *hge = hgeCreate(HGE_VERSION);

	hge->System_SetState(HGE_LOGFILE, "HGE_Error.log");
//#ifdef NDEBUG
	//hge->System_SetState(HGE_WINDOWED, false);
//#else
	hge->System_SetState(HGE_WINDOWED, true);
//#endif
	hge->System_SetState(HGE_USESOUND, false);
	hge->System_SetState(HGE_TITLE, "DICE Challenge");
	hge->System_SetState(HGE_SCREENWIDTH, aResolution.x);
	hge->System_SetState(HGE_SCREENHEIGHT, aResolution.y);
	hge->System_SetState(HGE_SHOWSPLASH, false);
	hge->System_SetState(HGE_HIDEMOUSE, false);

	if(hge->System_Initiate() == false)
	{
		char * response = hge->System_GetErrorMessage();
		DL_DEBUG("%s", response);
		delete response;
		HGEShutdown(hge);
		SAFE_DELETE(hge);
	}

	return hge;
}

void ConstrainMouseToWindow(HGE* aHGE)
{
	HWND wnd = aHGE->System_GetState(HGE_HWND);
	RECT client;
	GetClientRect(wnd, &client);

	POINT point;

	point.x = client.left;
	point.y = client.top;
	ClientToScreen(wnd, &point);
	client.left = point.x;
	client.top = point.y;

	point.x = client.right;
	point.y = client.bottom;
	ClientToScreen(wnd, &point);
	client.right = point.x;
	client.bottom = point.y;

	ClipCursor(&client);
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
#ifndef _DEBUG
	srand(static_cast<unsigned int>(time(nullptr)));
#endif

	DL_Debug::Debug::Create();
	CU::Vector2i resolution = CU::Vector2i(800, 600);//;= FindResolution();
	HGE *hge = HGEInit(resolution);

	if(hge == nullptr)
	{
		DL_DEBUG("Failed to initiate HGE");
		return -1;
	}

#ifdef NDEBUG
	ConstrainMouseToWindow(hge);
#endif

	GameLoop theGameLoop;
	theGameLoop.Init(hge, resolution);
	theGameLoop.Run();

	HGEShutdown(hge);

#ifdef NDEBUG
	ClipCursor(nullptr);
#endif


	return 0;
}