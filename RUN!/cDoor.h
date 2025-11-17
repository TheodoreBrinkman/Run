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

class cDoor :
	public cAnimatedSprite
{
public:
	cDoor(unsigned long x, unsigned long y, bool locked);
	~cDoor();

	virtual std::pair<cRect*, cRect*> CollisionBox();

private:
	bool _locked;
	enum _Animations : unsigned short
	{
		ANIMATION_UNLOCKED_KEY,
		ANIMATION_LOCKED_KEY
	};

	void _Init();

	static STRING cDoor::IMAGE_FILE_PATH;
	static unsigned long cDoor::ANIMATION_UNLOCKED_START;
	static unsigned long cDoor::ANIMATION_UNLOCKED_COUNT;
	static unsigned long cDoor::ANIMATION_LOCKED_START;
	static unsigned long cDoor::ANIMATION_LOCKED_COUNT;

	static unsigned long cDoor::WIDTH;
	static unsigned long cDoor::HEIGHT;
};