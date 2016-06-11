#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	myMoveSpeed = 0.0f;
	myTime = 0.0f;
	myPreviousTime = 0.0f;
	myHasSetTime = false;
	myHealth = 3;
}

Player::~Player()
{
}