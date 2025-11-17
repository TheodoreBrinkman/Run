/**************************************************************************\
*                                                                          *
*	Copyright © 2009-2010 Theo Brinkman. All rights reserved.              *
*	See COPYING.TXT for details.                                           *
*                                                                          *
*	This software is distributed WITHOUT ANY WARRANTY; without even        *
*	the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR    *
*	PURPOSE.  See the above copyright notices for more information.        *
*                                                                          *
\**************************************************************************/
#include "cInputManagerDX.h"

// STATIC INITIALIZATION
int cInputManagerDX::_keyMap[Input::KEY_LAST] = {};

// CONSTRUCTORS
cInputManagerDX::cInputManagerDX(IWindowManager *window)
{
	this->_Initialize((cWindowManagerDX*)window);
}

// DESTRUCTOR
cInputManagerDX::~cInputManagerDX()
{
}

// PUBLIC METHODS
void cInputManagerDX::PollInputs()
{
	if(NULL != this->_diMouse)
	{
		this->_PollMouse();
	}
	if(NULL != this->_diKeyboard)
	{
		this->_PollKeyboard();
	}
	if(NULL != this->_diJoystick)
	{
		this->_PollJoystick();
	}
}
bool cInputManagerDX::KeyDown(Input::KeyCodes key)
{
	return(0 != (this->_keyState[cInputManagerDX::_keyMap[key]] & 0x80));
}
bool cInputManagerDX::KeyWasDown(Input::KeyCodes key)
{
	return(0 != (this->_priorKeyState[cInputManagerDX::_keyMap[key]] & 0x80));
}
bool cInputManagerDX::KeyPress(Input::KeyCodes key)
{
	return(this->KeyWasDown(key) && !this->KeyDown(key));
}
bool cInputManagerDX::KeyHeld(Input::KeyCodes key)
{
	return(this->KeyWasDown(key) && this->KeyDown(key));
}
long cInputManagerDX::MouseX()
{
	return(this->_mouseState.lX);
}
long cInputManagerDX::MouseY()
{
	return(this->_mouseState.lY);
}

bool cInputManagerDX::MouseButtonDown(int button)
{
	return(0 != (this->_mouseState.rgbButtons[button] & 0x80));
}
void cInputManagerDX::Release()
{
	this->_Release();
}

// PRIVATE METHODS
void cInputManagerDX::_Initialize(cWindowManagerDX *window)
{
	this->_hWnd = window->hWnd();
	this->_Initialize(true, false, false);
}
void cInputManagerDX::_Initialize(bool keyboard)
{
	this->_Initialize(keyboard, !keyboard, false);
}
void cInputManagerDX::_Initialize(bool keyboard, bool mouse)
{
	this->_Initialize(keyboard, mouse, !(keyboard || mouse));
}
void cInputManagerDX::_Initialize(bool keyboard, bool mouse, bool joystick)
{
	if(cInputManagerDX::_keyMap[Input::KEY_0] != DIK_0)
	{
		cInputManagerDX::_InitializeKeyMap();
	}
	HRESULT result = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&this->_dinput, NULL);
	if(result != DI_OK)
	{
		throw("cInputManagerDX::_Initialize() could not initialize the DirectInput device.");
	}

	this->_diKeyboard = NULL;
	if(keyboard)
	{
		result = this->_dinput->CreateDevice(GUID_SysKeyboard, &this->_diKeyboard, NULL);
		if(result != DI_OK)
		{
			throw("cInputManagerDX::_Initialize() could not create the keyboard device object.");
		}
		this->_InitializeKeyboard();
	}

	this->_diMouse = NULL;
	if(mouse)
	{
		result = this->_dinput->CreateDevice(GUID_SysMouse, &this->_diMouse, NULL);
		if(result != DI_OK)
		{
			throw("cInputManagerDX::_Initialize() could not create the mouse device object.");
		}
		this->_InitializeMouse();
	}

	this->_diJoystick = NULL;
	if(joystick)
	{
		this->_InitializeJoystick();
	}
}

