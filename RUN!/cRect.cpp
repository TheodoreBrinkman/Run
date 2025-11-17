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
#include "cRect.h"

// CONSTRUCTORS
cRect::cRect()
{
	this->_Init(0, 0, 0, 0);
}

cRect::cRect(long width, long height)
{
	this->_Init(0, 0, width, height);
}

cRect::cRect(long top, long left, long right, long bottom)
{
	this->_Init(top, left, right, bottom);
}

// DESTRUCTORS
cRect::~cRect()
{
}

// PUBLIC METHODS
double cRect::Width()
{
	return(this->Right - this->Left);
}
double cRect::Height()
{
	return(this->Bottom - this->Top);
}
POINT2D cRect::Center()
{
	POINT2D center;
	center.x = (this->Left + this->Right) / 2;
	center.y = (this->Top + this->Bottom) / 2;
	return(center);
}
void cRect::Shift(long xOffset, long yOffset)
{
	this->Shift((double)xOffset, (double)yOffset);
}
void cRect::Shift(double xOffset, double yOffset)
{
	this->Top += yOffset;
	this->Left += xOffset;
	this->Right += xOffset;
	this->Bottom += yOffset;
}

void cRect::ShiftTo(long xLoc, long yLoc)
{
	this->ShiftTo((double)xLoc, (double)yLoc);
}
void cRect::ShiftTo(double xLoc, double yLoc)
{
	double xOffset = xLoc - this->Left;
	double yOffset = yLoc - this->Top;
	this->Shift(xOffset, yOffset);
}
void cRect::ShiftTo(POINT2D position)
{
	this->ShiftTo(position.x, position.y);
}
void cRect::TrimLeft(double width)
{
	this->Left += width;
}
void cRect::TrimRight(double width)
{
	this->Right -= width;
}
void cRect::TrimTop(double height)
{
	this->Top += height;
}
void cRect::TrimBottom(double height)
{
	this->Bottom -= height;
}

cRect* cRect::Copy()
{
	cRect *newRect = new cRect();
	newRect->Top = this->Top;
	newRect->Left = this->Left;
	newRect->Right = this->Right;
	newRect->Bottom = this->Bottom;
	return(newRect);
}

cRect* cRect::Copy(cRect* rect)
{
	return(rect->Copy());
}

bool cRect::Contains(POINT2D point)
{
	return(this->Contains(point.x, point.y));
}
bool cRect::Contains(double x, double y)
{
	return(x >= this->Left && x <= this->Right && y >= this->Top && y <= this->Bottom);
}
cRect* cRect::Intersects(cRect *rect)
{
	return(cRect::Intersects(this, rect));
}
cRect* cRect::Intersects(cRect *rect1, cRect *rect2)
{
	if(NULL != rect1 && NULL != rect2)
	{
		if(!(rect1->Left > rect2->Right || rect1->Right < rect2->Left || rect1->Top > rect2->Bottom || rect1->Bottom < rect2->Top))
		{
			bool top = rect1->Top > rect2->Top && rect1->Top < rect2->Bottom;
			bool left = rect1->Left > rect2->Left && rect1->Left < rect2->Right;
			bool right = rect1->Right < rect2->Right && rect2->Right > rect2->Left;
			bool bottom = rect1->Bottom < rect2->Bottom && rect1->Bottom > rect2->Top;
			bool vSpan = rect1->Top <= rect2->Top && rect1->Bottom >= rect2->Bottom;
			bool hSpan = rect1->Left <= rect2->Left && rect1->Right >= rect2->Right;

			cRect* cBox = rect1->Copy();
			if(top && (left || right || hSpan))
			{
				// top collision
				cBox->Top = rect2->Bottom;
			}
			if(left && (top || bottom || vSpan))
			{
				// left collision
				cBox->Left = rect2->Right;
			}
			if(right && (top || bottom || vSpan))
			{
				// right collision
				cBox->Right = rect2->Left;
			}
			if(bottom && (left || right || hSpan))
			{
				// bottom collision
				cBox->Bottom = rect2->Top;
			}
			return(cBox);
			//unsigned long top = (unsigned long)((rect1->Top > rect2->Top) ? rect1->Top : rect2->Top);
			//unsigned long left = (unsigned long)((rect1->Left > rect2->Left) ? rect1->Left : rect2->Left);
			//unsigned long right = (unsigned long)((rect1->Right < rect2->Right) ? rect1->Right : rect2->Right);
			//unsigned long bottom = (unsigned long)((rect1->Bottom < rect2->Bottom) ? rect1->Bottom : rect2->Bottom);
			//return(new cRect(top, left, right, bottom));
		}
	}
	return(NULL);
}

// PRIVATE METHODS
void cRect::_Init(long top, long left, long right, long bottom)
{
	this->Top = (double)top;
	this->Left = (double)left;
	this->Right = (double)right;
	this->Bottom = (double)bottom;
}