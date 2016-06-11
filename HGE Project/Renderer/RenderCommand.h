#ifndef _RENDER_COMMAND_H
#define _RENDER_COMMAND_H

#include "CommonUtilities/Vector2decl.h"

struct RenderCommand
{
	public:
		RenderCommand();
		virtual ~RenderCommand();

		bool						operator>(const RenderCommand& aCommand);
		bool						operator<(const RenderCommand& aCommand);
		bool						operator>=(const RenderCommand& aCommand);
		bool						operator<=(const RenderCommand& aCommand);

		virtual void				Draw();

		inline CU::Vector2<float>	GetPosition();
		void						SetPosition(const CU::Vector2<float>& somePosition);
		void						SetZ(float aZ);
		void						SetColor(unsigned long aColor);
		void						SetScaleH(const float& aScale);
		void						SetScaleV(const float& aScale);
		void						SetRotation(const float& aRotation);
		float						myZ;

	protected:
		float						myRotation;
		float						myScaleH;
		float						myScaleV;
		CU::Vector2<float>			myPosition;
		unsigned long				myColor;
};

inline CU::Vector2<float> RenderCommand::GetPosition()
{
	return myPosition;
}

#endif