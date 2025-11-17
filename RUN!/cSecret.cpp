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
#include "cSecret.h"

// STATIC INITIALIZATION
STRING cSecret::IMAGE_FILE_PATH = TEXT("./Images/Secret.png");
unsigned short cSecret::ANIMATION_IDLE_KEY = 0;
unsigned long cSecret::ANIMATION_IDLE_COUNT = 14;

unsigned long cSecret::WIDTH = 64;
unsigned long cSecret::HEIGHT = 64;

// CONSTRUCTORS
cSecret::cSecret(double x, double y)
	: cAnimatedSprite(cSecret::IMAGE_FILE_PATH)
{
	this->_position.x = x;
	this->_position.y = y;
	ANIMATION_DATA ad;
	ad.startFrame = 0;
	ad.frameCount = cSecret::ANIMATION_IDLE_COUNT;
	ad.frameInterval = (1.0 / 30.0);
	this->_animations[cSecret::ANIMATION_IDLE_KEY] = ad;
	for(unsigned long i=0;i<ad.frameCount;i++)
	{
		unsigned long left = i * cSecret::WIDTH;
		this->_frames.push_back(new cRect(0, left, left + cSecret::WIDTH, cSecret::HEIGHT));
	}
	this->_currentAnimation = cSecret::ANIMATION_IDLE_KEY;
}

// DESTRUCTOR
cSecret::~cSecret()
{
}