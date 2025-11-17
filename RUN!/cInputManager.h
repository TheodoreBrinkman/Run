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
#include "IWindowManager.h"
#include "cWindowManager.h"
#include "cInputManagerRaw.h"
#include "cInputManagerDX.h"
#include "cInputManagerSDL.h"
#include "Enums.h"

class cInputManager
{
#pragma message("-- cInputManager is included")
public:
	static void Initialize();
	static bool IsInitialized();

	static void PollInputs();

	static bool KeyDown(Input::KeyCodes key);
	static bool KeyWasDown(Input::KeyCodes key);
	static bool KeyPress(Input::KeyCodes key);
	static bool KeyHeld(Input::KeyCodes key);

	static long MouseX();
	static long MouseY();
	static bool MouseButtonDown(int button);

	static void Release();

private:
	static IInputManager *_manager;
};