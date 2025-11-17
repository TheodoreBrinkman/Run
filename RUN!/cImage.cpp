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
#include "cImage.h"

// PUBLIC METHODS
cImage::cImage(STRING key, unsigned long width, unsigned long height, cColor *bgColor)
{
	this->_Init(key, width, height, bgColor);
}
cImage::cImage(STRING imageFilePath)
{
	this->_Init(imageFilePath, NULL);
}
cImage::cImage(STRING imageFilePath, cColor *transparentColor)
{
	// load the file
	this->_Init(imageFilePath, transparentColor);
}
ICanvas* cImage::GetCanvas()
{
	return(this->_canvas);
}
cImage::~cImage()
{
	this->_canvas->Release();
}

// PRIVATE METHODS
cImage::cImage()
{
	this->_Init();
}
void cImage::_Init()
{
	this->_canvas = NULL;
	this->_width = 0;
	this->_height = 0;
}
void cImage::_Init(STRING key, unsigned long width, unsigned long height, cColor *bgColor)
{
	this->_canvas = cGraphicsManager::RegisterSurface(key, width, height, bgColor);
}
void cImage::_Init(STRING imageFilePath, cColor *transparentColor)
{
	this->_canvas = cGraphicsManager::RegisterSpriteSheet(imageFilePath, transparentColor);
}
void cImage::_Init(STRING imageFilePath, cColor *transparentColor, cColor *bgColor)
{
	this->_canvas = cGraphicsManager::RegisterBackgroundImage(imageFilePath, transparentColor, bgColor);
}
