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
#include "IWindowManager.h"
#include "cWindowManager.h"
#include "cGraphicsManagerDX.h"
#include "cGraphicsManagerSDL.h"

class cGraphicsManager
{
#pragma message("-- cGraphicsManager is included")
public:
	// Interface Methods
	static void Initialize();
	static bool IsInitialized();

	static ICanvas* RegisterSurface(STRING key, unsigned long width, unsigned long height, cColor *bgColor);
	static ICanvas* RegisterBackgroundImage(STRING imageFilePath, cColor *transparentColor, cColor *bgColor);
	static ICanvas* RegisterSpriteSheet(STRING imageFilePath, cColor *transparentColor);

	static void ReleaseSurface(STRING key);
	static void ReleaseBackgroundImage(STRING imageFilePath);
	static void ReleaseSpriteSheet(STRING imageFilePath);

	static void Draw(cRect *destRect, ICanvas *srcCanvas);
	static void Draw(cRect *destRect, ICanvas *srcCanvas, bool flipped);
	static void Draw(cRect *destRect, ICanvas *srcCanvas, cRect *srcRect);
	static void Draw(cRect *destRect, ICanvas *srcCanvas, cRect *srcRect, bool flipped);
	static void Draw(ICanvas *destCanvas, cRect *destRect, ICanvas *srcCanvas, cRect *srcRect);
	static void Draw(ICanvas *destCanvas, cRect *destRect, ICanvas *srcCanvas, cRect *srcRect, bool flipped);

	static bool BeginScene();
	static void EndScene();

	static void Release();

private:
	// Private Members
	static IGraphicsManager *_manager;
};
