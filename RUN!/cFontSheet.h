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
#include "cTileSet.h"

class cFontSheet :
	public cImage
{
public:
	cFontSheet();
	~cFontSheet();

	void Draw(cRect *destRect, STRING string);
	void DrawCharacter(cRect *destRect, TCHAR character);
	POINT2D GetSize(STRING string);

private:
	std::map<TCHAR, cRect*> _sprites;

	cRect* _GetRect(TCHAR character);

	static STRING IMAGE_FILE_PATH;
};