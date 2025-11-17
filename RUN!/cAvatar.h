/******************************************************************************\
*                                                                              *
*	Copyright © 2009-2010 Theo Brinkman. All rights reserved.                       *
*                                                                              *
*	This work is licensed under a Creative Commons                             *
*	Attribution-Noncommercial-No Derivative Works 3.0 United States License.   *
*                                                                              *
*	See COPYING.TXT for details.                                               *
*                                                                              *
\******************************************************************************/
#pragma once
#include "cAnimatedSprite.h"
#include "cInputManager.h"

class cAvatar :
	public cAnimatedSprite
{
public:
	cAvatar(double x, double y);
	~cAvatar();
	virtual std::pair<cRect*, cRect*> CollisionBox();
	virtual void Update(double interval, double gravity);
	virtual void TileCollision(std::pair<cRect*,cRect*> intersect);
	virtual void ObjectCollision(std::pair<cRect*,cRect*> intersect, IObject *object);
	void SetPosition(POINT2D position);
	void OnLadder(bool onLadder);

private:
	bool _pushing;
	bool _onLadder;

	void _Init();

	static STRING cAvatar::IMAGE_FILE_PATH;

	enum _Animations : unsigned short
	{
		ANIMATION_STAND_KEY,
		ANIMATION_RUN_KEY,
		ANIMATION_WALK_KEY,
		ANIMATION_CLIMB_KEY,
		ANIMATION_JUMP_KEY,
//		ANIMATION_CRAWL_KEY,
//		ANIMATION_HOIST_KEY,
//		ANIMATION_PUSH_KEY,
//		ANIMATION_LIFT_KEY,
//		ANIMATION_CARRY_KEY,
//		ANIMATION_DROP_KEY,
//		ANIMATION_DIE_KEY
	};
	static unsigned long cAvatar::ANIMATION_STAND_COUNT;
	static unsigned long cAvatar::ANIMATION_STAND_START;
	static unsigned long cAvatar::ANIMATION_RUN_COUNT;
	static unsigned long cAvatar::ANIMATION_RUN_START;
	static unsigned long cAvatar::SPEED_RUN;
	static unsigned long cAvatar::ANIMATION_WALK_COUNT;
	static unsigned long cAvatar::ANIMATION_WALK_START;
	static unsigned long cAvatar::SPEED_WALK;
	static unsigned long cAvatar::ANIMATION_CLIMB_COUNT;
	static unsigned long cAvatar::ANIMATION_CLIMB_START;
	static unsigned long cAvatar::SPEED_CLIMB;
	static unsigned long cAvatar::ANIMATION_JUMP_COUNT;
	static unsigned long cAvatar::ANIMATION_JUMP_START;
	static double cAvatar::JUMP_VELOCITY;
	//static unsigned long cAvatar::ANIMATION_LIFT_COUNT;
	//static unsigned long cAvatar::ANIMATION_LIFT_START;
	//static unsigned long cAvatar::ANIMATION_CARRY_COUNT;
	//static unsigned long cAvatar::ANIMATION_CARRY_START;
	//static unsigned long cAvatar::ANIMATION_PUSH_COUNT;
	//static unsigned long cAvatar::ANIMATION_PUSH_START;
	//static unsigned long cAvatar::ANIMATION_CRAWL_COUNT;
	//static unsigned long cAvatar::ANIMATION_CRAWL_START;
	//static unsigned long cAvatar::ANIMATION_HOIST_COUNT;
	//static unsigned long cAvatar::ANIMATION_HOIST_START;
	//static unsigned long cAvatar::ANIMATION_DIE_COUNT;
	//static unsigned long cAvatar::ANIMATION_DIE_START;
};