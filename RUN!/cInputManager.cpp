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
#include "cInputManager.h"

// MEMBERS
IInputManager *cInputManager::_manager = NULL;

// CONSTRUCTORS
void cInputManager::Initialize()
{
	cInputManager::_manager = NULL;
	switch(cWindowManager::window()->inputMethod())
	{
		case InputManager::Raw:
			cInputManager::_manager = new cInputManagerRaw();
			break;
		case InputManager::DirectInput:
			cInputManager::_manager = new cInputManagerDX(cWindowManager::window());
			break;
		case InputManager::SDL:
			cInputManager::_manager = new cInputManagerSDL();
			break;
		case InputManager::OpenGL:
			throw("cInputManager::Initialize(OpenGL) - Not yet implemented.");
			break;
		case InputManager::CoreInput:
			throw("cInputManager::Initialize(CoreInput) - Not yet implemented.");
			break;
		default:
			throw("cInputManager::Initialize(Unknown) - Not yet implemented.");
			break;
	}
}
bool cInputManager::IsInitialized()
{
	return(NULL != cInputManager::_manager);
}

void cInputManager::PollInputs()
{
	cInputManager::_manager->PollInputs();
}

bool cInputManager::KeyDown(Input::KeyCodes key)
{
	return(cInputManager::_manager->KeyDown(key));
}
bool cInputManager::KeyWasDown(Input::KeyCodes key)
{
	return(cInputManager::_manager->KeyWasDown(key));
}
bool cInputManager::KeyPress(Input::KeyCodes key)
{
	return(cInputManager::_manager->KeyPress(key));
}
bool cInputManager::KeyHeld(Input::KeyCodes key)
{
	return(cInputManager::_manager->KeyHeld(key));
}

long cInputManager::MouseX()
{
	return(cInputManager::_manager->MouseX());
}
long cInputManager::MouseY()
{
	return(cInputManager::_manager->MouseY());
}
bool cInputManager::MouseButtonDown(int button)
{
	return(cInputManager::_manager->MouseButtonDown(button));
}

void cInputManager::Release()
{
	cInputManager::_manager->Release();
}