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
#include <windows.h>

class cTimer
{
public:
	cTimer();
	~cTimer();

	void Update();
	double GetTime();
	void Wait(double seconds);

private:
	bool performance_timer;				// Using The Performance Timer?
	double resolution;					// Timer Resolution
	__int64 frequency;					// Timer Frequency
	__int64 performance_timer_start;	// Performance Timer Start Value
	__int64 performance_timer_elapsed;	// Performance Timer Elapsed Time
	unsigned long mm_timer_start;		// Multimedia Timer Start Value
	unsigned long mm_timer_elapsed;		// Multimedia Timer Elapsed Time

	void _Init();						// Initialize the class
};