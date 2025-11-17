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
#include "cWindowManagerDX.h"

// STATIC INITIALIZATIONS

// CONSTRUCTORS
cWindowManagerDX::cWindowManagerDX(STRING title, unsigned long width, unsigned long height, bool isFullscreen, HINSTANCE hInstance, int nCmdShow)
{
	this->_title = title;
	this->_width = width;
	this->_height = height;
	this->_isFullscreen = isFullscreen;

	// register the class
	this->_registration = this->MyRegisterClass(hInstance);
	this->_windowStyle = (isFullscreen) ? WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP : WS_OVERLAPPEDWINDOW;

	// create the window
	this->_hWnd = CreateWindow(title.c_str(), title.c_str(), this->_windowStyle, CW_USEDEFAULT, CW_USEDEFAULT, this->_width, this->_height, NULL, NULL, hInstance, NULL);
	if(NULL == this->_hWnd)
	{
		throw("cWindowManager - Could not create window.");
	}
	// display the window
	ShowWindow(this->_hWnd, nCmdShow);
	UpdateWindow(this->_hWnd);
}

// DESTRUCTOR
cWindowManagerDX::~cWindowManagerDX()
{
}

// PUBLIC METHODS
HWND cWindowManagerDX::hWnd()
{
	return(this->_hWnd);
}

// INTERFACE METHODS
	STRING cWindowManagerDX::title()
	{
		return(this->_title);
	}

	unsigned long cWindowManagerDX::width()
	{
		return(this->_width);
	}

	unsigned long cWindowManagerDX::height()
	{
		return(this->_height);
	}

	bool cWindowManagerDX::isFullscreen()
	{
		return(this->_isFullscreen);
	}

	WindowManager::eWindowType cWindowManagerDX::windowType()
	{
		return(WindowManager::DirectX);
	}

	GraphicsManager::eRenderingMethod cWindowManagerDX::renderingMethod()
	{
		return(GraphicsManager::Direct3D);
	}

	InputManager::eInputMethod cWindowManagerDX::inputMethod()
	{
		return(InputManager::Raw);
	}

	AudioManager::eAudioMethod cWindowManagerDX::audioMethod()
	{
		return(AudioManager::DirectSound);
	}

	void Release()
	{
	}

// PRIVATE METHODS

// window event callback function
LRESULT WINAPI cWindowManagerDX::WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			return(0);
	}
	return(DefWindowProc(hWnd, msg, wParam, lParam));
}

// helper function to set up the window properties
ATOM cWindowManagerDX::MyRegisterClass(HINSTANCE hInstance)
{
	// create the window class structure
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	// fill the struct with info
	wc.lpfnWndProc = (WNDPROC)cWindowManagerDX::WinProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = this->_title.c_str();
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hIconSm = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;

	// set up the window with the class info
	return(RegisterClassEx(&wc));
}

void cWindowManagerDX::Release()
{
	PostMessage(this->_hWnd, WM_DESTROY, 0, 0);
}