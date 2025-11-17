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
#include "cWindowManagerSDL.h"

// STATIC INITIALIZATION
int cWindowManagerSDL::SCREEN_BPP = 32;

// CONSRUCTORS
cWindowManagerSDL::cWindowManagerSDL(STRING title, unsigned long width, unsigned long height, bool isFullscreen)
{
	this->_title = title;
	this->_width = width;
	this->_height = height;
	this->_isFullscreen = isFullscreen;

	// create the window!
	if(-1 == SDL_Init(SDL_INIT_EVERYTHING))
    {
        throw("cWindowManagerSDL::cWindowManagerSDL() - Could not initialize SDL.");
    }
	
	SDL_Surface *screen = SDL_SetVideoMode((int)this->_width, (int)this->_height, (!isFullscreen) ? 0 : cWindowManagerSDL::SCREEN_BPP, SDL_SWSURFACE);
    if(NULL == this->_screen)
    {
        throw("cWindowManagerSDL::cWindowManagerSDL() - Error setting up the screen.");
    }

	//Set the window caption
	std::string SDLTitle(this->_title.begin(), this->_title.end());
	SDLTitle.assign(this->_title.begin(), this->_title.end());
	SDL_WM_SetCaption(SDLTitle.c_str(), NULL);
}

// DESTRUCTOR
cWindowManagerSDL::~cWindowManagerSDL()
{
	if(NULL != this->_screen)
	{
		SDL_FreeSurface(this->_screen);
		this->_screen = NULL;
	}
}

//INTERFACE METHODS
STRING cWindowManagerSDL::title()
{
	return(this->_title);
}

unsigned long cWindowManagerSDL::width()
{
	return(this->_width);
}

unsigned long cWindowManagerSDL::height()
{
	return(this->_height);
}

bool cWindowManagerSDL::isFullscreen()
{
	return(this->_isFullscreen);
}

SDL_Surface* cWindowManagerSDL::screen()
{
	return(SDL_GetVideoSurface());
}

WindowManager::eWindowType cWindowManagerSDL::windowType()
{
	return(WindowManager::SDL);
}

GraphicsManager::eRenderingMethod cWindowManagerSDL::renderingMethod()
{
	return(GraphicsManager::SDL);
}

InputManager::eInputMethod cWindowManagerSDL::inputMethod()
{
//	return(InputManager::SDL);
	return(InputManager::Raw);
}

AudioManager::eAudioMethod cWindowManagerSDL::audioMethod()
{
	return(AudioManager::SDL);
}

void cWindowManagerSDL::Release()
{
}