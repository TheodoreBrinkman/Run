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
#include "cColor.h"

cColor::cColor()
{
	this->_Init(0, 0, 0, 0);
}

cColor::cColor(unsigned short red, unsigned short green, unsigned short blue)
{
	this->_Init(red, green, blue, 0);
}
cColor::cColor(unsigned short red, unsigned short green, unsigned short blue, unsigned short alpha)
{
	this->_Init(red, green, blue, alpha);
}

cColor::cColor(unsigned int color)
{
	unsigned short red = 0;
	unsigned short green = 0;
	unsigned short blue = 0;
	unsigned short alpha = 0;
	this->_Init(red, green, blue, alpha);
}

cColor::~cColor()
{
}

// PRIVATE METHODS
void cColor::_Init(unsigned short red, unsigned short green, unsigned short blue, unsigned short alpha)
{
	this->Red = red;
	this->Green = green;
	this->Blue = blue;
	this->Alpha = alpha;
}