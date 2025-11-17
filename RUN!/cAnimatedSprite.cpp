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
#include "cAnimatedSprite.h"

// STATIC INITIALIZATION
unsigned short cAnimatedSprite::DEFAULT_ANIMATION_KEY = 0;

// CONSTRUCTORS
cAnimatedSprite::cAnimatedSprite(STRING imageFilePath)
	: cSprite(imageFilePath)
{
	this->_Init();
}

cAnimatedSprite::cAnimatedSprite(STRING imageFilePath, cColor *transparentColor)
	: cSprite(imageFilePath, transparentColor)
{
	this->_Init();
}

// DESTRUCTOR
cAnimatedSprite::~cAnimatedSprite()
{
}

// PUBLIC METHODS
void cAnimatedSprite::Update(double interval, double gravity)
{
	cSprite::Update(interval, gravity);
	// update current frame timer
	this->_frameTimer += interval;
	while(this->_frameTimer >= this->_animations[this->_currentAnimation].frameInterval)
	{
		this->_frameIndex = (this->_frameIndex + 1) % this->_animations[this->_currentAnimation].frameCount;
		this->_frameTimer -= this->_animations[this->_currentAnimation].frameInterval;
	}
}

// PUBLIC STATIC METHODS

// PROTECTED METHODS
cRect* cAnimatedSprite::CurrentFrame()
{
	ANIMATION_DATA a = this->_animations[this->_currentAnimation];
	this->_frameIndex %= a.frameCount;
	return(this->_frames[a.startFrame + this->_frameIndex]);
}

// PROTECTED STATIC METHODS
void cAnimatedSprite::_AddAnimationData(unsigned short key, unsigned long startFrame, unsigned long frameCount, double frameInterval)
{
	ANIMATION_DATA *ad = new ANIMATION_DATA();
	ad->startFrame = startFrame;
	ad->frameCount = frameCount;
	ad->frameInterval = frameInterval;

	this->_animations[key] = *ad;
}

// PRIVATE METHODS
void cAnimatedSprite::_Init()
{
	this->_frameIndex = 0;
	this->_frameTimer = 0;
	this->_currentAnimation = cAnimatedSprite::DEFAULT_ANIMATION_KEY;
}

// PRIVATE STATIC METHODS
