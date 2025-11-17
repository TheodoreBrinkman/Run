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
#include <d3d9.h>
#include <d3dx9.h>
#include "cColor.h"
#include "ICanvas.h"

class cCanvasDX : public ICanvas
{
#pragma message("-- cCanvasDX is included")
public:
	// Constructors
	cCanvasDX(LPDIRECT3DSURFACE9 d3dSurface, unsigned long width, unsigned long height);
	cCanvasDX(LPDIRECT3DTEXTURE9 d3dTexture, unsigned long width, unsigned long height);
	~cCanvasDX();

	LPDIRECT3DSURFACE9 GetSurface();
	LPDIRECT3DTEXTURE9 GetTexture();
	virtual void Release();

protected:
	LPDIRECT3DSURFACE9 _surface;
	LPDIRECT3DTEXTURE9 _texture;

private:
	// members
	unsigned long _width;
	unsigned long _height;

	// Interface
	virtual cRect* Size();
};
