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
#include "cWindowManager.h"

// STATIC INITIALIZATION
IWindowManager* cWindowManager::_manager = NULL;

// FACTORY METHODS
void cWindowManager::CreateWindowDX(STRING title, unsigned long width, unsigned long height, bool isFullscreen, HINSTANCE hInstance, int nCmdShow)
{
	cWindowManager::_manager = new cWindowManagerDX(title, width, height, isFullscreen, hInstance, nCmdShow);
}

void cWindowManager::CreateWindowSDL(STRING title, unsigned long width, unsigned long height, bool isFullscreen)
{
	cWindowManager::_manager = new cWindowManagerSDL(title, width, height, isFullscreen);
}

// PUBLIC METHODS
bool cWindowManager::IsInitialized()
{
	return(NULL != cWindowManager::_manager);
}

IWindowManager* cWindowManager::window()
{
	return(cWindowManager::_manager);
}

unsigned long cWindowManager::width()
{
	return(cWindowManager::_manager->width());
}

unsigned long cWindowManager::height()
{
	return(cWindowManager::_manager->height());
}

bool cWindowManager::isFullscreen()
{
	return(cWindowManager::_manager->isFullscreen());
}

void cWindowManager::Release()
{
	if(NULL != cWindowManager::_manager)
	{
		cWindowManager::_manager->Release();
		cWindowManager::_manager = NULL;
	}
}