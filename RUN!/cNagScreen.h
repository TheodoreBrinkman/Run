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

class cNagScreen :
	public cScrollingText
{
public:
	// Constructors
	cNagScreen(unsigned long width, unsigned long height, double speed);
	// Destructors
	~cNagScreen();

private:
	static STRING NAG_FILE_PATH;
};