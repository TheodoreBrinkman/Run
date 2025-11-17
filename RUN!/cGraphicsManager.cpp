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
#include "cGraphicsManager.h"

// MEMBERS
IGraphicsManager *cGraphicsManager::_manager = NULL;
SDL_Surface *AppScreen = NULL;

// CONSTRUCTORS
void cGraphicsManager::Initialize()
{
	cGraphicsManager::_manager = NULL;
	switch(cWindowManager::window()->renderingMethod())
	{
		case GraphicsManager::Direct3D:
			cGraphicsManager::_manager = new cGraphicsManagerDX(cWindowManager::window());
			break;
		case GraphicsManager::SDL:
			cGraphicsManager::_manager = new cGraphicsManagerSDL(cWindowManager::window());
			break;
		case GraphicsManager::OpenGL:
			throw("cGraphicsManager::Initialize(OpenGL) - Not yet implemented.");
			break;
		case GraphicsManager::CoreAnimation:
			throw("cGraphicsManager::Initialize(CoreAnimation) - Not yet implemented.");
			break;
		default:
			throw("cGraphicsManager::Initialize(Unknown) - Not yet implemented.");
			break;
	}
}

bool cGraphicsManager::IsInitialized()
{
	return(NULL != cGraphicsManager::_manager);
}

// Interface Methods
ICanvas* cGraphicsManager::RegisterSurface(STRING key, unsigned long width, unsigned long height, cColor *bgColor)
{
	return(cGraphicsManager::_manager->RegisterSurface(key, width, height, bgColor));
}
ICanvas* cGraphicsManager::RegisterBackgroundImage(STRING imageFilePath, cColor *transparentColor, cColor *bgColor)
{
	return(cGraphicsManager::_manager->RegisterBackgroundImage(imageFilePath, transparentColor, bgColor));
}
ICanvas* cGraphicsManager::RegisterSpriteSheet(STRING imageFilePath, cColor *transparentColor)
{
	return(cGraphicsManager::_manager->RegisterSpriteSheet(imageFilePath, transparentColor));
}

void cGraphicsManager::ReleaseSurface(STRING key)
{
	cGraphicsManager::_manager->ReleaseSurface(key);
}
void cGraphicsManager::ReleaseBackgroundImage(STRING imageFilePath)
{
	cGraphicsManager::_manager->ReleaseBackgroundImage(imageFilePath);
}
void cGraphicsManager::ReleaseSpriteSheet(STRING imageFilePath)
{
	cGraphicsManager::_manager->ReleaseSpriteSheet(imageFilePath);
}

void cGraphicsManager::Draw(cRect *destRect, ICanvas *srcCanvas)
{
	cGraphicsManager::_manager->Draw(destRect, srcCanvas, srcCanvas->Size(), false);
}
void cGraphicsManager::Draw(cRect *destRect, ICanvas *srcCanvas, bool flipped)
{
	cGraphicsManager::_manager->Draw(destRect, srcCanvas, srcCanvas->Size(), flipped);
}
void cGraphicsManager::Draw(cRect *destRect, ICanvas *srcCanvas, cRect *srcRect)
{
	cGraphicsManager::_manager->Draw(destRect, srcCanvas, srcRect, false);
}
void cGraphicsManager::Draw(cRect *destRect, ICanvas *srcCanvas, cRect *srcRect, bool flipped)
{
	cGraphicsManager::_manager->Draw(destRect, srcCanvas, srcRect, flipped);
}
void cGraphicsManager::Draw(ICanvas *destCanvas, cRect *destRect, ICanvas *srcCanvas, cRect *srcRect)
{
	cGraphicsManager::_manager->Draw(destCanvas, destRect, srcCanvas, srcRect, false);
}
void cGraphicsManager::Draw(ICanvas *destCanvas, cRect *destRect, ICanvas *srcCanvas, cRect *srcRect, bool flipped)
{
	cGraphicsManager::_manager->Draw(destCanvas, destRect, srcCanvas, srcRect, flipped);
}

bool cGraphicsManager::BeginScene()
{
	return(cGraphicsManager::_manager->BeginScene());
}
void cGraphicsManager::EndScene()
{
	cGraphicsManager::_manager->EndScene();
}

void cGraphicsManager::Release()
{
	if(NULL != cGraphicsManager::_manager)
	{
		cGraphicsManager::_manager->Release();
		cGraphicsManager::_manager = NULL;
	}
}