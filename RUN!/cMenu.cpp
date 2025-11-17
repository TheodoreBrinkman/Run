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
#include "cMenu.h"

// STATIC INITIALIZATIONS
STRING cMenu::ESCAPE = STRING(TEXT(""));
STRING cMenu::PLAY = STRING(TEXT("Play Game"));
STRING cMenu::CREDITS = STRING(TEXT("Credits"));
STRING cMenu::EXIT = STRING(TEXT("Exit"));

// CONSTRUCTORS
cMenu::cMenu(unsigned long width, unsigned long height, STRING menuTitle)
{
	this->_Init(width, height, menuTitle);
}
cMenu::cMenu(unsigned long width, unsigned long height, STRING menuTitle, std::vector<STRING> menuItems)
{
	this->_Init(width, height, menuTitle);
	for each(STRING item in menuItems)
	{
		this->_menuItems.push_back(item);
	}
}

// DESTRUCTORS
cMenu::~cMenu()
{
}

// PUBLIC METHODS
void cMenu::Show()
{
	unsigned long itemCount = this->_menuItems.size();
	while(!this->_selected)
	{
		cInputManager::PollInputs();
		if(cGraphicsManager::BeginScene())
		{
			this->_Draw(this->_selectedIndex);
			cGraphicsManager::EndScene();
			if(cInputManager::KeyPress(Input::KEY_RETURN) || cInputManager::KeyPress(Input::KEY_SPACE))
			{
				this->_selected = true;
			}
			else if(cInputManager::KeyPress(Input::KEY_DOWN))
			{
				this->_selectedIndex = (this->_selectedIndex + 1 + itemCount) % itemCount;
			}
			else if(cInputManager::KeyPress(Input::KEY_UP))
			{
				this->_selectedIndex = (this->_selectedIndex - 1 + itemCount) % itemCount;
			}
			else if(cInputManager::KeyPress(Input::KEY_ESCAPE))
			{
				this->_selectedIndex = -1;
				this->_selected = true;
			}
		}
	}
}

STRING cMenu::Selection()
{
	if(-1 == this->_selectedIndex)
	{
		return(cMenu::ESCAPE);
	}
	return(this->_menuItems[this->_selectedIndex]);
}

void cMenu::AddItem(STRING itemText)
{
	this->_menuItems.push_back(itemText);
}

// PRIVATE METHODS
void cMenu::_Init(unsigned long width, unsigned long height, STRING menuTitle)
{
	this->_menuImage = NULL;
	this->_size.x = width;
	this->_size.y = height;
	this->_selected = false;
	this->_menuTitle = menuTitle;
	this->_fontSheet = new cFontSheet();
	this->_selected = false;
	this->_selectedIndex = 0;

	this->AddItem(cMenu::PLAY);
	this->AddItem(cMenu::CREDITS);
	this->AddItem(cMenu::EXIT);
}

void cMenu::_Draw(unsigned long selectedIndex)
{
	// Draw the menu Image
	if(NULL != this->_menuImage)
	{
		cGraphicsManager::Draw(new cRect(10, 100, 900, 60), this->_menuImage);
	}
	// Draw the menu Title
	this->_fontSheet->Draw(new cRect(70, 100, 900, 100), this->_menuTitle);

	long top = 150;
	for(unsigned long i=0;i<this->_menuItems.size();i++)
	{
		STRING item = this->_menuItems[i];
		// calculate the horizontal position
		POINT2D textSize = this->_fontSheet->GetSize(item);
		long left = (long)((this->_size.x - textSize.x) / 2);
		if(i == selectedIndex)
		{
			STRING indicator = TEXT("* ");
			POINT2D indicatorSize = this->_fontSheet->GetSize(indicator);
			this->_fontSheet->Draw(new cRect(top, left - (unsigned long)indicatorSize.x, left , top + (unsigned long)indicatorSize.y), indicator);
		}
		// Draw the item
		this->_fontSheet->Draw(new cRect(top, left, left + (unsigned long)textSize.x, top + (unsigned long)textSize.y), item);
		top += (unsigned long)(textSize.y * 2);
	}
}