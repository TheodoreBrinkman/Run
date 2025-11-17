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
#include "cAvatar.h"

// STATIC INITIALIZATION
STRING cAvatar::IMAGE_FILE_PATH = TEXT("./Images/Avatar.png");

unsigned long cAvatar::ANIMATION_STAND_COUNT = 1;
unsigned long cAvatar::ANIMATION_STAND_START = 0;
unsigned long cAvatar::ANIMATION_RUN_COUNT = 8;
unsigned long cAvatar::ANIMATION_RUN_START = cAvatar::ANIMATION_STAND_START + cAvatar::ANIMATION_STAND_COUNT;
unsigned long cAvatar::SPEED_RUN = 64 * 8;				// 8m/s (average human running speed) * 64px/tile * 1 tile/m
unsigned long cAvatar::ANIMATION_WALK_COUNT = 8;
unsigned long cAvatar::ANIMATION_WALK_START = cAvatar::ANIMATION_RUN_START + cAvatar::ANIMATION_RUN_COUNT;
unsigned long cAvatar::SPEED_WALK = cAvatar::SPEED_RUN / 2;
unsigned long cAvatar::ANIMATION_CLIMB_COUNT = 2;
unsigned long cAvatar::ANIMATION_CLIMB_START = cAvatar::ANIMATION_WALK_START + cAvatar::ANIMATION_WALK_COUNT;
unsigned long cAvatar::SPEED_CLIMB = 320;
unsigned long cAvatar::ANIMATION_JUMP_COUNT = 1;
unsigned long cAvatar::ANIMATION_JUMP_START = cAvatar::ANIMATION_CLIMB_START + cAvatar::ANIMATION_CLIMB_COUNT;
double cAvatar::JUMP_VELOCITY = 10;
//unsigned long cAvatar::ANIMATION_LIFT_COUNT = 8;
//unsigned long cAvatar::ANIMATION_LIFT_START = 17;
//unsigned long cAvatar::ANIMATION_CARRY_COUNT = 8;
//unsigned long cAvatar::ANIMATION_CARRY_START = 25;
//unsigned long cAvatar::ANIMATION_PUSH_COUNT = 8;
//unsigned long cAvatar::ANIMATION_PUSH_START = 41;
//unsigned long cAvatar::ANIMATION_CRAWL_COUNT = 4;
//unsigned long cAvatar::ANIMATION_CRAWL_START = 49;
//unsigned long cAvatar::ANIMATION_HOIST_COUNT = 4;
//unsigned long cAvatar::ANIMATION_HOIST_START = 57;
//unsigned long cAvatar::ANIMATION_DIE_COUNT = 4;
//unsigned long cAvatar::ANIMATION_DIE_START = 61;

// CONSTRUCTORS
cAvatar::cAvatar(double x, double y)
	: cAnimatedSprite(cAvatar::IMAGE_FILE_PATH)
{
	this->_Init();
	this->_position.x = x;
	this->_position.y = y;
	this->_hasMass = true;
	this->_currentAnimation = cAvatar::ANIMATION_STAND_KEY;
	this->_inAir = false;
	this->_pushing = false;
	this->_onLadder = false;
}

// DESTRUCTOR
cAvatar::~cAvatar()
{
	cGraphicsManager::ReleaseSpriteSheet(cAvatar::IMAGE_FILE_PATH);
}

