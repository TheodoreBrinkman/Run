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
#include <stdlib.h>
#include <map>
#include "TYPEDEFS.h"
#include "Enums.h"
#include "IWindowManager.h"
#include "cWindowManager.h"
#include "cWindowManagerSDL.h"
#include "IGraphicsManager.h"
#include "ICanvas.h"
#include "SDL.h"
#include "SDL_image.h"
#include "cCanvasSDL.h"
#include "cColor.h"

class cGraphicsManagerSDL
	: public IGraphicsManager
{
	#pragma message("-- cGraphicsManagerSDL is included")
public:
	// Constructors
	cGraphicsManagerSDL(IWindowManager *window);

	// Public Methods
	void setScreenSurface(SDL_Surface* surface);

	// Destructor
	~cGraphicsManagerSDL();

private:
	void _Initialize(cWindowManagerSDL *window);

	//Private members:
	STRING _title;
	unsigned long _width;
	unsigned long _height;
	bool _fullscreen;

	std::map<STRING, cCanvasSDL*> _canvases;
	std::map<STRING, unsigned long> _references;

	//interface methods:
	virtual cCanvasSDL* RegisterSurface(STRING key, unsigned long width, unsigned long height, cColor *bgColor);
	virtual cCanvasSDL* RegisterBackgroundImage(STRING imageFilePath, cColor *transparentColor, cColor *bgColor);
	virtual cCanvasSDL* RegisterSpriteSheet(STRING imageFilePath, cColor *transparentColor);

	virtual cCanvasSDL* RegisterSpriteSheet(STRING imageFilePath);

	virtual void ReleaseSurface(STRING key);
	virtual void ReleaseBackgroundImage(STRING imageFilePath);
	virtual void ReleaseSpriteSheet(STRING imageFilePath);

	virtual void Clear(ICanvas *canvas);
	virtual void Clear(ICanvas *canvas, cColor *bgColor);
	void _Clear(cCanvasSDL *canvas, cColor *bgColor);

	virtual void Draw(cRect *destRect, ICanvas *srcCanvas);
	virtual void Draw(cRect *destRect, ICanvas *srcCanvas, bool flipped);
	virtual void Draw(cRect *destRect, ICanvas *srcCanvas, cRect *srcRect);
	virtual void Draw(cRect *destRect, ICanvas *srcCanvas, cRect *srcRect, bool flipped);
	virtual void Draw(ICanvas *destCanvas, cRect *destRect, ICanvas *srcCanvas, cRect *srcRect);
	virtual void Draw(ICanvas *destCanvas, cRect *destRect, ICanvas *srcCanvas, cRect *srcRect, bool flipped);
	void _Draw(cRect *destRect, cCanvasSDL *srcCanvas, cRect *srcRect, bool flipped);
	void _Draw(cCanvasSDL *destCanvas, cRect *destRect, cCanvasSDL *srcCanvas, cRect *srcRect, bool flipped);
	void _Draw(SDL_Surface *destSurface, cRect *destRect, SDL_Surface *srcSurface, cRect *srcRect, bool flipped);

	virtual bool BeginScene();
	virtual void EndScene();

	virtual void Release();

	//internal use only:

	// Private Methods
	SDL_Surface* _GetSurface();
	void _LoadSurface(SDL_Surface *surface, STRING imageFilePath, cColor *transparentColor);
	
	SDL_Surface* _LoadTexture(STRING imageFilePath, cColor *transparentColor);
	bool _Exists(STRING key);
	void _Release(STRING key);

	// Private Static
	static SDL_Rect ToRect(cRect* rect);
	static cRect* ToRect(SDL_Rect rect);
	//static D3DXVECTOR3 ToVector(cRect *rect);
	//static D3DXVECTOR3 ToCenter(cRect *rect);
	static SDL_Color* ToColor(cColor *color);
	static cColor* ToColor(SDL_Color *color);

	static SDL_Surface* _CopyRect(SDL_Surface *surface, cRect *rect);
	static Uint32 _GetPixel(SDL_Surface *surface, int x, int y);
	static void _SetPixel(SDL_Surface *surface, int x, int y, Uint32 value);
	static void _FlipSurface(SDL_Surface *surface);
};