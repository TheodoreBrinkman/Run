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
#include "stdlib.h"
#include "STRUCTURES.h"

class cRect
{
#pragma message("-- cRect is included")
public:
	double Top;
	double Left;
	double Right;
	double Bottom;

	cRect();
	cRect(long right, long bottom);
	cRect(long top, long left, long right, long bottom);

	double Height();
	double Width();
	POINT2D Center();

	void Shift(long xOffset, long yOffset);
	void Shift(double xOffset, double yOffset);
	void ShiftTo(long xLoc, long yLoc);
	void ShiftTo(double xLoc, double yLoc);
	void ShiftTo(POINT2D position);

	void TrimLeft(double width);
	void TrimRight(double width);
	void TrimTop(double height);
	void TrimBottom(double height);

	bool Contains(POINT2D point);
	bool Contains(double x, double y);
	cRect* Intersects(cRect *rect);

	cRect* Copy();
	static cRect* Copy(cRect *rect);
	static cRect* Intersects(cRect *rect1, cRect *rect2);

	~cRect();

private:
	void _Init(long top, long left, long right, long bottom);
};