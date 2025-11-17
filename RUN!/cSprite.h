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
#include <stdlib.h>
#include <map>
#include "TYPEDEFS.h"
#include "cGraphicsManager.h"
#include "cImage.h"
#include "IObject.h"
#include "cRect.h"

class cSprite :
	public cImage, public IObject
{
public:
	// Constructors
	cSprite(STRING imageFilePath);
	cSprite(STRING imageFilePath, cColor *transparentColor);
	// Destructor
	virtual ~cSprite();

	// Methods
	void Initialize(POINT2D position);
	virtual std::pair<cRect*,cRect*> CollisionBox();
	virtual cRect* PositionBox();
	virtual POINT2D Position();
	virtual POINT2D Velocity();
	virtual void SetVelocityX(double velocity);
	virtual void SetVelocityY(double velocity);
	virtual void Update(double interval, double gravity);
	virtual void TileCollision(std::pair<cRect*,cRect*> intersect);
	virtual void ObjectCollision(std::pair<cRect*,cRect*> intersect, IObject *object);
	virtual void Draw(cRect *destRect);

protected:
	POINT2D _position;
	POINT2D _velocity;
	bool _hasMass;
	bool _checkCollisions;
	bool _flipped;
	bool _inAir;

	virtual void _Init();
	virtual cRect* CurrentFrame();
};