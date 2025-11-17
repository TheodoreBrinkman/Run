/******************************************************************************\
*                                                                              *
*	Copyright © 2010 Andrew Dabrowski, Theo Brinkman. All rights reserved.     *
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
#include "cColor.h"
#include "ICanvas.h"

class cCanvasSDL : public ICanvas
{
#pragma message ("-- cCanvasSDL is included --")
public:
	cCanvasSDL(SDL_Surface *SDLSurface, unsigned long width, unsigned long height);
	~cCanvasSDL();

	
	SDL_Surface* GetSurface();
	
	virtual void Release();

protected:
	SDL_Surface *_surface;


private:
	// members
	unsigned long _width;
	unsigned long _height;

	// Interface
	virtual cRect* Size();

};