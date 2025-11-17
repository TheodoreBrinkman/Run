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
#include "SDL.h"
#include "SDL_image.h"
#include "IWindowManager.h"
#include "TYPEDEFS.h"
#include "Enums.h"

class cWindowManagerSDL
	: public IWindowManager
{
#pragma message("-- cWindowManagerSDL is included")

public:
	// Constructors
	cWindowManagerSDL(STRING title, unsigned long width, unsigned long height, bool isFullscreen);

	// Public Methods
	SDL_Surface* screen();

	// Destructor
	~cWindowManagerSDL();

private:
	// Private Members
	SDL_Surface* _screen;
	STRING _title;
	unsigned long _width;
	unsigned long _height;
	bool _isFullscreen;

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

	static int SCREEN_BPP;
};