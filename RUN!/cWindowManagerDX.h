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
#include <stdlib.h>
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "IWindowManager.h"
#include "TYPEDEFS.h"
#include "Enums.h"

class cWindowManagerDX
	: public IWindowManager
{
#pragma message("-- cWindowManagerDX is included")

public:
	// Constructors
	cWindowManagerDX(STRING title, unsigned long width, unsigned long height, bool isFullscreen, HINSTANCE hInstance, int nCmdShow);

	// Public Methods
	HWND hWnd();

	// Destructor
	~cWindowManagerDX();

private:
	// Private Members
	ATOM _registration;
	long _windowStyle;
	HWND _hWnd;
	STRING _title;
	unsigned long _width;
	unsigned long _height;
	bool _isFullscreen;

	// Private Methods
	static LRESULT WINAPI WinProc(HWND, UINT, WPARAM, LPARAM);
	ATOM MyRegisterClass(HINSTANCE hInstance);

	// Interface Methods
	virtual STRING title();
	virtual unsigned long width();
	virtual unsigned long height();
	virtual bool isFullscreen();

	virtual WindowManager::eWindowType windowType();
	virtual GraphicsManager::eRenderingMethod renderingMethod();
	virtual InputManager::eInputMethod inputMethod();
	virtual AudioManager::eAudioMethod audioMethod();

	virtual void Release();
};