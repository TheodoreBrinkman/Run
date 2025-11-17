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
#include "cSprite.h"

class cSmallBox :
	public cSprite
{
public:
	enum Layout : unsigned short
	{
		ONE_LEFT = 1,
		ONE_RIGHT = 2,
		ONE_LEFT_ONE_RIGHT = 3,
		TWO_LEFT = 4,
		TWO_RIGHT = 5,
		TWO_LEFT_ONE_RIGHT = 6,
		ONE_LEFT_TWO_RIGHT = 7,
		TWO_LEFT_TWO_RIGHT = 8
	};
	cSmallBox(double x, double y);
	~cSmallBox();

	virtual void Update(double interval, double gravity);

private:
	static STRING IMAGE_FILE_PATH;
};