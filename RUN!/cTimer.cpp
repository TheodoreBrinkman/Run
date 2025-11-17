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
#include "cTimer.h"

cTimer::cTimer()
{
	this->_Init();
	timeBeginPeriod(1);
}

cTimer::~cTimer()
{
	timeEndPeriod(1);
}

// PUBLIC METHODS
double cTimer::GetTime()								// Get Time In Seconds
{
	__int64 time;								// time Will Hold A 64 Bit Integer

	if (this->performance_timer)						// Are We Using The Performance Timer?
	{
		QueryPerformanceCounter((LARGE_INTEGER *) &time);		// Grab The Current Performance Time
		// Return The Current Time Minus The Start Time Multiplied By The Resolution
		return ((double)(time - this->performance_timer_start) * this->resolution);
	}
	else
	{
		// Return The Current Time Minus The Start Time Multiplied By The Resolution And 1000 (To Get MS)
		return((double)(timeGetTime() - this->mm_timer_start) * this->resolution);
	}
}

void cTimer::Update()
{
	if (this->performance_timer)						// Are We Using The Performance Timer?
	{
		QueryPerformanceCounter((LARGE_INTEGER *) &this->performance_timer_start);		// Grab The Current Performance Time
	}
	else
	{
		this->mm_timer_start = timeGetTime();
	}
}

void cTimer::Wait(double seconds)
{
	if(this->performance_timer)
	{
		double end = this->GetTime() + seconds;
		while(this->GetTime() <= end - 2)
		{
			Sleep(1);
		}
		while(this->GetTime() <= end)
		{
		}
	}
	else
	{
		Sleep((DWORD)(seconds * 1000));
	}
	this->Update();
}

// PRIVATE METHODS
void cTimer::_Init()
{
	// Check To See If A Performance Counter Is Available
	// If One Is Available The Timer Frequency Will Be Updated
	if (!QueryPerformanceFrequency((LARGE_INTEGER *) &this->frequency))
	{
		// No Performace Counter Available
		this->performance_timer	= FALSE;				// Set Performance Timer To FALSE
		this->mm_timer_start	= timeGetTime();		// Use timeGetTime() To Get Current Time
		this->resolution	= (double)(1.0f/1000.0f);	// Set Our Timer Resolution To .001f
		this->frequency		= 1000;						// Set Our Timer Frequency To 1000
		this->mm_timer_elapsed	= this->mm_timer_start;	// Set The Elapsed Time To The Current Time
	}
	else
	{
		// Performance Counter Is Available, Use It Instead Of The Multimedia Timer
		// Get The Current Time And Store It In performance_timer_start
		QueryPerformanceCounter((LARGE_INTEGER *) &this->performance_timer_start);
		this->performance_timer	= true;				// Set Performance Timer To TRUE
		// Calculate The Timer Resolution Using The Timer Frequency
		this->resolution = (double) (((double)1.0f)/((double)this->frequency));
		// Set The Elapsed Time To The Current Time
		this->performance_timer_elapsed	= this->performance_timer_start;
	}
}