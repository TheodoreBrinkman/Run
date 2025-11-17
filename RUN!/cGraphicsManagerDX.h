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
#pragma once
#include <stdlib.h>
#include <map>
#include <d3d9.h>
#include <d3dx9.h>
#include "TYPEDEFS.h"
#include "Enums.h"
#include "cWindowManagerDX.h"
#include "IGraphicsManager.h"
#include "ICanvas.h"
#include "cCanvasDX.h"
#include "cColor.h"

class cGraphicsManagerDX
	: public IGraphicsManager
{
#pragma message("-- cGraphicsManagerDX is included")
public:
	// Constructors
	cGraphicsManagerDX(IWindowManager *window);
	~cGraphicsManagerDX();

private:
	// Private Members
	LPDIRECT3D9 _d3d;
	LPDIRECT3DDEVICE9 _d3ddev;
	LPD3DXSPRITE _spriteHandler;
	LPDIRECT3DSURFACE9 _backbuffer;

	std::map<STRING, cCanvasDX*> _canvases;
	std::map<STRING, unsigned long> _references;

	HWND _hWnd;
	unsigned long _width;
	unsigned long _height;
	bool _fullscreen;

	void cGraphicsManagerDX::_Initialize(cWindowManagerDX *window);

	// Interface Methods
	virtual cCanvasDX* RegisterSurface(STRING key, unsigned long width, unsigned long height, cColor *bgColor);
	virtual cCanvasDX* RegisterBackgroundImage(STRING imageFilePath, cColor *transparentColor, cColor *bgColor);
	virtual cCanvasDX* RegisterSpriteSheet(STRING imageFilePath, cColor *transparentColor);

	virtual void ReleaseSurface(STRING key);
	virtual void ReleaseBackgroundImage(STRING imageFilePath);
	virtual void ReleaseSpriteSheet(STRING imageFilePath);

	virtual void Clear(ICanvas *canvas);
	virtual void Clear(ICanvas* canvas, cColor *bgColor);
	void _Clear(cCanvasDX* canvas, cColor *bgColor);

	virtual void Draw(cRect *destRect, ICanvas *srcCanvas);
	virtual void Draw(cRect *destRect, ICanvas *srcCanvas, bool flipped);
	virtual void Draw(cRect *destRect, ICanvas *srcCanvas, cRect *srcRect);
	virtual void Draw(cRect *destRect, ICanvas *srcCanvas, cRect *srcRect, bool flipped);
	virtual void Draw(ICanvas *destCanvas, cRect *destRect, ICanvas *srcCanvas, cRect *srcRect);
	virtual void Draw(ICanvas *destCanvas, cRect *destRect, ICanvas *srcCanvas, cRect *srcRect, bool flipped);
	void _Draw(cRect *destRect, cCanvasDX *srcCanvas, cRect *srcRect, bool flipped);
	void _Draw(cCanvasDX *destCanvas, cRect *destRect, cCanvasDX *srcCanvas, cRect *srcRect, bool flipped);
	
	virtual bool BeginScene();
	virtual void EndScene();

	virtual void Release();

	// INTERNAL ONLY

	// Private Methods
	D3DXIMAGE_INFO _GetImageInfo(STRING imageFilePath);
	LPDIRECT3DSURFACE9 _GetSurface(unsigned long width, unsigned long height, cColor *bgColor);
	void _LoadSurface(LPDIRECT3DSURFACE9 surface, STRING imageFilePath, cColor *transparentColor);
	LPDIRECT3DTEXTURE9 _LoadTexture(STRING imageFilePath, D3DXIMAGE_INFO info, cColor *transparentColor);
	bool _Exists(STRING key);
	void _Release(STRING key);

	// Private Static
	static RECT ToRect(cRect* rect);
	static cRect* ToRect(RECT rect);
	static D3DXVECTOR3 ToVector(cRect *rect);
	static D3DXVECTOR3 ToCenter(cRect *rect);
	static D3DCOLOR ToColor(cColor* color);
	static cColor* ToColor(D3DCOLOR color);
};