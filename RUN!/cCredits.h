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
#include "cScrollingText.h"

class cCredits :
	public cScrollingText
{
public:
	// Constructors
	cCredits(unsigned long width, unsigned long height, double speed);
	// Destructors
	~cCredits();

private:
	static STRING CREDITS_FILE_PATH;
};