void cInputManagerDX::_InitializeKeyboard()
{
	if(NULL == this->_diKeyboard)
	{
		throw("cInputManager::InitializeKeyboard() failed - keyboard could not be found.");
	}
	HRESULT result = this->_diKeyboard->SetDataFormat(&c_dfDIKeyboard);
	if(result != DI_OK)
	{
		throw("cInputManagerDX::_InitializeKeyboard() could not set the keyboard data format.");
	}
	result = this->_diKeyboard->SetCooperativeLevel(this->_hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if(result != DI_OK)
	{
		throw("cInputManagerDX::_InitializeKeyboard() could not set the keyboard cooperative level.");
	}
	result = this->_diKeyboard->Acquire();
	if(result != DI_OK)
	{
		throw("cInputManagerDX::_InitializeKeyboard() could not acquire the keyboard.");
	}
}

void cInputManagerDX::_InitializeMouse()
{
	if(NULL == this->_diMouse)
	{
		throw("cInputManager::_InitializeMouse() failed - mouse could not be found.");
	}
	HRESULT result = this->_diMouse->SetDataFormat(&c_dfDIMouse);
	if(result != DI_OK)
	{
		throw("cInputManagerDX::_InitializeMouse() could not set the mouse data format.");
	}
	result = this->_diMouse->SetCooperativeLevel(this->_hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND);
	if(result != DI_OK)
	{
		throw("cInputManagerDX::_InitializeMouse() could not set the mouse cooperative level.");
	}
	result = this->_diMouse->Acquire();
	if(result != DI_OK)
	{
		throw("cInputManagerDX::_InitializeMouse() could not acquire the mouse.");
	}
}

void cInputManagerDX::_InitializeJoystick()
{
	if(NULL == this->_diJoystick)
	{
		throw("cInputManagerDX::_Initialize() failed - joystick not yet implemented.");
	}
}

void cInputManagerDX::_PollKeyboard()
{
	if(DI_OK != this->_diKeyboard->GetDeviceState(sizeof(this->_keyRead), (LPVOID)&this->_keyRead))
	{
		this->_diKeyboard->Acquire();
	}
	for(unsigned long i=Input::KEY_FIRST;i<Input::KEY_LAST;i++)
	{
		this->_priorKeyState[i] = this->_keyState[i];
		this->_keyState[i] = this->_keyRead[i];
	}
}

void cInputManagerDX::_PollMouse()
{
	this->_diMouse->GetDeviceState(sizeof(this->_mouseState), (LPVOID) &this->_mouseState);
}

void cInputManagerDX::_PollJoystick()
{
	if(NULL != this->_diJoystick)
	{
		this->_diJoystick->GetDeviceState(sizeof(this->_joystickState), (LPVOID)&this->_joystickState);
	}
}
void cInputManagerDX::_Release()
{
	this->_ReleaseDevice(this->_diJoystick);
	this->_ReleaseDevice(this->_diMouse);
	this->_ReleaseDevice(this->_diKeyboard);
	if(NULL != this->_dinput)
	{
		this->_dinput->Release();
	}
}

void cInputManagerDX::_ReleaseDevice(LPDIRECTINPUTDEVICE8 device)
{
	if(NULL != device)
	{
		device->Unacquire();
		device->Release();
		device = NULL;
	}
}

void cInputManagerDX::_InitializeKeyMap()
{
	cInputManagerDX::_keyMap[Input::KEY_0] = DIK_0;
	cInputManagerDX::_keyMap[Input::KEY_1] = DIK_1;
	cInputManagerDX::_keyMap[Input::KEY_2] = DIK_2;
	cInputManagerDX::_keyMap[Input::KEY_3] = DIK_3;
	cInputManagerDX::_keyMap[Input::KEY_4] = DIK_4;
	cInputManagerDX::_keyMap[Input::KEY_5] = DIK_5;
	cInputManagerDX::_keyMap[Input::KEY_6] = DIK_6;
	cInputManagerDX::_keyMap[Input::KEY_7] = DIK_7;
	cInputManagerDX::_keyMap[Input::KEY_8] = DIK_8;
	cInputManagerDX::_keyMap[Input::KEY_9] = DIK_9;
	cInputManagerDX::_keyMap[Input::KEY_A] = DIK_A;
	cInputManagerDX::_keyMap[Input::KEY_ABNT_C1] = DIK_ABNT_C1;
	cInputManagerDX::_keyMap[Input::KEY_ABNT_C2] = DIK_ABNT_C2;
	cInputManagerDX::_keyMap[Input::KEY_ADD] = DIK_ADD;
	cInputManagerDX::_keyMap[Input::KEY_APOSTROPHE] = DIK_APOSTROPHE;
	cInputManagerDX::_keyMap[Input::KEY_APPS] = DIK_APPS;
	cInputManagerDX::_keyMap[Input::KEY_AT] = DIK_AT;
	cInputManagerDX::_keyMap[Input::KEY_AX] = DIK_AX;
	cInputManagerDX::_keyMap[Input::KEY_B] = DIK_B;
	cInputManagerDX::_keyMap[Input::KEY_BACK] = DIK_BACK;
	cInputManagerDX::_keyMap[Input::KEY_BACKSLASH] = DIK_BACKSLASH;
	cInputManagerDX::_keyMap[Input::KEY_C] = DIK_C;
	cInputManagerDX::_keyMap[Input::KEY_CALCULATOR] = DIK_CALCULATOR;
	cInputManagerDX::_keyMap[Input::KEY_CAPITAL] = DIK_CAPITAL;
	cInputManagerDX::_keyMap[Input::KEY_COLON] = DIK_COLON;
	cInputManagerDX::_keyMap[Input::KEY_COMMA] = DIK_COMMA;
	cInputManagerDX::_keyMap[Input::KEY_CONVERT] = DIK_CONVERT;
	cInputManagerDX::_keyMap[Input::KEY_D] = DIK_D;
	cInputManagerDX::_keyMap[Input::KEY_DECIMAL] = DIK_DECIMAL;
	cInputManagerDX::_keyMap[Input::KEY_DELETE] = DIK_DELETE;
	cInputManagerDX::_keyMap[Input::KEY_DIVIDE] = DIK_DIVIDE;
	cInputManagerDX::_keyMap[Input::KEY_DOWN] = DIK_DOWN;
	cInputManagerDX::_keyMap[Input::KEY_E] = DIK_E;
	cInputManagerDX::_keyMap[Input::KEY_END] = DIK_END;
	cInputManagerDX::_keyMap[Input::KEY_EQUALS] = DIK_EQUALS;
	cInputManagerDX::_keyMap[Input::KEY_ESCAPE] = DIK_ESCAPE;
	cInputManagerDX::_keyMap[Input::KEY_F] = DIK_F;
	cInputManagerDX::_keyMap[Input::KEY_F1] = DIK_F1;
	cInputManagerDX::_keyMap[Input::KEY_F2] = DIK_F2;
	cInputManagerDX::_keyMap[Input::KEY_F3] = DIK_F3;
	cInputManagerDX::_keyMap[Input::KEY_F4] = DIK_F4;
	cInputManagerDX::_keyMap[Input::KEY_F5] = DIK_F5;
	cInputManagerDX::_keyMap[Input::KEY_F6] = DIK_F6;
	cInputManagerDX::_keyMap[Input::KEY_F7] = DIK_F7;
	cInputManagerDX::_keyMap[Input::KEY_F8] = DIK_F8;
	cInputManagerDX::_keyMap[Input::KEY_F9] = DIK_F9;
	cInputManagerDX::_keyMap[Input::KEY_F10] = DIK_F10;
	cInputManagerDX::_keyMap[Input::KEY_F11] = DIK_F11;
	cInputManagerDX::_keyMap[Input::KEY_F12] = DIK_F12;
	cInputManagerDX::_keyMap[Input::KEY_F13] = DIK_F13;
	cInputManagerDX::_keyMap[Input::KEY_F14] = DIK_F14;
	cInputManagerDX::_keyMap[Input::KEY_F15] = DIK_F15;
	cInputManagerDX::_keyMap[Input::KEY_G] = DIK_G;
	cInputManagerDX::_keyMap[Input::KEY_GRAVE] = DIK_GRAVE;
	cInputManagerDX::_keyMap[Input::KEY_H] = DIK_H;
	cInputManagerDX::_keyMap[Input::KEY_HOME] = DIK_HOME;
	cInputManagerDX::_keyMap[Input::KEY_I] = DIK_I;
	cInputManagerDX::_keyMap[Input::KEY_INSERT] = DIK_INSERT;
	cInputManagerDX::_keyMap[Input::KEY_J] = DIK_J;
	cInputManagerDX::_keyMap[Input::KEY_K] = DIK_K;
	cInputManagerDX::_keyMap[Input::KEY_KANA] = DIK_KANA;
	cInputManagerDX::_keyMap[Input::KEY_KANJI] = DIK_KANJI;
	cInputManagerDX::_keyMap[Input::KEY_L] = DIK_L;
	cInputManagerDX::_keyMap[Input::KEY_LBRACKET] = DIK_LBRACKET;
	cInputManagerDX::_keyMap[Input::KEY_LCONTROL] = DIK_LCONTROL;
	cInputManagerDX::_keyMap[Input::KEY_LEFT] = DIK_LEFT;
	cInputManagerDX::_keyMap[Input::KEY_LMENU] = DIK_LMENU;
	cInputManagerDX::_keyMap[Input::KEY_LSHIFT] = DIK_LSHIFT;
	cInputManagerDX::_keyMap[Input::KEY_LWIN] = DIK_LWIN;
	cInputManagerDX::_keyMap[Input::KEY_M] = DIK_M;
	cInputManagerDX::_keyMap[Input::KEY_MAIL] = DIK_MAIL;
	cInputManagerDX::_keyMap[Input::KEY_MEDIASELECT] = DIK_MEDIASELECT;
	cInputManagerDX::_keyMap[Input::KEY_MEDIASTOP] = DIK_MEDIASTOP;
	cInputManagerDX::_keyMap[Input::KEY_MINUS] = DIK_MINUS;
	cInputManagerDX::_keyMap[Input::KEY_MULTIPLY] = DIK_MULTIPLY;
	cInputManagerDX::_keyMap[Input::KEY_MUTE] = DIK_MUTE;
	cInputManagerDX::_keyMap[Input::KEY_MYCOMPUTER] = DIK_MYCOMPUTER;
	cInputManagerDX::_keyMap[Input::KEY_N] = DIK_N;
	cInputManagerDX::_keyMap[Input::KEY_NEXT] = DIK_NEXT;
	cInputManagerDX::_keyMap[Input::KEY_NEXTTRACK] = DIK_NEXTTRACK;
	cInputManagerDX::_keyMap[Input::KEY_NOCONVERT] = DIK_NOCONVERT;
	cInputManagerDX::_keyMap[Input::KEY_NUMLOCK] = DIK_NUMLOCK;
	cInputManagerDX::_keyMap[Input::KEY_NUMPAD0] = DIK_NUMPAD0;
	cInputManagerDX::_keyMap[Input::KEY_NUMPAD1] = DIK_NUMPAD1;
	cInputManagerDX::_keyMap[Input::KEY_NUMPAD2] = DIK_NUMPAD2;
	cInputManagerDX::_keyMap[Input::KEY_NUMPAD3] = DIK_NUMPAD3;
	cInputManagerDX::_keyMap[Input::KEY_NUMPAD4] = DIK_NUMPAD4;
	cInputManagerDX::_keyMap[Input::KEY_NUMPAD5] = DIK_NUMPAD5;
	cInputManagerDX::_keyMap[Input::KEY_NUMPAD6] = DIK_NUMPAD6;
	cInputManagerDX::_keyMap[Input::KEY_NUMPAD7] = DIK_NUMPAD7;
	cInputManagerDX::_keyMap[Input::KEY_NUMPAD8] = DIK_NUMPAD8;
	cInputManagerDX::_keyMap[Input::KEY_NUMPAD9] = DIK_NUMPAD9;
	cInputManagerDX::_keyMap[Input::KEY_NUMPAD_COMMA] = DIK_NUMPADCOMMA;
	cInputManagerDX::_keyMap[Input::KEY_NUMPAD_ENTER] = DIK_NUMPADENTER;
	cInputManagerDX::_keyMap[Input::KEY_NUMPAD_EQUALS] = DIK_NUMPADEQUALS;
	cInputManagerDX::_keyMap[Input::KEY_O] = DIK_O;
	cInputManagerDX::_keyMap[Input::KEY_OEM_102] = DIK_OEM_102;
	cInputManagerDX::_keyMap[Input::KEY_P] = DIK_P;
	cInputManagerDX::_keyMap[Input::KEY_PAUSE] = DIK_PAUSE;
	cInputManagerDX::_keyMap[Input::KEY_PERIOD] = DIK_PERIOD;
	cInputManagerDX::_keyMap[Input::KEY_PLAYPAUSE] = DIK_PLAYPAUSE;
	cInputManagerDX::_keyMap[Input::KEY_POWER] = DIK_POWER;
	cInputManagerDX::_keyMap[Input::KEY_PREVTRACK] = DIK_PREVTRACK;
	cInputManagerDX::_keyMap[Input::KEY_PRIOR] = DIK_PRIOR;
	cInputManagerDX::_keyMap[Input::KEY_Q] = DIK_Q;
	cInputManagerDX::_keyMap[Input::KEY_R] = DIK_R;
	cInputManagerDX::_keyMap[Input::KEY_RBRACKET] = DIK_RBRACKET;
	cInputManagerDX::_keyMap[Input::KEY_RCONTROL] = DIK_RCONTROL;
	cInputManagerDX::_keyMap[Input::KEY_RETURN] = DIK_RETURN;
	cInputManagerDX::_keyMap[Input::KEY_RIGHT] = DIK_RIGHT;
	cInputManagerDX::_keyMap[Input::KEY_RMENU] = DIK_RMENU;
	cInputManagerDX::_keyMap[Input::KEY_RSHIFT] = DIK_RSHIFT;
	cInputManagerDX::_keyMap[Input::KEY_RWIN] = DIK_RWIN;
	cInputManagerDX::_keyMap[Input::KEY_S] = DIK_S;
	cInputManagerDX::_keyMap[Input::KEY_SCROLL] = DIK_SCROLL;
	cInputManagerDX::_keyMap[Input::KEY_SEMICOLON] = DIK_SEMICOLON;
	cInputManagerDX::_keyMap[Input::KEY_SLASH] = DIK_SLASH;
	cInputManagerDX::_keyMap[Input::KEY_SLEEP] = DIK_SLEEP;
	cInputManagerDX::_keyMap[Input::KEY_SPACE] = DIK_SPACE;
	cInputManagerDX::_keyMap[Input::KEY_STOP] = DIK_STOP;
	cInputManagerDX::_keyMap[Input::KEY_SUBTRACT] = DIK_SUBTRACT;
	cInputManagerDX::_keyMap[Input::KEY_SYSRQ] = DIK_SYSRQ;
	cInputManagerDX::_keyMap[Input::KEY_T] = DIK_T;
	cInputManagerDX::_keyMap[Input::KEY_TAB] = DIK_TAB;
	cInputManagerDX::_keyMap[Input::KEY_U] = DIK_U;
	cInputManagerDX::_keyMap[Input::KEY_UNDERLINE] = DIK_UNDERLINE;
	cInputManagerDX::_keyMap[Input::KEY_UNLABELED] = DIK_UNLABELED;
	cInputManagerDX::_keyMap[Input::KEY_UP] = DIK_UP;
	cInputManagerDX::_keyMap[Input::KEY_V] = DIK_V;
	cInputManagerDX::_keyMap[Input::KEY_VOLUMEDOWN] = DIK_VOLUMEDOWN;
	cInputManagerDX::_keyMap[Input::KEY_VOLUMEUP] = DIK_VOLUMEUP;
	cInputManagerDX::_keyMap[Input::KEY_W] = DIK_W;
	cInputManagerDX::_keyMap[Input::KEY_WAKE] = DIK_WAKE;
	cInputManagerDX::_keyMap[Input::KEY_WEBBACK] = DIK_WEBBACK;
	cInputManagerDX::_keyMap[Input::KEY_WEBFAVORITES] = DIK_WEBFAVORITES;
	cInputManagerDX::_keyMap[Input::KEY_WEBFORWARD] = DIK_WEBFORWARD;
	cInputManagerDX::_keyMap[Input::KEY_WEBHOME] = DIK_WEBHOME;
	cInputManagerDX::_keyMap[Input::KEY_WEBREFRESH] = DIK_WEBREFRESH;
	cInputManagerDX::_keyMap[Input::KEY_WEBSEARCH] = DIK_WEBSEARCH;
	cInputManagerDX::_keyMap[Input::KEY_WEBSTOP] = DIK_WEBSTOP;
	cInputManagerDX::_keyMap[Input::KEY_X] = DIK_X;
	cInputManagerDX::_keyMap[Input::KEY_Y] = DIK_Y;
	cInputManagerDX::_keyMap[Input::KEY_YEN] = DIK_YEN;
	cInputManagerDX::_keyMap[Input::KEY_Z] = DIK_Z;
}