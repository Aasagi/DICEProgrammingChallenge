#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "CommonUtilities\Vector2.h"
#include <math.h>

class Player
{
public:
	Player();
	~Player();

	inline void SetDestination(const CU::Vector2f& aPosition);
	inline void SetDestination(const float aX, const float aY);
	inline void SetPosition(const CU::Vector2f& aPosition);
	inline void SetPosition(const float aX, const float aY);

	inline void SetVelocity(const CU::Vector2f& aVelocity);
	inline void SetMoveSpeed(const float aMoveSpeed);
	inline void SetTime(const float aTime);

	inline CU::Vector2f GetCenterPosition();
	inline const CU::Vector2f& GetPosition() const;
	inline const CU::Vector2f& GetVelocity() const;
	inline const float GetMoveSpeed() const;
	inline const float GetTime() const;
	inline const float GetCalculatedFrameTime() const;

	inline void ResetTime();

	inline void ReverseX();
	inline void ReverseY();

	short myHealth;
	bool myIsAlive;

private:
	CU::Vector2f myDestination;
	CU::Vector2f myPosition;
	CU::Vector2f myVelocity;
	float myMoveSpeed;
	float myTime;
	float myPreviousTime;
	bool myHasSetTime;
};

inline void Player::SetDestination(const CU::Vector2f& aPosition)
{
	myPosition = myDestination;
	myDestination = aPosition;
	myVelocity = GetNormalized(myDestination - myPosition);
	if(myPosition == myDestination)
	{
		myVelocity = CU::Vector2f(0,0);
	}
}

inline void Player::SetDestination(const float aX, const float aY)
{
	myPosition = myDestination;
	myDestination = CU::Vector2f(aX, aY);
	myVelocity = GetNormalized(myDestination - myPosition);
	if (myPosition == myDestination)
	{
		myVelocity = CU::Vector2f(0, 0);
	}
}

inline void Player::SetPosition(const CU::Vector2f& aPosition)
{
	myPosition = aPosition;
}

inline void Player::SetPosition(const float aX, const float aY)
{
	myPosition.x = aX;
	myPosition.y = aY;
}

inline void Player::SetVelocity(const CU::Vector2f& aVelocity)
{
	myVelocity = aVelocity;
}

inline void Player::SetMoveSpeed(const float aMoveSpeed)
{
	myMoveSpeed = aMoveSpeed;
}

inline void Player::SetTime(const float aTime)
{
	myPreviousTime = myTime;
	myTime = aTime;
	if (myHasSetTime == false)
	{
		myPreviousTime = aTime;
		myHasSetTime = true;
	}
}

inline CU::Vector2f Player::GetCenterPosition()
{
	return myPosition + CU::Vector2f(16, 16);
}

inline const CU::Vector2f& Player::GetPosition() const
{
	return myPosition;
}

inline const CU::Vector2f& Player::GetVelocity() const
{
	return myVelocity;
}

inline const float Player::GetMoveSpeed() const
{
	return myMoveSpeed;
}

inline const float Player::GetTime() const
{
	return myTime;
}

inline const float Player::GetCalculatedFrameTime() const
{
	float debugTime = static_cast<float>(myTime - myPreviousTime) / 1000.f;
	return static_cast<float>(myTime - myPreviousTime) / 1000.f;
}

inline void Player::ResetTime()
{
	myPreviousTime = 0.0f;
	myHasSetTime = false;
}

inline void Player::ReverseX()
{
	myVelocity.x *= -1.f;
}

inline void Player::ReverseY()
{
	myVelocity.y *= -1.f;
}

#endif