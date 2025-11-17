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
#include "cInputManagerRaw.h"

// STATIC INITIALIZATION
int cInputManagerRaw::_keyMap[Input::KEY_LAST] = {};

// CONSTRUCTORS
cInputManagerRaw::cInputManagerRaw()
{
	if(cInputManagerRaw::_keyMap[0] == 0)
	{
		cInputManagerRaw::_InitializeKeyMap();
	}
}

// DESTRUCTOR
cInputManagerRaw::~cInputManagerRaw(void)
{
}

// PUBLIC METHODS
void cInputManagerRaw::PollInputs()
{
	for(unsigned long i=Input::KEY_FIRST;i<Input::KEY_LAST;i++)
	{
		this->_priorKeyState[i] = this->_keyState[i];
		this->_keyState[i] = GetAsyncKeyState(i);
	}
}
bool cInputManagerRaw::KeyDown(Input::KeyCodes key)
{
	return(0 != (this->_keyState[cInputManagerRaw::_keyMap[key]] & 0x8000));
}
bool cInputManagerRaw::KeyWasDown(Input::KeyCodes key)
{
	return(0 != (this->_priorKeyState[cInputManagerRaw::_keyMap[key]] & 0x8000));
}
bool cInputManagerRaw::KeyPress(Input::KeyCodes key)
{
	return(this->KeyWasDown(key) && !this->KeyDown(key));
}
bool cInputManagerRaw::KeyHeld(Input::KeyCodes key)
{
	return(this->KeyWasDown(key) && this->KeyDown(key));
}
long cInputManagerRaw::MouseX()
{
	return(0);
//	return(this->_mouseState.lX);
}
long cInputManagerRaw::MouseY()
{
	return(0);
//	return(this->_mouseState.lY);
}

bool cInputManagerRaw::MouseButtonDown(int button)
{
	return(0);
//	return(0 != (this->_mouseState.rgbButtons[button] & 0x80));
}
void cInputManagerRaw::Release()
{
}

