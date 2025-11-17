/******************************************************************************\
*                                                                              *
*	Copyright © 2010 Theo Brinkman. All rights reserved.                       *
*                                                                              *
*	This work is licensed under a Creative Commons                             *
*	Attribution-Noncommercial-No Derivative Works 3.0 United States License.   *
*                                                                              *
*	See COPYING.TXT for details.                                               *
*                                                                              *
\******************************************************************************/
#pragma once
#include <SDL.h>
#include <SDL_main.h>
#include "IWindowManager.h"
#include "cWindowManagerSDL.h"
#include "IInputManager.h"

class cInputManagerSDL
	: public IInputManager
{
#pragma message("-- cInputManagerSDL is included")
public:
	cInputManagerSDL();
	virtual ~cInputManagerSDL();

private:
	bool _useKeyboard;
	char _keyState[Input::KEY_LAST];
	char _priorKeyState[Input::KEY_LAST];
	bool _useMouse;
	int *_mouseX;
	int *_mouseY;
	Uint8 _mouseButtonState;
	bool _useJoystick;
	SDL_Joystick *_joystick;

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
	void _Initialize();
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

	static int _keyMap[Input::KEY_LAST];
	static void _InitializeKeyMap();
};
