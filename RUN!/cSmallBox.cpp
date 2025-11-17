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
#include "cSmallBox.h"

// STATIC INITIALIZATION
STRING cSmallBox::IMAGE_FILE_PATH = TEXT("./Images/SmallBox.png");

// CONSTRUCTORS
cSmallBox::cSmallBox(double x, double y)
	: cSprite(cSmallBox::IMAGE_FILE_PATH)
{
	this->_position.x = x;
	this->_position.y = y;
	this->_velocity.x = 0;
	this->_velocity.y = 0;
	this->_hasMass = false;//true;
}

// DESTRUCTOR
cSmallBox::~cSmallBox()
{
	cGraphicsManager::ReleaseSpriteSheet(cSmallBox::IMAGE_FILE_PATH);
}

// PUBLIC METHODS
void cSmallBox::Update(double interval, double gravity)
{
	cSprite::Update(interval, gravity);
}