// PUBLIC METHODS
void cAvatar::SetPosition(POINT2D position)
{
	this->_position.x = position.x;
	this->_position.y = position.y;
}
void cAvatar::OnLadder(bool onLadder)
{
	this->_onLadder = onLadder;
}
std::pair<cRect*,cRect*> cAvatar::CollisionBox()
{
	std::pair<cRect*,cRect*> cb = cSprite::CollisionBox();
	// vertical box
	double hPad = ((cb.first->Width() - 16) / 2);
	cb.first->Top += 16;			// align to the avatar's head to give more jump room
	cb.first->Left += hPad;
	cb.first->Right -= hPad;
	// horizontal box
	cb.second->Top += 24;
	cb.second->Bottom -= 32;	// the maximum rise the avatar can step onto
	return(cb);
}
void cAvatar::Update(double interval, double gravity)
{
	double speed = 0.0;
	bool left = cInputManager::KeyDown(Input::KEY_LEFT);
	bool right = cInputManager::KeyDown(Input::KEY_RIGHT);
	bool up = cInputManager::KeyDown(Input::KEY_UP);
	bool down = cInputManager::KeyDown(Input::KEY_DOWN);
	bool action = cInputManager::KeyDown(Input::KEY_LSHIFT);
	bool jump = cInputManager::KeyDown(Input::KEY_SPACE) && !cInputManager::KeyHeld(Input::KEY_SPACE);

	cAnimatedSprite::Update(interval, gravity);
	// don't fall when on a ladder
	if(this->_onLadder)
	{
		this->_velocity.y = 0.0;
		if(up)
		{
			this->_currentAnimation = cAvatar::ANIMATION_CLIMB_KEY;
			this->_velocity.y = -(cAvatar::SPEED_CLIMB * interval);
		}
		else if(down)
		{
			this->_currentAnimation = cAvatar::ANIMATION_CLIMB_KEY;
			this->_velocity.y = (cAvatar::SPEED_CLIMB * interval);
		}
		else
		{
			this->_currentAnimation = cAvatar::ANIMATION_STAND_KEY;
		}
	}

//#ifdef _DEBUG
//	if(cInputManager::KeyPress(KEY_G))
//	{
//		this->_hasMass = !this->_hasMass;
//	}
//	right = true;
//#endif
	if(left || right)
	{
		this->_currentAnimation = cAvatar::ANIMATION_RUN_KEY;
//		this->_currentAnimation = cAvatar::ANIMATION_WALK_KEY;
	}
	else
	{
		if(!this->_onLadder)
		{
			this->_currentAnimation = cAvatar::ANIMATION_STAND_KEY;
		}
		this->_velocity.x = 0.0;
	}

	switch(this->_currentAnimation)
	{
		case cAvatar::ANIMATION_RUN_KEY:
			speed = cAvatar::SPEED_RUN * interval;
			break;
		case cAvatar::ANIMATION_WALK_KEY:
			speed = cAvatar::SPEED_WALK * interval;
			break;
		case cAvatar::ANIMATION_STAND_KEY:
		default:
			speed = 0.0;
			break;
	}
	if(this->_inAir)
	{
		this->_currentAnimation = cAvatar::ANIMATION_JUMP_KEY;
	}
	if(left)
	{
		this->_velocity.x = -speed;
		this->_flipped = true;
	}
	else if(right)
	{
		this->_velocity.x = speed;
		this->_flipped = false;
	}
	if(jump && !this->_inAir)
	{
		this->_velocity.y -= cAvatar::JUMP_VELOCITY;// * interval;
		this->_inAir = true;
	}
}

void cAvatar::TileCollision(std::pair<cRect*,cRect*> intersect)
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
			this->_position.x = (hBox->Right - pBox->Width());
		}
		else if(this->_velocity.x < 0)	// Moving Left
		{
			this->_velocity.x = 0.0;
			this->_position.x = hBox->Left - 2;// where is this -2 offset coming from?
		}
	}
}

