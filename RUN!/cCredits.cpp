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
#include "cCredits.h"

// STATIC INITIALIZATION
STRING cCredits::CREDITS_FILE_PATH = TEXT("./Credits.txt");

// CONSTRUCTORS
cCredits::cCredits(unsigned long width, unsigned long height, double speed)
	: cScrollingText(width, height, speed)
{
	this->LoadText(CREDITS_FILE_PATH);
}

// DESTRUCTOR
cCredits::~cCredits()
{
}

// PUBLIC METHODS
