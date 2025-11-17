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
#include "cColor.h"
#include "cGraphicsManager.h"

class cImage
{
#pragma message("-- cImage is included")
public:
	// Constructors
	cImage(STRING key, unsigned long width, unsigned long height, cColor *bgColor);
	cImage(STRING imageFilePath);
	cImage(STRING imageFilePath, cColor *transparentColor);
	// Methods
	ICanvas* GetCanvas();
	// Destructor
	~cImage();

protected:
	ICanvas *_canvas;
	unsigned long _width;
	unsigned long _height;
	// Constructors
	cImage();

private:
	void _Init();
	void _Init(STRING key, unsigned long width, unsigned long height, cColor *bgColor);
	void _Init(STRING imageFilePath, cColor *transparentColor);
	void _Init(STRING imageFilePath, cColor *transparentColor, cColor *bgColor);
};