void cInputManagerRaw::_InitializeKeyMap()
{
	cInputManagerRaw::_keyMap[Input::KEY_0] = '0';
	cInputManagerRaw::_keyMap[Input::KEY_1] = '1';
	cInputManagerRaw::_keyMap[Input::KEY_2] = '2';
	cInputManagerRaw::_keyMap[Input::KEY_3] = '3';
	cInputManagerRaw::_keyMap[Input::KEY_4] = '4';
	cInputManagerRaw::_keyMap[Input::KEY_5] = '5';
	cInputManagerRaw::_keyMap[Input::KEY_6] = '6';
	cInputManagerRaw::_keyMap[Input::KEY_7] = '7';
	cInputManagerRaw::_keyMap[Input::KEY_8] = '8';
	cInputManagerRaw::_keyMap[Input::KEY_9] = '9';
	cInputManagerRaw::_keyMap[Input::KEY_A] = 'A';
	cInputManagerRaw::_keyMap[Input::KEY_ABNT_C1] = Input::KEY_UNKNOWN;
	cInputManagerRaw::_keyMap[Input::KEY_ABNT_C2] = Input::KEY_UNKNOWN;
	cInputManagerRaw::_keyMap[Input::KEY_ADD] = VK_ADD;
	cInputManagerRaw::_keyMap[Input::KEY_APOSTROPHE] = '\'';
	cInputManagerRaw::_keyMap[Input::KEY_APPS] = VK_APPS;
	cInputManagerRaw::_keyMap[Input::KEY_AT] = '@';
	cInputManagerRaw::_keyMap[Input::KEY_AX] = Input::KEY_UNKNOWN;
	cInputManagerRaw::_keyMap[Input::KEY_B] = 'B';
	cInputManagerRaw::_keyMap[Input::KEY_BACK] = VK_BACK;
	cInputManagerRaw::_keyMap[Input::KEY_BACKSLASH] = '\\';
	cInputManagerRaw::_keyMap[Input::KEY_C] = 'C';
	cInputManagerRaw::_keyMap[Input::KEY_CALCULATOR] = Input::KEY_UNKNOWN;
	cInputManagerRaw::_keyMap[Input::KEY_CAPITAL] = Input::KEY_UNKNOWN;
	cInputManagerRaw::_keyMap[Input::KEY_COLON] = ':';
	cInputManagerRaw::_keyMap[Input::KEY_COMMA] = ',';
	cInputManagerRaw::_keyMap[Input::KEY_CONVERT] = VK_CONVERT;
	cInputManagerRaw::_keyMap[Input::KEY_D] = 'D';
	cInputManagerRaw::_keyMap[Input::KEY_DECIMAL] = '.';
	cInputManagerRaw::_keyMap[Input::KEY_DELETE] = VK_DELETE;
	cInputManagerRaw::_keyMap[Input::KEY_DIVIDE] = VK_DIVIDE;
	cInputManagerRaw::_keyMap[Input::KEY_DOWN] = VK_DOWN;
	cInputManagerRaw::_keyMap[Input::KEY_E] = 'E';
	cInputManagerRaw::_keyMap[Input::KEY_END] = VK_END;
	cInputManagerRaw::_keyMap[Input::KEY_EQUALS] = '=';
	cInputManagerRaw::_keyMap[Input::KEY_ESCAPE] = VK_ESCAPE;
	cInputManagerRaw::_keyMap[Input::KEY_F] = 'F';
	cInputManagerRaw::_keyMap[Input::KEY_F1] = VK_F1;
	cInputManagerRaw::_keyMap[Input::KEY_F2] = VK_F2;
	cInputManagerRaw::_keyMap[Input::KEY_F3] = VK_F3;
	cInputManagerRaw::_keyMap[Input::KEY_F4] = VK_F4;
	cInputManagerRaw::_keyMap[Input::KEY_F5] = VK_F5;
	cInputManagerRaw::_keyMap[Input::KEY_F6] = VK_F6;
	cInputManagerRaw::_keyMap[Input::KEY_F7] = VK_F7;
	cInputManagerRaw::_keyMap[Input::KEY_F8] = VK_F8;
	cInputManagerRaw::_keyMap[Input::KEY_F9] = VK_F9;
	cInputManagerRaw::_keyMap[Input::KEY_F10] = VK_F10;
	cInputManagerRaw::_keyMap[Input::KEY_F11] = VK_F11;
	cInputManagerRaw::_keyMap[Input::KEY_F12] = VK_F12;
	cInputManagerRaw::_keyMap[Input::KEY_F13] = VK_F13;
	cInputManagerRaw::_keyMap[Input::KEY_F14] = VK_F14;
	cInputManagerRaw::_keyMap[Input::KEY_F15] = VK_F15;
	cInputManagerRaw::_keyMap[Input::KEY_G] = 'G';
	cInputManagerRaw::_keyMap[Input::KEY_GRAVE] = Input::KEY_UNKNOWN;
	cInputManagerRaw::_keyMap[Input::KEY_GREATER] = '>';
	cInputManagerRaw::_keyMap[Input::KEY_H] = 'H';
	cInputManagerRaw::_keyMap[Input::KEY_HOME] = VK_HOME;
	cInputManagerRaw::_keyMap[Input::KEY_I] = 'I';
	cInputManagerRaw::_keyMap[Input::KEY_INSERT] = VK_INSERT;
	cInputManagerRaw::_keyMap[Input::KEY_J] = 'J';
	cInputManagerRaw::_keyMap[Input::KEY_K] = 'K';
	cInputManagerRaw::_keyMap[Input::KEY_KANA] = VK_KANA;
	cInputManagerRaw::_keyMap[Input::KEY_KANJI] = VK_KANJI;
	cInputManagerRaw::_keyMap[Input::KEY_L] = 'L';
	cInputManagerRaw::_keyMap[Input::KEY_LBRACKET] = '[';
	cInputManagerRaw::_keyMap[Input::KEY_LCONTROL] = VK_LCONTROL;
	cInputManagerRaw::_keyMap[Input::KEY_LEFT] = VK_LEFT;
	cInputManagerRaw::_keyMap[Input::KEY_LESS] = '<';
	cInputManagerRaw::_keyMap[Input::KEY_LMENU] = VK_LMENU;
	cInputManagerRaw::_keyMap[Input::KEY_LSHIFT] = VK_LSHIFT;
	cInputManagerRaw::_keyMap[Input::KEY_LSUPER] = VK_LWIN;
	cInputManagerRaw::_keyMap[Input::KEY_LWIN] = VK_LWIN;
	cInputManagerRaw::_keyMap[Input::KEY_M] = 'M';
	cInputManagerRaw::_keyMap[Input::KEY_MAIL] = Input::KEY_UNKNOWN;
	cInputManagerRaw::_keyMap[Input::KEY_MEDIASELECT] = Input::KEY_UNKNOWN;
	cInputManagerRaw::_keyMap[Input::KEY_MEDIASTOP] = Input::KEY_UNKNOWN;
	cInputManagerRaw::_keyMap[Input::KEY_MINUS] = '-';
	cInputManagerRaw::_keyMap[Input::KEY_MULTIPLY] = VK_MULTIPLY;
	cInputManagerRaw::_keyMap[Input::KEY_MUTE] = Input::KEY_UNKNOWN;
	cInputManagerRaw::_keyMap[Input::KEY_MYCOMPUTER] = Input::KEY_UNKNOWN;
	cInputManagerRaw::_keyMap[Input::KEY_N] = 'N';
	cInputManagerRaw::_keyMap[Input::KEY_NEXT] = VK_NEXT;
	cInputManagerRaw::_keyMap[Input::KEY_NEXTTRACK] = Input::KEY_UNKNOWN;
	cInputManagerRaw::_keyMap[Input::KEY_NOCONVERT] = Input::KEY_UNKNOWN;
	cInputManagerRaw::_keyMap[Input::KEY_NUMLOCK] = VK_NUMLOCK;
	cInputManagerRaw::_keyMap[Input::KEY_NUMPAD0] = VK_NUMPAD0;
	cInputManagerRaw::_keyMap[Input::KEY_NUMPAD1] = VK_NUMPAD1;
	cInputManagerRaw::_keyMap[Input::KEY_NUMPAD2] = VK_NUMPAD2;
	cInputManagerRaw::_keyMap[Input::KEY_NUMPAD3] = VK_NUMPAD3;
	cInputManagerRaw::_keyMap[Input::KEY_NUMPAD4] = VK_NUMPAD4;
	cInputManagerRaw::_keyMap[Input::KEY_NUMPAD5] = VK_NUMPAD5;
	cInputManagerRaw::_keyMap[Input::KEY_NUMPAD6] = VK_NUMPAD6;
	cInputManagerRaw::_keyMap[Input::KEY_NUMPAD7] = VK_NUMPAD7;
	cInputManagerRaw::_keyMap[Input::KEY_NUMPAD8] = VK_NUMPAD8;
	cInputManagerRaw::_keyMap[Input::KEY_NUMPAD9] = VK_NUMPAD9;
	cInputManagerRaw::_keyMap[Input::KEY_NUMPAD_COMMA] = ',';
	cInputManagerRaw::_keyMap[Input::KEY_NUMPAD_ENTER] = VK_RETURN;
	cInputManagerRaw::_keyMap[Input::KEY_NUMPAD_EQUALS] = '=';
	cInputManagerRaw::_keyMap[Input::KEY_O] = 'O';
	cInputManagerRaw::_keyMap[Input::KEY_OEM_102] = Input::KEY_UNKNOWN;
	cInputManagerRaw::_keyMap[Input::KEY_P] = 'P';
	cInputManagerRaw::_keyMap[Input::KEY_PAUSE] = VK_PAUSE;
	cInputManagerRaw::_keyMap[Input::KEY_PERIOD] = '.';
	cInputManagerRaw::_keyMap[Input::KEY_PLAYPAUSE] = Input::KEY_UNKNOWN;
	cInputManagerRaw::_keyMap[Input::KEY_POWER] = Input::KEY_UNKNOWN;
	cInputManagerRaw::_keyMap[Input::KEY_PREVTRACK] = Input::KEY_UNKNOWN;
	cInputManagerRaw::_keyMap[Input::KEY_PRIOR] = VK_PRIOR;
	cInputManagerRaw::_keyMap[Input::KEY_Q] = 'Q';
	cInputManagerRaw::_keyMap[Input::KEY_QUESTION] = '?';
	cInputManagerRaw::_keyMap[Input::KEY_R] = 'R';
	cInputManagerRaw::_keyMap[Input::KEY_RBRACKET] = ']';
	cInputManagerRaw::_keyMap[Input::KEY_RCONTROL] = VK_RCONTROL;
	cInputManagerRaw::_keyMap[Input::KEY_RETURN] = VK_RETURN;
	cInputManagerRaw::_keyMap[Input::KEY_RIGHT] = VK_RIGHT;
	cInputManagerRaw::_keyMap[Input::KEY_RMENU] = VK_RMENU;
	cInputManagerRaw::_keyMap[Input::KEY_RSHIFT] = VK_RSHIFT;
	cInputManagerRaw::_keyMap[Input::KEY_RSUPER] = VK_RWIN;
	cInputManagerRaw::_keyMap[Input::KEY_RWIN] = VK_RWIN;
	cInputManagerRaw::_keyMap[Input::KEY_S] = 'S';
	cInputManagerRaw::_keyMap[Input::KEY_SCROLL] = VK_SCROLL;
	cInputManagerRaw::_keyMap[Input::KEY_SEMICOLON] = ';';
	cInputManagerRaw::_keyMap[Input::KEY_SLASH] = '/';
	cInputManagerRaw::_keyMap[Input::KEY_SLEEP] = VK_SLEEP;
	cInputManagerRaw::_keyMap[Input::KEY_SPACE] = VK_SPACE;
	cInputManagerRaw::_keyMap[Input::KEY_STOP] = Input::KEY_UNKNOWN;
	cInputManagerRaw::_keyMap[Input::KEY_SUBTRACT] = VK_SUBTRACT;
	cInputManagerRaw::_keyMap[Input::KEY_SYSRQ] = Input::KEY_UNKNOWN;
	cInputManagerRaw::_keyMap[Input::KEY_T] = 'T';
	cInputManagerRaw::_keyMap[Input::KEY_TAB] = VK_TAB;
	cInputManagerRaw::_keyMap[Input::KEY_U] = 'U';
	cInputManagerRaw::_keyMap[Input::KEY_UNDERLINE] = '_';
	cInputManagerRaw::_keyMap[Input::KEY_UNLABELED] = Input::KEY_UNKNOWN;
	cInputManagerRaw::_keyMap[Input::KEY_UP] = VK_UP;
	cInputManagerRaw::_keyMap[Input::KEY_V] = 'V';
	cInputManagerRaw::_keyMap[Input::KEY_VOLUMEDOWN] = Input::KEY_UNKNOWN;
	cInputManagerRaw::_keyMap[Input::KEY_VOLUMEUP] = Input::KEY_UNKNOWN;
	cInputManagerRaw::_keyMap[Input::KEY_W] = 'W';
	cInputManagerRaw::_keyMap[Input::KEY_WAKE] = Input::KEY_UNKNOWN;
	cInputManagerRaw::_keyMap[Input::KEY_WEBBACK] = Input::KEY_UNKNOWN;
	cInputManagerRaw::_keyMap[Input::KEY_WEBFAVORITES] = Input::KEY_UNKNOWN;
	cInputManagerRaw::_keyMap[Input::KEY_WEBFORWARD] = Input::KEY_UNKNOWN;
	cInputManagerRaw::_keyMap[Input::KEY_WEBHOME] = Input::KEY_UNKNOWN;
	cInputManagerRaw::_keyMap[Input::KEY_WEBREFRESH] = Input::KEY_UNKNOWN;
	cInputManagerRaw::_keyMap[Input::KEY_WEBSEARCH] = Input::KEY_UNKNOWN;
	cInputManagerRaw::_keyMap[Input::KEY_WEBSTOP] = Input::KEY_UNKNOWN;
	cInputManagerRaw::_keyMap[Input::KEY_X] = 'X';
	cInputManagerRaw::_keyMap[Input::KEY_Y] = 'Y';
	cInputManagerRaw::_keyMap[Input::KEY_YEN] = Input::KEY_UNKNOWN;
	cInputManagerRaw::_keyMap[Input::KEY_Z] = 'Z';
}