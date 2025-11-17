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

class cColor
{
#pragma message("-- cColor is included")
public:
	unsigned short Red;
	unsigned short Green;
	unsigned short Blue;
	unsigned short Alpha;

	cColor();
	cColor(unsigned int color);
	cColor(unsigned short red, unsigned short green, unsigned short blue);
	cColor(unsigned short red, unsigned short green, unsigned short blue, unsigned short alpha);
	~cColor();

private:
	void _Init(unsigned short red, unsigned short green, unsigned short blue, unsigned short alpha);
};