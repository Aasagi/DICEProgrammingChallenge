#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include "CommonUtilities/Heap.h"
#include "CommonUtilities/LesserPointer.h"
#include "CommonUtilities/GreaterPointer.h"
#include "RenderCommand.h"
#include <vector>

namespace CU = CommonUtilities;

class HGE;

class Renderer
{
public:
					Renderer();
					Renderer(HGE* aHGE);
					~Renderer(void);
	void			Init(HGE* aHGE);
	void			ThreadedUpdate();
	void			SetRenderBuffert(CU::Heap<RenderCommand*, CU::GreaterPointer<RenderCommand*>>* aRenderBuffert);
	bool			IsRenderDone();
	void			SetRenderIsDone(bool aIsDone);
	void			ShutDown();

private:
	CU::Heap<RenderCommand*, CU::GreaterPointer<RenderCommand*>>
					*myRenderCommands;



	volatile bool	myRenderDone;
	volatile bool	myShutdownThread;


	HGE*			myHGE;
	volatile bool	myClearScene;

};

inline void Renderer::ShutDown()
{
	myShutdownThread = true;
	myRenderDone = false;
}

inline void	Renderer::SetRenderIsDone(bool bIsDone)
{
	myRenderDone = bIsDone;
}

inline bool Renderer::IsRenderDone()
{
	return myRenderDone;
}

inline void Renderer::SetRenderBuffert(CU::Heap<RenderCommand*, CU::GreaterPointer<RenderCommand*>>* aRenderBuffert)
{
	myRenderCommands = aRenderBuffert;
}


#endif