/**************************************************************************\
*                                                                          *
*	Copyright © 2010 Theo Brinkman. All rights reserved.                   *
*	See COPYING.TXT for details.                                           *
*                                                                          *
*	This software is distributed WITHOUT ANY WARRANTY; without even        *
*	the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR    *
*	PURPOSE.  See the above copyright notices for more information.        *
*                                                                          *
\**************************************************************************/
#include "cInputManagerSDL.h"
// STATIC INITIALIZATION
int cInputManagerSDL::_keyMap[Input::KEY_LAST] = {};

// CONSTRUCTORS
cInputManagerSDL::cInputManagerSDL()
{
	this->_Initialize();
}

// DESTRUCTOR
cInputManagerSDL::~cInputManagerSDL()
{
}

// PUBLIC METHODS
void cInputManagerSDL::PollInputs()
{
	if(this->_useMouse)
	{
		this->_PollMouse();
	}
	if(this->_useKeyboard)
	{
		this->_PollKeyboard();
	}
	if(this->_useJoystick)
	{
		this->_PollJoystick();
	}
}
bool cInputManagerSDL::KeyDown(Input::KeyCodes key)
{
	return(0 != (this->_keyState[cInputManagerSDL::_keyMap[key]] & 0x80));
}
bool cInputManagerSDL::KeyWasDown(Input::KeyCodes key)
{
	return(0 != (this->_priorKeyState[cInputManagerSDL::_keyMap[key]] & 0x80));
}
bool cInputManagerSDL::KeyPress(Input::KeyCodes key)
{
	return(this->KeyWasDown(key) && !this->KeyDown(key));
}
bool cInputManagerSDL::KeyHeld(Input::KeyCodes key)
{
	return(this->KeyWasDown(key) && this->KeyDown(key));
}
long cInputManagerSDL::MouseX()
{
	throw("cInputManagerSDL::MouseX is not yet implemented.");
}
long cInputManagerSDL::MouseY()
{
	throw("cInputManagerSDL::MouseY is not yet implemented.");
}

bool cInputManagerSDL::MouseButtonDown(int button)
{
	throw("cInputManagerSDL::MouseButtonDown is not yet implemented.");
}
void cInputManagerSDL::Release()
{
	this->_Release();
}

// PRIVATE METHODS
void cInputManagerSDL::_Initialize()
{
	this->_Initialize(true, false, false);
}
void cInputManagerSDL::_Initialize(bool keyboard)
{
	this->_Initialize(keyboard, !keyboard, false);
}
void cInputManagerSDL::_Initialize(bool keyboard, bool mouse)
{
	this->_Initialize(keyboard, mouse, !(keyboard || mouse));
}
void cInputManagerSDL::_Initialize(bool keyboard, bool mouse, bool joystick)
{
	if(-1 == SDL_Init(SDL_INIT_EVERYTHING))
	{
		throw("cInputManagerSDL::_Initialize - Could not Initialize SDL!");
	}

	this->_useKeyboard = keyboard;
	this->_useMouse = mouse;
	this->_useJoystick = joystick;

	if(cInputManagerSDL::_keyMap[Input::KEY_0] != SDLK_0)
	{
		cInputManagerSDL::_InitializeKeyMap();
	}

	if(keyboard)
	{
		this->_InitializeKeyboard();
	}

	if(mouse)
	{
		this->_InitializeMouse();
	}

	if(joystick)
	{
		this->_InitializeJoystick();
	}
}

void cInputManagerSDL::_InitializeKeyboard()
{
	// Nothing to implement here?
	//throw("cInputManagerSDL::_InitializeKeyboard() is not yet implemented.");
	//if(0 != SDL_GetNumKeyboards())
	//{
	//	throw("cInputManagerSDL::_InitializeKeyboard() - Could not find a keyboard.");
	//}
	//if(SDL_SelectKeyboard(0) < 0)
	//{
	//	throw(SDL_GetError());
	//}
}

