#include "cPaddle.h"

cPaddle::cPaddle(cRect *limits)
	: cImage(TEXT(".\\Images\\Paddle.bmp"), new cColor(255,0,255))
{
	this->_limits = limits->Copy();

	this->_size = this->_canvas->Size()->Copy();
	this->_GoToStartingPosition();
	this->_speed = 75;

	// Insert Frames
	this->_frames.insert(this->_frames.end(), new cRect(0, 0, (unsigned long)this->_size->Right, (unsigned long)this->_size->Bottom));
}

cPaddle::~cPaddle()
{
}

void cPaddle::Update(unsigned long interval)
{
	this->_UpdateLocation(interval);
	cRect *pos = this->_size->Copy();
	pos->ShiftTo(this->_position.x, this->_position.y);
	cGraphicsManager::Draw(pos, this->_canvas, this->_size);
}

cRect* cPaddle::CollisionBox()
{
	cRect *cb = this->_size->Copy();
	cb->ShiftTo(this->_position.x, this->_position.y);
	return(cb);
}

void cPaddle::_UpdateLocation(unsigned long interval)
{
	double xDiff = (double)this->_speed * (double)(interval/1000.0);
	if(cInputManager::KeyDown(KEY_RIGHT))
	{
		this->_position.x += xDiff;
	}
	if(cInputManager::KeyDown(KEY_LEFT))
	{
		this->_position.x -= xDiff;
	}
	double rightEdge = this->_position.x + this->_size->Right;
	if(rightEdge >= this->_limits->Right)
	{
		this->_position.x = this->_limits->Right - this->_size->Right;
	}
	if(this->_position.x <= this->_limits->Left)
	{
		this->_position.x = 0;
	}
}

void cPaddle::_GoToStartingPosition()
{
	this->_position.x = (this->_limits->Right - this->_limits->Left - this->_size->Right) / 2;
	this->_position.y = this->_limits->Bottom - (this->_size->Bottom * 2);
}

cRect* cPaddle::_CurrentFrame()
{
	return(this->_frames.at(0));
}