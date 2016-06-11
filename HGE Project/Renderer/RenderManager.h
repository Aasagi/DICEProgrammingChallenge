#ifndef _RENDER_MANAGER_H_
#define _RENDER_MANAGER_H_

#include "RenderCommand.h"
#include "Renderer.h"
#include "hge.h"
#include "CommonUtilities/Heap.h"

namespace CU = CommonUtilities;

class RenderManager
{
	friend class Megaton;
public:

	static void								Create(Renderer* someRenderer);

	void									Update();

	void									AddCommand(RenderCommand* someCommand);

	inline static RenderManager*			GetInstance();

private:

	RenderManager(Renderer* someRenderer);
	~RenderManager(void);

	void									SwapRendererCommands();

	CU::Heap<RenderCommand*, CU::GreaterPointer<RenderCommand*>>			myFirstRenderCommands;
	CU::Heap<RenderCommand*, CU::GreaterPointer<RenderCommand*>>			mySecondRenderCommands;

	CU::Heap<RenderCommand*, CU::GreaterPointer<RenderCommand*>>*			myRenderCommandsToFill;

	Renderer*								myRenderer;

	static RenderManager*					myInstance;
};

inline RenderManager* RenderManager::GetInstance()
{
	return myInstance;
}

#endif