void cInputManagerSDL::_InitializeMouse()
{
	// Nothing to implement here?
	//throw("cInputManagerSDL::_InitializeMouse() is not yet implemented.");
	//if(0 != SDL_NumMice())
	//{
	//	throw("cInputManagerSDL::_InitializeMouse() - Could not find a mouse.");
	//}
	//if(SDL_SelectMouse(0) < 0)
	//{
	//	throw(SDL_GetError());
	//}
}

void cInputManagerSDL::_InitializeJoystick()
{
	//throw("cInputManagerSDL::_InitializeJoystick() is not yet implemented.");
	if(0 != SDL_NumJoysticks())
	{
		throw("cInputManagerSDL::_InitializeJoystick() - Could not find a joystick.");
	}
	this->_joystick = SDL_JoystickOpen(0);
	if(0 == SDL_JoystickOpened(0))
	{
		throw(SDL_GetError());
	}
}

void cInputManagerSDL::_PollKeyboard()
{
	Uint8 *keystates = SDL_GetKeyState(NULL);
	for(unsigned long i=Input::KEY_FIRST;i<Input::KEY_LAST;i++)
	{
		this->_priorKeyState[i] = this->_keyState[i];
		this->_keyState[i] = (char)keystates[i];
	}
}

void cInputManagerSDL::_PollMouse()
{
	this->_mouseButtonState = SDL_GetMouseState(this->_mouseX, this->_mouseY);
}

void cInputManagerSDL::_PollJoystick()
{
	throw("cInputManagerSDL::_PollJoystick() is not yet implemented.");
}
void cInputManagerSDL::_Release()
{
	if(NULL != this->_joystick)
	{
		SDL_JoystickClose(this->_joystick);
	}
	this->_joystick = NULL;
}

