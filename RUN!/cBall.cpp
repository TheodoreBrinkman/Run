#include "cBall.h"

// STATIC INITIALIZATIONS
LPTSTR cBall::AUDIO_FILE = TEXT(".\\Audio\\bounce.wav");
LPTSTR cBall::IMAGE_FILE = TEXT(".\\Images\\Ball.bmp");

// CONSTRUCTORS
cBall::cBall(cRect *limits)
	: cImage(cBall::IMAGE_FILE, new cColor(255,0,255))
{
	this->_limits = limits->Copy();

	this->_size = this->_canvas->Size()->Copy();
	this->_GoToStartingPosition();

	this->_speed = 50;
	this->_movingLeft = false;
	this->_movingUp = true;
	// Initialize frames
	this->_frames.insert(this->_frames.end(), new cRect(0, 0, (unsigned long)this->_size->Right, (unsigned long)this->_size->Bottom));
	cAudioManager::RegisterSound(cBall::AUDIO_FILE);
}

cBall::~cBall()
{
//	cGraphicsManager::ReleaseCanvas(cBall::IMAGE_FILE);
	cAudioManager::ReleaseSound(cBall::AUDIO_FILE);
}

void cBall::Update(unsigned long interval)
{
	this->_UpdateLocation(interval);
	cRect *pos = this->_size->Copy();
	pos->ShiftTo(this->_position.x, this->_position.y);
	cGraphicsManager::Draw(pos, this->_canvas, this->_size);
}

cRect* cBall::CollisionBox()
{
	cRect *cb = this->_size->Copy();
	cb->ShiftTo(this->_position.x, this->_position.y);
	return(cb);
}

bool cBall::CheckCollision(cRect *collisionBox)
{
	cRect *cb = this->CollisionBox();
	bool hitTop = false;
	bool hitLeft = false;
	bool hitRight = false;
	bool hitBottom = false;
	bool collision = false;
	if(this->_movingUp)
	{
		if(collisionBox->Contains((cb->Left + cb->Right) / 2, cb->Top))
		{
			this->_movingUp = false;
			collision = true;
		}
	}
	else
	{
		if(collisionBox->Contains((cb->Left + cb->Right) / 2, cb->Bottom))
		{
			this->_movingUp = true;
			collision = true;
		}
	}
	if(this->_movingLeft)
	{
		if(collisionBox->Contains(cb->Left, (cb->Top + cb->Bottom) / 2))
		{
			this->_movingLeft = false;
			collision = true;
		}
	}
	else
	{
		if(collisionBox->Contains(cb->Right, (cb->Top + cb->Bottom) / 2))
		{
			this->_movingLeft = true;
			collision = true;
		}
	}
	if(collision)
	{
		cAudioManager::Play(cBall::AUDIO_FILE);
	}
	return(collision);
}

void cBall::_UpdateLocation(unsigned long interval)
{
	double xDiff = (double)this->_speed * (double)(interval/1000.0);
	double yDiff = xDiff;
	bool collision = false;
	if(this->_movingLeft)
	{
		this->_position.x -= xDiff;
		if(this->_position.x <= this->_limits->Left)
		{
			this->_position.x += this->_limits->Left - this->_position.x;
			this->_movingLeft = false;
			collision = true;
		}
	}
	else
	{
		this->_position.x += xDiff;
		double rightEdge = this->_position.x + this->_size->Right;
		if(rightEdge >= this->_limits->Right)
		{
			this->_position.x -= rightEdge - this->_limits->Right;
			this->_movingLeft = true;
			collision = true;
		}
	}
	if(this->_movingUp)
	{
		this->_position.y -= yDiff;
		if(this->_position.y <= this->_limits->Top)
		{
			this->_position.y += this->_limits->Top - this->_position.y;
			this->_movingUp = false;
			collision = true;
		}
	}
	else
	{
		this->_position.y += yDiff;
		double bottomEdge = this->_position.y + this->_size->Bottom;
		if(bottomEdge >= this->_limits->Bottom)
		{
			this->_position.y -= bottomEdge - this->_limits->Bottom;
			this->_movingUp = true;
			collision = true;
		}
	}
	if(collision)
	{
		cAudioManager::Play(cBall::AUDIO_FILE);
	}
}

void cBall::_GoToStartingPosition()
{
	this->_position.x = (this->_limits->Right - this->_limits->Left - this->_size->Right) / 2;
	this->_position.y = (this->_limits->Bottom - this->_limits->Top - this->_size->Bottom) / 2;
}

cRect* cBall::_CurrentFrame()
{
	return(this->_frames.at(0));
}