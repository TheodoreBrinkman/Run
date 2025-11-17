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
#include "cScoreScreen.h"

// CONSTRUCTORS
cScoreScreen::cScoreScreen(unsigned long width, unsigned long height, double speed)
	: cScrollingText(width, height, speed)
{
}

// DESTRUCTOR
cScoreScreen::~cScoreScreen()
{
}

// PUBLIC METHODS
void cScoreScreen::SetScore(double time, unsigned long lives, unsigned long secrets)
{
	long creatureMultiplier = 1;
	long score = (long)((time * 1000) + (lives * lives * 100) - (secrets * 10000));
	this->_lines.clear();
	this->_lines.push_back(TEXT("RUN!"));
	this->_lines.push_back(TEXT(""));
	this->_lines.push_back(TEXT("Time - ") + this->_NumToStr(time) + TEXT(" seconds"));
	this->_lines.push_back(TEXT("Lives -") + this->_NumToStr(lives));
	this->_lines.push_back(TEXT("Secrets - ") + this->_NumToStr(secrets));
	this->_lines.push_back(TEXT(""));
	this->_lines.push_back(TEXT("Creature Multiplier - *") + this->_NumToStr(creatureMultiplier));
	this->_lines.push_back(TEXT("Total Score - ") + this->_NumToStr(score));
}

STRING cScoreScreen::_NumToStr(double number)
{
	unsigned long integer = (unsigned long)number;
	unsigned long decimal = (unsigned long)((number - integer) * 1000);
	STRINGSTREAM ss;
	ss << integer << "." << decimal;
	return(ss.str());
}

STRING cScoreScreen::_NumToStr(unsigned long number)
{
	STRINGSTREAM ss;
	ss << number;
	return(ss.str());
}

STRING cScoreScreen::_NumToStr(long number)
{
	STRINGSTREAM ss;
	ss << number;
	return(ss.str());
}