void cAvatar::ObjectCollision(std::pair<cRect*,cRect*> intersect, IObject *object)
{
	cRect *pBox = this->PositionBox();	// position during prior frame
	cRect *vBox = intersect.first;		// vertical collision box
	cRect *hBox = intersect.second;		// horizontal collision box

	// Handle Vertical Collisions
	if(NULL != vBox)
	{
		if(this->_velocity.y >= 0)	// Moving Down
		{
			if(NULL == hBox || vBox->Bottom > hBox->Bottom)	// vertical collision 'shorter' than maximum 'climbable' distance
			{
				this->_velocity.y = 0.0;	// halt downward movement
				this->_position.y = ((vBox->Bottom) - pBox->Height());
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
			this->_position.x = (hBox->Right - pBox->Width());
		}
		else if(this->_velocity.x < 0)	// Moving Left
		{
			this->_velocity.x = 0.0;
			this->_position.x = hBox->Left - 2;
		}
	}
}

// PRIVATE METHODS
void cAvatar::_Init()
{
	double frameRate = (1.0 / 15.0);
	unsigned long leftEdge = 0;
	unsigned long topEdge = 0;
	unsigned long frameWidth = 64;
	unsigned long frameHeight = 128;
	this->_AddAnimationData(cAvatar::ANIMATION_STAND_KEY, cAvatar::ANIMATION_STAND_START, cAvatar::ANIMATION_STAND_COUNT, frameRate);
	this->_frames.push_back(new cRect(topEdge, leftEdge, frameWidth, frameHeight));
	leftEdge += (cAvatar::ANIMATION_STAND_COUNT * frameWidth);

	this->_AddAnimationData(cAvatar::ANIMATION_RUN_KEY, cAvatar::ANIMATION_RUN_START, cAvatar::ANIMATION_RUN_COUNT, frameRate);
	frameWidth = 86;
	for(unsigned long i=0;i<cAvatar::ANIMATION_RUN_COUNT;i++)
	{
		unsigned long left = leftEdge + (i * frameWidth);
		this->_frames.push_back(new cRect(topEdge, left, left + frameWidth, frameHeight));
	}
	leftEdge += (cAvatar::ANIMATION_RUN_COUNT * frameWidth);

	this->_AddAnimationData(cAvatar::ANIMATION_WALK_KEY, cAvatar::ANIMATION_WALK_START, cAvatar::ANIMATION_WALK_COUNT, frameRate);
	frameWidth = 64;
	for(unsigned long i=0;i<cAvatar::ANIMATION_WALK_COUNT;i++)
	{
		unsigned long left = leftEdge + (i * frameWidth);
		this->_frames.push_back(new cRect(topEdge, left, left + frameWidth, frameHeight));
	}
	leftEdge += (cAvatar::ANIMATION_WALK_COUNT * frameWidth);

	frameWidth = 64;
	this->_AddAnimationData(cAvatar::ANIMATION_CLIMB_KEY, cAvatar::ANIMATION_CLIMB_START, cAvatar::ANIMATION_CLIMB_COUNT, 1.0 / 10.0);
	for(unsigned long i=0;i<cAvatar::ANIMATION_CLIMB_COUNT;i++)
	{
		unsigned long left = leftEdge + (i * frameWidth);
		this->_frames.push_back(new cRect(topEdge, left, left + frameWidth, frameHeight));
	}
	leftEdge += (cAvatar::ANIMATION_CLIMB_COUNT * frameWidth);

	frameWidth = 64;
	this->_AddAnimationData(cAvatar::ANIMATION_JUMP_KEY, cAvatar::ANIMATION_JUMP_START, cAvatar::ANIMATION_JUMP_COUNT, frameRate);
	for(unsigned long i=0;i<cAvatar::ANIMATION_JUMP_COUNT;i++)
	{
		unsigned long left = leftEdge + (i * frameWidth);
		this->_frames.push_back(new cRect(topEdge, left, left + frameWidth, frameHeight));
	}
	leftEdge += (cAvatar::ANIMATION_JUMP_COUNT * frameWidth);

//	this->_AddAnimationData(cAvatar::ANIMATION_LIFT_KEY, cAvatar::ANIMATION_RUN_START, cAvatar::ANIMATION_RUN_COUNT, frameRate);
//	this->_AddAnimationData(cAvatar::ANIMATION_CARRY_KEY, cAvatar::ANIMATION_RUN_START, cAvatar::ANIMATION_RUN_COUNT, frameRate);
//	this->_AddAnimationData(cAvatar::ANIMATION_PUSH_KEY, cAvatar::ANIMATION_RUN_START, cAvatar::ANIMATION_RUN_COUNT, frameRate);
//	this->_AddAnimationData(cAvatar::ANIMATION_CRAWL_KEY, cAvatar::ANIMATION_RUN_START, cAvatar::ANIMATION_RUN_COUNT, frameRate);
//	this->_AddAnimationData(cAvatar::ANIMATION_HOIST_KEY, cAvatar::ANIMATION_RUN_START, cAvatar::ANIMATION_RUN_COUNT, frameRate);
//	this->_AddAnimationData(cAvatar::ANIMATION_DIE_KEY, cAvatar::ANIMATION_RUN_START, cAvatar::ANIMATION_RUN_COUNT, frameRate);
}