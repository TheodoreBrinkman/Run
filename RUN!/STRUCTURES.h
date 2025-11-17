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
#pragma message("-- STRUCTURES is included")

struct POINT2D
{
	double x;
	double y;
};

struct ANIMATION_DATA
{
	unsigned long startFrame;
	unsigned long frameCount;
	double frameInterval;
};