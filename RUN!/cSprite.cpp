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
#include "cSprite.h"

// CONSTRUCTORS
cSprite::cSprite(STRING imageFilePath) : cImage(imageFilePath)
{
	this->_Init();
}

cSprite::cSprite(STRING imageFilePath, cColor *transparentColor) : cImage(imageFilePath, transparentColor)
{
	this->_Init();
}

// DESTRUCTOR
cSprite::~cSprite()
{
	this->_canvas->Release();
}

// PUBLIC METHODS
void cSprite::Initialize(POINT2D position)
{
	this->_position = position;
}

void cSprite::Update(double interval, double gravity)
{
	// apply gravity
	if(this->_hasMass)
	{
		//double d=(this->_velocity.y * interval) + gravity;
		//this->_velocity.y += d;
		this->_velocity.y += gravity;
	}
}

void cSprite::TileCollision(std::pair<cRect*,cRect*> intersect)
{
	cRect *pBox = this->PositionBox();	// position during prior frame
	cRect *vBox = intersect.first;		// vertical collision box
	cRect *hBox = intersect.second;		// horizontal collision box
	// Handle Vertical Collisions
	if(NULL != vBox)
	{
		if(this->_velocity.y > 0)	// Moving Down
		{
			if(NULL == hBox || vBox->Bottom < hBox->Bottom)	// vertical collision 'shorter' than maximum 'climbable' distance
			{
				this->_velocity.y = 0.0;	// halt downward movement
				this->_position.y = (vBox->Bottom - pBox->Height());
//				this->_position.y -= (pBox->Bottom - vBox->Top);
				this->_inAir = false;
			}
		}
		else if(this->_velocity.y < 0)	// Moving Up
		{
			if(NULL == hBox)
			{
				this->_velocity.y = 0.0;
				this->_position.y = vBox->Top;
//				this->_position.y += (vBox->Bottom - pBox->Top);
			}
		}
	}

	// Handle Horizontal Collisions
	if(NULL != hBox)
	{
		if(this->_velocity.x > 0)	// Moving Right
		{
			this->_velocity.x = 0.0;	// halt the 
			this->_position.x = (hBox->Right - pBox->Width());// + 40;	// where is this +40 offset coming from?
		}
		else if(this->_velocity.x < 0)	// Moving Left
		{
			this->_velocity.x = 0.0;
			this->_position.x = hBox->Left;// - 42;	// where is this -42 offset coming from?
//			this->_position.x += (pBox->Left - hBox->Left);
		}
	}
}
void cSprite::ObjectCollision(std::pair<cRect*,cRect*> intersect, IObject *object)
{
	cRect *pBox = this->PositionBox();	// position during prior frame
	cRect *vBox = intersect.first;		// vertical collision box
	cRect *hBox = intersect.second;		// horizontal collision box

	// Handle Vertical Collisions
	if(NULL != vBox)
	{
		if(this->_velocity.y > 0)	// Moving Down
		{
			if(NULL == hBox || vBox->Bottom < hBox->Bottom)	// vertical collision 'shorter' than maximum 'climbable' distance
			{
				this->_velocity.y = 0.0;	// halt downward movement
				this->_position.y = (vBox->Bottom - pBox->Height());
				this->_inAir = false;
			}
		}
		else if(this->_velocity.y < 0)	// Moving Up
		{
			if(NULL == hBox)
			{
				this->_velocity.y = 0.0;
				this->_position.y = vBox->Top;
			}
			else if(vBox->Bottom < hBox->Bottom)
			{
				this->_velocity.y = 0.0;	
				this->_position.y += (vBox->Bottom - pBox->Top);
			}
		}
	}
	// Handle Horizontal Collisions
	if(NULL != hBox)
	{
		if(this->_velocity.x > 0)	// Moving Right
		{
			this->_velocity.x = 0.0;
			this->_position.x = (hBox->Right - pBox->Width());// + 40;	// where is this +40 offset coming from?
		}
		else if(this->_velocity.x < 0)	// Moving Left
		{
			this->_velocity.x = 0.0;
			this->_position.x = hBox->Left;// - 42;	// where is this -42 offset coming from?
		}
	}
}

cRect* cSprite::PositionBox()
{
	cRect* box = this->CurrentFrame()->Copy();
	box->ShiftTo(this->_position);
	return(box);
}
std::pair<cRect*,cRect*> cSprite::CollisionBox()
{
	cRect* vBox = this->PositionBox();
//	vBox->Shift(this->_velocity.x, this->_velocity.y);
	cRect* hBox = vBox->Copy();
	vBox->Shift(0.0, this->_velocity.y);
	hBox->Shift(this->_velocity.x, 0.0);
	return(std::pair<cRect*,cRect*>(vBox,hBox));
}

POINT2D cSprite::Position()
{
	return(this->_position);
}

POINT2D cSprite::Velocity()
{
	return(this->_velocity);
}

void cSprite::SetVelocityX(double velocity)
{
	this->_velocity.x = velocity;
}

void cSprite::SetVelocityY(double velocity)
{
	this->_velocity.y = velocity;
}

void cSprite::Draw(cRect *destRect)
{
	this->_position.x += this->_velocity.x;
	this->_position.y += this->_velocity.y;
	cGraphicsManager::Draw(destRect, this->_canvas, this->CurrentFrame(), this->_flipped);
}

// PROTECTED METHODS
cRect* cSprite::CurrentFrame()
{
	return(this->_canvas->Size());
}

// PRIVATE METHODS
void cSprite::_Init()
{
	this->_position.x = 0.0;
	this->_position.y = 0.0;
	this->_velocity.x = 0.0;
	this->_velocity.y = 0.0;
	this->_checkCollisions = false;
	this->_hasMass = false;
	this->_flipped = false;
}