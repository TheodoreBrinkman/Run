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
#include <map>
#include "TYPEDEFS.h"
#include "cFontSheet.h"
#include "ICanvas.h"
#include "cInputManager.h"
#include "STRUCTURES.H"

class cMenu
{
public:
	// Constructor
	cMenu(unsigned long width, unsigned long height, STRING menuTitle);
	cMenu(unsigned long width, unsigned long height, STRING menuTitle, std::vector<STRING> menuItems);
	// Destructor
	~cMenu();

	void AddItem(STRING itemText);
	void Show();
	STRING Selection();

	static STRING ESCAPE;
	static STRING PLAY;
	static STRING CREDITS;
	static STRING EXIT;

private:
	POINT2D _size;
	cFontSheet* _titleFontSheet;
	cFontSheet* _fontSheet;
	ICanvas* _menuImage;
	STRING _menuTitle;
	std::vector<STRING> _menuItems;
	bool _selected;
	unsigned long _selectedIndex;

	void _Init(unsigned long width, unsigned long height, STRING menuTitle);
	void _Draw(unsigned long selectedIndex);
};