void cInputManagerSDL::_InitializeKeyMap()
{
	cInputManagerSDL::_keyMap[Input::KEY_0] = SDLK_0;
	cInputManagerSDL::_keyMap[Input::KEY_1] = SDLK_1;
	cInputManagerSDL::_keyMap[Input::KEY_2] = SDLK_2;
	cInputManagerSDL::_keyMap[Input::KEY_3] = SDLK_3;
	cInputManagerSDL::_keyMap[Input::KEY_4] = SDLK_4;
	cInputManagerSDL::_keyMap[Input::KEY_5] = SDLK_5;
	cInputManagerSDL::_keyMap[Input::KEY_6] = SDLK_6;
	cInputManagerSDL::_keyMap[Input::KEY_7] = SDLK_7;
	cInputManagerSDL::_keyMap[Input::KEY_8] = SDLK_8;
	cInputManagerSDL::_keyMap[Input::KEY_9] = SDLK_9;
	cInputManagerSDL::_keyMap[Input::KEY_A] = SDLK_a;
	cInputManagerSDL::_keyMap[Input::KEY_ABNT_C1] = SDLK_UNKNOWN;
	cInputManagerSDL::_keyMap[Input::KEY_ABNT_C2] = SDLK_UNKNOWN;
	cInputManagerSDL::_keyMap[Input::KEY_ADD] = SDLK_PLUS;
	cInputManagerSDL::_keyMap[Input::KEY_AMPERSAND] = SDLK_AMPERSAND;
	cInputManagerSDL::_keyMap[Input::KEY_APOSTROPHE] = SDLK_QUOTE;
	cInputManagerSDL::_keyMap[Input::KEY_APPS] = SDLK_UNKNOWN;
	cInputManagerSDL::_keyMap[Input::KEY_ASTERISK] = SDLK_ASTERISK;
	cInputManagerSDL::_keyMap[Input::KEY_AT] = SDLK_AT;
	cInputManagerSDL::_keyMap[Input::KEY_AX] = SDLK_UNKNOWN;
	cInputManagerSDL::_keyMap[Input::KEY_B] = SDLK_b;
	cInputManagerSDL::_keyMap[Input::KEY_BACKQUOTE] = SDLK_BACKQUOTE;
	cInputManagerSDL::_keyMap[Input::KEY_BACK] = SDLK_BACKSPACE;
	cInputManagerSDL::_keyMap[Input::KEY_BACKSLASH] = SDLK_BACKSLASH;
	cInputManagerSDL::_keyMap[Input::KEY_BREAK] = SDLK_BREAK;
	cInputManagerSDL::_keyMap[Input::KEY_C] = SDLK_c;
	cInputManagerSDL::_keyMap[Input::KEY_CALCULATOR] = SDLK_UNKNOWN;
	cInputManagerSDL::_keyMap[Input::KEY_CAPITAL] = SDLK_CAPSLOCK;
	cInputManagerSDL::_keyMap[Input::KEY_CARET] = SDLK_CARET;
	cInputManagerSDL::_keyMap[Input::KEY_CLEAR] = SDLK_CLEAR;
	cInputManagerSDL::_keyMap[Input::KEY_COLON] = SDLK_COLON;
	cInputManagerSDL::_keyMap[Input::KEY_COMMA] = SDLK_COMMA;
	cInputManagerSDL::_keyMap[Input::KEY_COMPOSE] = SDLK_COMPOSE;
	cInputManagerSDL::_keyMap[Input::KEY_CONVERT] = SDLK_UNKNOWN;
	cInputManagerSDL::_keyMap[Input::KEY_D] = SDLK_d;
	cInputManagerSDL::_keyMap[Input::KEY_DECIMAL] = SDLK_PERIOD;
	cInputManagerSDL::_keyMap[Input::KEY_DELETE] = SDLK_DELETE;
	cInputManagerSDL::_keyMap[Input::KEY_DIVIDE] = SDLK_SLASH;
	cInputManagerSDL::_keyMap[Input::KEY_DOLLAR] = SDLK_DOLLAR;
	cInputManagerSDL::_keyMap[Input::KEY_DOWN] = SDLK_DOWN;
	cInputManagerSDL::_keyMap[Input::KEY_E] = SDLK_e;
	cInputManagerSDL::_keyMap[Input::KEY_END] = SDLK_END;
	cInputManagerSDL::_keyMap[Input::KEY_EQUALS] = SDLK_EQUALS;
	cInputManagerSDL::_keyMap[Input::KEY_ESCAPE] = SDLK_ESCAPE;
	cInputManagerSDL::_keyMap[Input::KEY_EURO] = SDLK_EURO;
	cInputManagerSDL::_keyMap[Input::KEY_EXCLAIM] = SDLK_EXCLAIM;
	cInputManagerSDL::_keyMap[Input::KEY_F] = SDLK_f;
	cInputManagerSDL::_keyMap[Input::KEY_F1] = SDLK_F1;
	cInputManagerSDL::_keyMap[Input::KEY_F2] = SDLK_F2;
	cInputManagerSDL::_keyMap[Input::KEY_F3] = SDLK_F3;
	cInputManagerSDL::_keyMap[Input::KEY_F4] = SDLK_F4;
	cInputManagerSDL::_keyMap[Input::KEY_F5] = SDLK_F5;
	cInputManagerSDL::_keyMap[Input::KEY_F6] = SDLK_F6;
	cInputManagerSDL::_keyMap[Input::KEY_F7] = SDLK_F7;
	cInputManagerSDL::_keyMap[Input::KEY_F8] = SDLK_F8;
	cInputManagerSDL::_keyMap[Input::KEY_F9] = SDLK_F9;
	cInputManagerSDL::_keyMap[Input::KEY_F10] = SDLK_F10;
	cInputManagerSDL::_keyMap[Input::KEY_F11] = SDLK_F11;
	cInputManagerSDL::_keyMap[Input::KEY_F12] = SDLK_F12;
	cInputManagerSDL::_keyMap[Input::KEY_F13] = SDLK_F13;
	cInputManagerSDL::_keyMap[Input::KEY_F14] = SDLK_F14;
	cInputManagerSDL::_keyMap[Input::KEY_F15] = SDLK_F15;
	cInputManagerSDL::_keyMap[Input::KEY_G] = SDLK_g;
	cInputManagerSDL::_keyMap[Input::KEY_GRAVE] = SDLK_UNKNOWN;
	cInputManagerSDL::_keyMap[Input::KEY_GREATER] = SDLK_GREATER;
	cInputManagerSDL::_keyMap[Input::KEY_H] = SDLK_h;
	cInputManagerSDL::_keyMap[Input::KEY_HASH] = SDLK_HASH;
	cInputManagerSDL::_keyMap[Input::KEY_HELP] = SDLK_HELP;
	cInputManagerSDL::_keyMap[Input::KEY_HOME] = SDLK_HOME;
	cInputManagerSDL::_keyMap[Input::KEY_I] = SDLK_i;
	cInputManagerSDL::_keyMap[Input::KEY_INSERT] = SDLK_INSERT;
	cInputManagerSDL::_keyMap[Input::KEY_J] = SDLK_j;
	cInputManagerSDL::_keyMap[Input::KEY_K] = SDLK_k;
	cInputManagerSDL::_keyMap[Input::KEY_KANA] = SDLK_UNKNOWN;
	cInputManagerSDL::_keyMap[Input::KEY_KANJI] = SDLK_UNKNOWN;
	cInputManagerSDL::_keyMap[Input::KEY_L] = SDLK_l;
	cInputManagerSDL::_keyMap[Input::KEY_LALT] = SDLK_LALT;
	cInputManagerSDL::_keyMap[Input::KEY_LBRACKET] = SDLK_LEFTBRACKET;
	cInputManagerSDL::_keyMap[Input::KEY_LCONTROL] = SDLK_LCTRL;
	cInputManagerSDL::_keyMap[Input::KEY_LESS] = SDLK_LESS;
	cInputManagerSDL::_keyMap[Input::KEY_LEFT] = SDLK_LEFT;
	cInputManagerSDL::_keyMap[Input::KEY_LPAREN] = SDLK_LEFTPAREN;
	cInputManagerSDL::_keyMap[Input::KEY_LMENU] = SDLK_UNKNOWN;
	cInputManagerSDL::_keyMap[Input::KEY_LMETA] = SDLK_LMETA;
	cInputManagerSDL::_keyMap[Input::KEY_LSHIFT] = SDLK_LSHIFT;
	cInputManagerSDL::_keyMap[Input::KEY_LSUPER] = SDLK_LSUPER;
	cInputManagerSDL::_keyMap[Input::KEY_LWIN] = SDLK_LSUPER;
	cInputManagerSDL::_keyMap[Input::KEY_M] = SDLK_m;
	cInputManagerSDL::_keyMap[Input::KEY_MAIL] = SDLK_UNKNOWN;
	cInputManagerSDL::_keyMap[Input::KEY_MEDIASELECT] = SDLK_UNKNOWN;
	cInputManagerSDL::_keyMap[Input::KEY_MEDIASTOP] = SDLK_UNKNOWN;
	cInputManagerSDL::_keyMap[Input::KEY_MENU] = SDLK_MENU;
	cInputManagerSDL::_keyMap[Input::KEY_MINUS] = SDLK_MINUS;
	cInputManagerSDL::_keyMap[Input::KEY_MODE] = SDLK_MODE;
	cInputManagerSDL::_keyMap[Input::KEY_MULTIPLY] = SDLK_UNKNOWN;
	cInputManagerSDL::_keyMap[Input::KEY_MUTE] = SDLK_UNKNOWN;
	cInputManagerSDL::_keyMap[Input::KEY_MYCOMPUTER] = SDLK_UNKNOWN;
	cInputManagerSDL::_keyMap[Input::KEY_N] = SDLK_n;
	cInputManagerSDL::_keyMap[Input::KEY_NEXT] = SDLK_UNKNOWN;
	cInputManagerSDL::_keyMap[Input::KEY_NEXTTRACK] = SDLK_UNKNOWN;
	cInputManagerSDL::_keyMap[Input::KEY_NOCONVERT] = SDLK_UNKNOWN;
	cInputManagerSDL::_keyMap[Input::KEY_NUMLOCK] = SDLK_NUMLOCK;
	cInputManagerSDL::_keyMap[Input::KEY_NUMPAD0] = SDLK_KP0;
	cInputManagerSDL::_keyMap[Input::KEY_NUMPAD1] = SDLK_KP1;
	cInputManagerSDL::_keyMap[Input::KEY_NUMPAD2] = SDLK_KP2;
	cInputManagerSDL::_keyMap[Input::KEY_NUMPAD3] = SDLK_KP3;
	cInputManagerSDL::_keyMap[Input::KEY_NUMPAD4] = SDLK_KP4;
	cInputManagerSDL::_keyMap[Input::KEY_NUMPAD5] = SDLK_KP5;
	cInputManagerSDL::_keyMap[Input::KEY_NUMPAD6] = SDLK_KP6;
	cInputManagerSDL::_keyMap[Input::KEY_NUMPAD7] = SDLK_KP7;
	cInputManagerSDL::_keyMap[Input::KEY_NUMPAD8] = SDLK_KP8;
	cInputManagerSDL::_keyMap[Input::KEY_NUMPAD9] = SDLK_KP9;
	cInputManagerSDL::_keyMap[Input::KEY_NUMPAD_COMMA] = SDLK_COMMA;
	cInputManagerSDL::_keyMap[Input::KEY_NUMPAD_DIVIDE] = SDLK_KP_DIVIDE;
	cInputManagerSDL::_keyMap[Input::KEY_NUMPAD_ENTER] = SDLK_KP_ENTER;
	cInputManagerSDL::_keyMap[Input::KEY_NUMPAD_EQUALS] = SDLK_KP_EQUALS;
	cInputManagerSDL::_keyMap[Input::KEY_NUMPAD_PERIOD] = SDLK_KP_PERIOD;
	cInputManagerSDL::_keyMap[Input::KEY_NUMPAD_MULTIPLY] = SDLK_KP_MULTIPLY;
	cInputManagerSDL::_keyMap[Input::KEY_NUMPAD_MINUS] = SDLK_KP_MINUS;
	cInputManagerSDL::_keyMap[Input::KEY_NUMPAD_PLUS] = SDLK_KP_PLUS;
	cInputManagerSDL::_keyMap[Input::KEY_O] = SDLK_o;
	cInputManagerSDL::_keyMap[Input::KEY_OEM_102] = SDLK_UNKNOWN;
	cInputManagerSDL::_keyMap[Input::KEY_P] = SDLK_p;
	cInputManagerSDL::_keyMap[Input::KEY_PAGEUP] = SDLK_PAGEUP;
	cInputManagerSDL::_keyMap[Input::KEY_PAGEDOWN] = SDLK_PAGEDOWN;
	cInputManagerSDL::_keyMap[Input::KEY_PAUSE] = SDLK_PAUSE;
	cInputManagerSDL::_keyMap[Input::KEY_PERIOD] = SDLK_PERIOD;
	cInputManagerSDL::_keyMap[Input::KEY_PLAYPAUSE] = SDLK_UNKNOWN;
	cInputManagerSDL::_keyMap[Input::KEY_POWER] = SDLK_POWER;
	cInputManagerSDL::_keyMap[Input::KEY_PREVTRACK] = SDLK_UNKNOWN;
	cInputManagerSDL::_keyMap[Input::KEY_PRINT] = SDLK_PRINT;
	cInputManagerSDL::_keyMap[Input::KEY_PRIOR] = SDLK_UNKNOWN;
	cInputManagerSDL::_keyMap[Input::KEY_Q] = SDLK_q;
	cInputManagerSDL::_keyMap[Input::KEY_QUESTION] = SDLK_QUESTION;
	cInputManagerSDL::_keyMap[Input::KEY_QUOTE] = SDLK_QUOTEDBL;
	cInputManagerSDL::_keyMap[Input::KEY_R] = SDLK_r;
	cInputManagerSDL::_keyMap[Input::KEY_RALT] = SDLK_RALT;
	cInputManagerSDL::_keyMap[Input::KEY_RBRACKET] = SDLK_RIGHTBRACKET;
	cInputManagerSDL::_keyMap[Input::KEY_RCONTROL] = SDLK_RCTRL;
	cInputManagerSDL::_keyMap[Input::KEY_RETURN] = SDLK_RETURN;
	cInputManagerSDL::_keyMap[Input::KEY_RIGHT] = SDLK_RIGHT;
	cInputManagerSDL::_keyMap[Input::KEY_RMENU] = SDLK_UNKNOWN;
	cInputManagerSDL::_keyMap[Input::KEY_RMETA] = SDLK_RMETA;
	cInputManagerSDL::_keyMap[Input::KEY_RPAREN] = SDLK_RIGHTPAREN;
	cInputManagerSDL::_keyMap[Input::KEY_RSHIFT] = SDLK_RSHIFT;
	cInputManagerSDL::_keyMap[Input::KEY_RSUPER] = SDLK_RSUPER;
	cInputManagerSDL::_keyMap[Input::KEY_RWIN] = SDLK_RSUPER;
	cInputManagerSDL::_keyMap[Input::KEY_S] = SDLK_s;
	cInputManagerSDL::_keyMap[Input::KEY_SCROLL] = SDLK_SCROLLOCK;
	cInputManagerSDL::_keyMap[Input::KEY_SEMICOLON] = SDLK_SEMICOLON;
	cInputManagerSDL::_keyMap[Input::KEY_SLASH] = SDLK_SLASH;
	cInputManagerSDL::_keyMap[Input::KEY_SLEEP] = SDLK_UNKNOWN;
	cInputManagerSDL::_keyMap[Input::KEY_SPACE] = SDLK_SPACE;
	cInputManagerSDL::_keyMap[Input::KEY_STOP] = SDLK_UNKNOWN;
	cInputManagerSDL::_keyMap[Input::KEY_SUBTRACT] = SDLK_UNKNOWN;
	cInputManagerSDL::_keyMap[Input::KEY_SYSRQ] = SDLK_SYSREQ;
	cInputManagerSDL::_keyMap[Input::KEY_T] = SDLK_t;
	cInputManagerSDL::_keyMap[Input::KEY_TAB] = SDLK_TAB;
	cInputManagerSDL::_keyMap[Input::KEY_U] = SDLK_u;
	cInputManagerSDL::_keyMap[Input::KEY_UNDERLINE] = SDLK_UNDERSCORE;
	cInputManagerSDL::_keyMap[Input::KEY_UNDO] = SDLK_UNDO;
	cInputManagerSDL::_keyMap[Input::KEY_UNLABELED] = SDLK_UNKNOWN;
	cInputManagerSDL::_keyMap[Input::KEY_UP] = SDLK_UP;
	cInputManagerSDL::_keyMap[Input::KEY_V] = SDLK_v;
	cInputManagerSDL::_keyMap[Input::KEY_VOLUMEDOWN] = SDLK_UNKNOWN;
	cInputManagerSDL::_keyMap[Input::KEY_VOLUMEUP] = SDLK_UNKNOWN;
	cInputManagerSDL::_keyMap[Input::KEY_W] = SDLK_w;
	cInputManagerSDL::_keyMap[Input::KEY_WAKE] = SDLK_UNKNOWN;
	cInputManagerSDL::_keyMap[Input::KEY_WEBBACK] = SDLK_UNKNOWN;
	cInputManagerSDL::_keyMap[Input::KEY_WEBFAVORITES] = SDLK_UNKNOWN;
	cInputManagerSDL::_keyMap[Input::KEY_WEBFORWARD] = SDLK_UNKNOWN;
	cInputManagerSDL::_keyMap[Input::KEY_WEBHOME] = SDLK_UNKNOWN;
	cInputManagerSDL::_keyMap[Input::KEY_WEBREFRESH] = SDLK_UNKNOWN;
	cInputManagerSDL::_keyMap[Input::KEY_WEBSEARCH] = SDLK_UNKNOWN;
	cInputManagerSDL::_keyMap[Input::KEY_WEBSTOP] = SDLK_UNKNOWN;
	cInputManagerSDL::_keyMap[Input::KEY_X] = SDLK_x;
	cInputManagerSDL::_keyMap[Input::KEY_Y] = SDLK_y;
	cInputManagerSDL::_keyMap[Input::KEY_YEN] = SDLK_UNKNOWN;
	cInputManagerSDL::_keyMap[Input::KEY_Z] = SDLK_z;
}