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
#include "cScrollingText.h"
#include <sstream>

class cScoreScreen :
	public cScrollingText
{
public:
	cScoreScreen(unsigned long width, unsigned long height, double speed);
	~cScoreScreen();

	void SetScore(double time, unsigned long lives, unsigned long secrets);

private:
	STRING cScoreScreen::_NumToStr(double number);
	STRING cScoreScreen::_NumToStr(unsigned long number);
	STRING cScoreScreen::_NumToStr(long number);
};