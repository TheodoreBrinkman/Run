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
#include "IInputManager.h"

class cInputManagerRaw :
	public IInputManager
{
public:
	cInputManagerRaw();
	virtual ~cInputManagerRaw();

private:
	short _keyState[Input::KEY_LAST];
	short _priorKeyState[Input::KEY_LAST];

	// Inteface Methods
	virtual void PollInputs();

	virtual bool KeyDown(Input::KeyCodes key);
	virtual bool KeyWasDown(Input::KeyCodes);
	virtual bool KeyPress(Input::KeyCodes key);
	virtual bool KeyHeld(Input::KeyCodes key);

	virtual long MouseX();
	virtual long MouseY();
	virtual bool MouseButtonDown(int button);

	virtual void Release();

	static int _keyMap[Input::KEY_LAST];
	static void _InitializeKeyMap();
};
