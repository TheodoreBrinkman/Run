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
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>
#include "cSprite.h"
#include "STRUCTURES.h"
#include "cInputManager.h"

class cAnimatedSprite :
	public cSprite
{
public:
	// Constructors
	cAnimatedSprite(STRING imageFilePath);
	cAnimatedSprite(STRING imageFilePath, cColor *transparentColor);
	// Destructor
	~cAnimatedSprite();

	// Interface Methods
	virtual void Update(double interval, double gravity);

protected:
	virtual cRect* CurrentFrame();
	std::vector<cRect*> _frames;
	std::map<unsigned short, ANIMATION_DATA> _animations;
	unsigned short _currentAnimation;
	unsigned long _frameIndex;
	double _frameTimer;

	virtual void _AddAnimationData(unsigned short key, unsigned long startFrame, unsigned long frameCount, double frameInterval);

private:
	void _Init();

	static unsigned short DEFAULT_ANIMATION_KEY;
};