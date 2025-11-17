#include "cBlock.h"

cBlock::cBlock(POINT2D position)
	: cImage(TEXT(".\\Images\\Brick.bmp"))
{
	this->_size = this->_canvas->Size()->Copy();
	this->_position = position;
	this->Reset();

	// Initialize frames
	this->_frames.insert(this->_frames.end(), new cRect(0, 0, (unsigned long)this->_size->Right, (unsigned long)this->_size->Bottom));
}

cBlock::~cBlock()
{
}

cRect* cBlock::CollisionBox()
{
	cRect *cb = this->_size->Copy();
	cb->ShiftTo(this->_position.x, this->_position.y);
	return(cb);
}

bool cBlock::IsLive()
{
	return(this->_live);
}

void cBlock::Update()
{
	if(this->_live)
	{
		cRect *pos = this->_size->Copy();
		pos->ShiftTo(this->_position.x, this->_position.y);
		cGraphicsManager::Draw(pos, this->_canvas, this->_CurrentFrame());
	}
}

void cBlock::Kill()
{
	this->_live = false;
}

void cBlock::Reset()
{
	this->_live = true;
}

cRect* cBlock::_CurrentFrame()
{
	return(this->_frames.at(0));
}