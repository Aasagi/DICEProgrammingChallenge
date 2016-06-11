#ifndef _INTERSECTION_H_
#define _INTERSECTION_H_

#define PI 3.14159265359f

#include "Vector2decl.h"

namespace CommonUtilities
{
	static bool LineSegment2DVsLineSegment2D(CU::Vector2f aStartPos1, CU::Vector2f aEndPos1, CU::Vector2f aStartPos2, CU::Vector2f aEndPos2, CU::Vector2f& aIntersectionPoint)
	{
		float x1, y1, x2, y2;

		x1 = aEndPos1.x - aStartPos1.x;
		y1 = aEndPos1.y - aStartPos1.y;

		x2 = aEndPos2.x - aStartPos2.x;
		y2 = aEndPos2.y - aStartPos2.y;

		float s, t;
		s = (-y1 * (aStartPos1.x - aStartPos2.x) + x1 * (aStartPos1.y - aStartPos2.y)) / (-x2 * y1 + x1 * y2);
		t = (x2 * (aStartPos1.y - aStartPos2.y) - y2 * (aStartPos1.x - aStartPos2.x)) / (-x2 * y1 + x1 * y2);

		if(0 <= s && s <= 1 && 0 <= t && t <= 1)
		{
			// Collision detected
			aIntersectionPoint.x = aStartPos1.x + (t * x1);
			aIntersectionPoint.y = aStartPos1.y + (t * y1);
			return true;
		}

		return false; // No collision
	}

	//Works only for Counter clock wise
	static inline bool PointInsideLine(LineSegment2D& aLineSegment, const CU::Vector2f& aPoint)
	{
		CU::Vector2f direction = GetNormalized(aLineSegment.myEnd - aLineSegment.myStart);

		CU::Vector2f normal;
		normal.x = direction.x * cos(PI / 2.0f) + direction.y * sin(PI / 2.0f);
		normal.y = direction.x * -sin(PI / 2.0f) + direction.y * cos(PI / 2.0f);
		CU::Vector2f vector = aPoint - aLineSegment.myStart;
		float d = Dot(normal, vector);
		if(d > 0.0f)
		{
			return true;
		}
		return false;
	}
};

#endif