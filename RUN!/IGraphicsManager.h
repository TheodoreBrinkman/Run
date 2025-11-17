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
#include "TYPEDEFS.h"
#include "ICanvas.h"
#include "cColor.h"

class IGraphicsManager
{
#pragma message("-- IGraphicsManager is included")
public:
	virtual ICanvas* RegisterSurface(STRING key, unsigned long width, unsigned long height, cColor *bgColor) = 0;
	virtual ICanvas* RegisterBackgroundImage(STRING imageFilePath, cColor *transparentColor, cColor *bgColor) = 0;
	virtual ICanvas* RegisterSpriteSheet(STRING imageFilePath, cColor *transparentColor) = 0;

	virtual void ReleaseSurface(STRING key) = 0;
	virtual void ReleaseBackgroundImage(STRING imageFilePath) = 0;
	virtual void ReleaseSpriteSheet(STRING imageFilePath) = 0;

	virtual void Draw(cRect *destRect, ICanvas *srcCanvas) = 0;
	virtual void Draw(cRect *destRect, ICanvas *srcCanvas, bool flipped) = 0;
	virtual void Draw(cRect *destRect, ICanvas *srcCanvas, cRect *srcRect) = 0;
	virtual void Draw(cRect *destRect, ICanvas *srcCanvas, cRect *srcRect, bool flipped) = 0;
	virtual void Draw(ICanvas *destCanvas, cRect *destRect, ICanvas *srcCanvas, cRect *srcRect) = 0;
	virtual void Draw(ICanvas *destCanvas, cRect *destRect, ICanvas *srcCanvas, cRect *srcRect, bool flipped) = 0;

	virtual bool BeginScene() = 0;
	virtual void EndScene() = 0;

	virtual void Release() = 0;

	virtual ~IGraphicsManager() {};
};