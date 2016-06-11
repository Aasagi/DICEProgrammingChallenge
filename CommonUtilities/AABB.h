#ifndef INCL_AABB_H
#define INCL_AABB_H

#include "Vector2.h"

class AABB
{
public:
	AABB(void);
	AABB(const float aX, const float aY, const float aWidth, const float aHeight);
	~AABB(void);

	float		GetX() const;
	float		GetY() const;
	float		GetWidth() const;
	float		GetHeight() const;

	void		SetX(const float aX);
	void		SetY(const float aY);
	void		SetWidth(const float aWidth);
	void		SetHeight(const float aHeight);

	bool		Collides(const AABB aAABB) const;
	bool		Inside(const CU::Vector2f& aPoint) const;

private:
	float		myX;
	float		myY;
	float		myWidth;
	float		myHeight;
};

#endif