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
#include "cTileSet.h"

cTileSet::cTileSet(STRING imageFilePath, unsigned long tileWidth, unsigned long tileHeight)
	: cImage(imageFilePath)
{
	this->_tileWidth = tileWidth;
	this->_tileHeight = tileHeight;
	unsigned long tilesWide = (unsigned long)(this->_canvas->Size()->Right / this->_tileWidth);
	unsigned long tilesHigh = (unsigned long)(this->_canvas->Size()->Bottom / this->_tileHeight);
	for(unsigned long y=0;y<tilesHigh;y++)
	{
		for(unsigned long x=0;x<tilesWide;x++)
		{
			unsigned long top = y * this->_tileHeight;
			unsigned long left = x * this->_tileWidth;
			this->_tiles.push_back(new cRect(top, left, left+this->_tileWidth, top+this->_tileHeight));
		}
	}
}

cTileSet::~cTileSet()
{
}

// PUBLIC METHODS
unsigned long cTileSet::TileWidth()
{
	return(this->_tileWidth);
}
unsigned long cTileSet::TileHeight()
{
	return(this->_tileHeight);
}
void cTileSet::DrawTile(cRect *destRect, unsigned long index)
{
	cGraphicsManager::Draw(destRect, this->_canvas, this->_tiles.at(index));
}