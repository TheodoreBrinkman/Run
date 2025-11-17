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
#include "cDoor.h"

// STATIC INITIALIZATION
STRING cDoor::IMAGE_FILE_PATH = TEXT("./Images/Doors.png");
unsigned long cDoor::ANIMATION_UNLOCKED_START = 0;
unsigned long cDoor::ANIMATION_UNLOCKED_COUNT = 2;
unsigned long cDoor::ANIMATION_LOCKED_START = cDoor::ANIMATION_UNLOCKED_START + cDoor::ANIMATION_UNLOCKED_COUNT;
unsigned long cDoor::ANIMATION_LOCKED_COUNT = 2;

unsigned long cDoor::WIDTH = 192;
unsigned long cDoor::HEIGHT = 192;

// CONSTRUCTORS
cDoor::cDoor(unsigned long x, unsigned long y, bool locked)
	: cAnimatedSprite(cDoor::IMAGE_FILE_PATH)
{
	this->_position.x = x;
	this->_position.y = y;
	this->_locked = locked;
	this->_Init();
}

// DESTRUCTOR
cDoor::~cDoor()
{
}

// PUBLIC METHODS
std::pair<cRect*, cRect*> cDoor::CollisionBox()
{
	std::pair<cRect*,cRect*> cb = cSprite::CollisionBox();
	cb.first->Right = cb.first->Left + 64;
	cb.second->Right = cb.second->Left + 64;
	return(cb);
}

// PRIVATE METHODS
void cDoor::_Init()
{
	double frameRate = 2.0;
	unsigned long leftEdge = 0;
	unsigned long topEdge = 0;
	this->_AddAnimationData(cDoor::ANIMATION_UNLOCKED_KEY, cDoor::ANIMATION_UNLOCKED_START, cDoor::ANIMATION_UNLOCKED_COUNT, frameRate);
	for(unsigned long i=0;i<cDoor::ANIMATION_LOCKED_COUNT;i++)
	{
		unsigned long left = leftEdge + (i * cDoor::WIDTH);
		this->_frames.push_back(new cRect(topEdge, left, left + cDoor::WIDTH, cDoor::HEIGHT));
	}
	leftEdge += (cDoor::ANIMATION_UNLOCKED_COUNT * cDoor::WIDTH);

	this->_AddAnimationData(cDoor::ANIMATION_LOCKED_KEY, cDoor::ANIMATION_LOCKED_START, cDoor::ANIMATION_LOCKED_COUNT, frameRate);
	for(unsigned long i=0;i<cDoor::ANIMATION_LOCKED_COUNT;i++)
	{
		unsigned long left = leftEdge + (i * cDoor::WIDTH);
		this->_frames.push_back(new cRect(topEdge, left, left + cDoor::WIDTH, cDoor::HEIGHT));
	}
	leftEdge += (cDoor::ANIMATION_LOCKED_COUNT * cDoor::WIDTH);
}