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
#include "cMediumBox.h"

// STATIC INITIALIZATION
STRING cMediumBox::IMAGE_FILE_PATH = TEXT("./Images/MediumBox.png");

// CONSTRUCTORS
cMediumBox::cMediumBox(double x, double y)
	: cSprite(cMediumBox::IMAGE_FILE_PATH)
{
	this->_position.x = x;
	this->_position.y = y;
	this->_velocity.x = 0;
	this->_velocity.y = 0;
	this->_hasMass = false;//true;
}

// DESTRUCTOR
cMediumBox::~cMediumBox()
{
	cGraphicsManager::ReleaseSpriteSheet(cMediumBox::IMAGE_FILE_PATH);
}

// PUBLIC METHODS
void cMediumBox::Update(double interval, double gravity)
{
	cSprite::Update(interval, gravity);
}

std::pair<cRect*,cRect*> cMediumBox::CollisionBox()
{
	std::pair<cRect*,cRect*> cb = cSprite::CollisionBox();
	cb.first->Left += 4;
	cb.first->Right -= 4;
	cb.second->Top += 4;
	cb.second->Bottom -= 4;
	return(cb);
}