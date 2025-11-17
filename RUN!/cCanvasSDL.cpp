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
#include "cCanvasSDL.h"

// STATIC INITIALIZATION
// none

// CONSTRUCTORS
cCanvasSDL::cCanvasSDL(SDL_Surface *SDLSurface, unsigned long width, unsigned long height)
{
	this->_surface = SDLSurface;
	this->_width = width;
	this->_height = height;
}

cCanvasSDL::~cCanvasSDL()
{
	this->Release();
}

SDL_Surface* cCanvasSDL::GetSurface()
{
	return this->_surface;
}

cRect* cCanvasSDL::Size()
{
	return(new cRect(this->_width, this->_height));
}

void cCanvasSDL::Release()
{
	if(NULL != this->_surface)
	{
		SDL_FreeSurface( _surface );
		this->_surface = NULL;
	}
}