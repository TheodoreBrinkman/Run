#include "cWinMessage.h"

// CONSTRUCTOR
cWinMessage::cWinMessage(unsigned long xLimit, unsigned long yLimit)
	: cImage(TEXT("./Images/Win.bmp"), new cColor(255,0,255))
{
	this->_size = this->_canvas->Size()->Copy();
	this->_position.x = (xLimit - this->_size->Right) / 2;
	this->_position.y = (yLimit - this->_size->Bottom) / 2;
	// Initialize frames
	this->_frames.insert(this->_frames.end(), new cRect(0, 0, (unsigned long)this->_size->Right, (unsigned long)this->_size->Bottom));
}

// DESTRUCTOR
cWinMessage::~cWinMessage()
{
}

// PUBLIC METHODS
void cWinMessage::Update()
{
	cRect *pos = this->_size->Copy();
	pos->ShiftTo(this->_position.x, this->_position.y);
	cGraphicsManager::Draw(pos, this->_canvas, this->_size);
}