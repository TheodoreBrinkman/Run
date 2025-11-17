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
#include "cSprite.h"
#include "cLevelMap.h"
#include "cRect.h"

class cLargeBox :
	public cSprite
{
public:
	cLargeBox(double x, double y);
	~cLargeBox();

	virtual void Update(double interval, double gravity);
	virtual std::pair<cRect*, cRect*> CollisionBox();

private:
	POINT2D _velocity;

	static STRING IMAGE_FILE_PATH;
};