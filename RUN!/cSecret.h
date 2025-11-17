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
#include "TYPEDEFS.h"
#include "canimatedsprite.h"

class cSecret :
	public cAnimatedSprite
{
public:
	cSecret(double x, double y);
	~cSecret();

private:
static STRING cSecret::IMAGE_FILE_PATH;
static unsigned short cSecret::ANIMATION_IDLE_KEY;
static unsigned long cSecret::ANIMATION_IDLE_COUNT;

static unsigned long cSecret::WIDTH;
static unsigned long cSecret::HEIGHT;
};