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
#include <dinput.h>
#include "IWindowManager.h"
#include "cWindowManagerDX.h"
#include "IInputManager.h"

class cInputManagerDX
	: public IInputManager
{
#pragma message("-- cInputManagerDX is included")
public:
	cInputManagerDX(IWindowManager *window);
	virtual ~cInputManagerDX();

private:
	HWND _hWnd;
	LPDIRECTINPUT8 _dinput;
	LPDIRECTINPUTDEVICE8 _diKeyboard;
	char _keyRead[255];
	char _keyState[Input::KEY_LAST];
	char _priorKeyState[Input::KEY_LAST];
	LPDIRECTINPUTDEVICE8 _diMouse;
	DIMOUSESTATE2 _mouseState;
	LPDIRECTINPUTDEVICE8 _diJoystick;
	DIJOYSTATE2 _joystickState;

	// Inteface Methods
	virtual void PollInputs();

	virtual bool KeyDown(Input::KeyCodes key);
	virtual bool KeyWasDown(Input::KeyCodes key);
	virtual bool KeyPress(Input::KeyCodes key);
	virtual bool KeyHeld(Input::KeyCodes key);

	virtual long MouseX();
	virtual long MouseY();
	virtual bool MouseButtonDown(int button);

	virtual void Release();

	// Private Methods
	void _Initialize(cWindowManagerDX *window);
	void _Initialize(bool keyboard);
	void _Initialize(bool keyboard, bool mouse);
	void _Initialize(bool keyboard, bool mouse, bool joystick);
	void _InitializeMouse();
	void _InitializeKeyboard();
	void _InitializeJoystick();

	void _PollMouse();
	void _PollKeyboard();
	void _PollJoystick();

	void _Release();
	void _ReleaseDevice(LPDIRECTINPUTDEVICE8 device);

	static int _keyMap[Input::KEY_LAST];
	static void _InitializeKeyMap();
};