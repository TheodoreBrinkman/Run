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
#include <windows.h>
#include <stdlib.h>
#include "cRect.h"

class IObject
{
#pragma message("-- IObject is included")
public:
	// Methods
	virtual std::pair<cRect*,cRect*> CollisionBox() = 0;
	virtual cRect* PositionBox() = 0;
	virtual POINT2D Position() = 0;
	virtual POINT2D Velocity() = 0;
	virtual void SetVelocityX(double velocity) = 0;
	virtual void SetVelocityY(double velocity) = 0;
	virtual void Update(double interval, double gravity) = 0;
	virtual void TileCollision(std::pair<cRect*,cRect*> intersect) = 0;
	virtual void ObjectCollision(std::pair<cRect*,cRect*> intersect, IObject *object) = 0;
	virtual void Draw(cRect *destRect) = 0;
	// Destructor
	virtual ~IObject(){};

private:
	virtual cRect* CurrentFrame() = 0;
};