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
#include "cNagScreen.h"

// STATIC INITIALIZATION
STRING cNagScreen::NAG_FILE_PATH = TEXT("./Nag.txt");

// CONSTRUCTORS
cNagScreen::cNagScreen(unsigned long width, unsigned long height, double speed)
	: cScrollingText(width, height, speed)
{
	this->LoadText(NAG_FILE_PATH);
}

// DESTRUCTOR
cNagScreen::~cNagScreen()
{
}
