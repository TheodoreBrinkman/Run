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
#include <windows.h>
#include <stdlib.h>
#include <vector>
#include "TYPEDEFS.h"
#include "cFileManager.h"
#include "cInputManager.h"
#include "cFontSheet.h"

class cScrollingText
{
public:
	// Constructors
	cScrollingText(unsigned long width, unsigned long height, double speed);
	// Destructors
	virtual ~cScrollingText();

	virtual void Show();
	virtual void LoadText(STRING filePath);
	virtual void LoadText(std::vector<STRING> text);

protected:
	std::vector<STRING> _lines;

private:
	unsigned long _screenWidth;
	unsigned long _screenHeight;
	double _speed;
	cFontSheet *_fontSheet;
};