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
#include "TYPEDEFS.h"
#include "cWindowManagerDX.h"
#include "cWindowManagerSDL.h"

class cWindowManager
{
#pragma message("-- cWindowManager is included")
public:
	// Interface Methods
	static void CreateWindowDX(STRING title, unsigned long width, unsigned long height, bool isFullscreen, HINSTANCE hInstance, int nCmdShow);
	static void CreateWindowSDL(STRING title, unsigned long width, unsigned long height, bool isFullscreen);
	static bool IsInitialized();

	static IWindowManager *window();
	static unsigned long width();
	static unsigned long height();
	static bool isFullscreen();

	static void Release();

private:
	// Private Members
	static IWindowManager *_manager;
};
