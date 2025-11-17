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
#include <vector>
#include "TYPEDEFS.h"
#include "cImage.h"
#include "cGraphicsManager.h"

class cTileSet :
	public cImage
{
public:
	enum eTILE_TYPE : unsigned long
	{
		TILE_EMPTY = 0,		// open space
		TILE_SOLID = 1,		// solid surface
		TILE_LETHAL = 2,	// spikes, bottomless pit, etc
		TILE_CLIMB = 4,		// ladder, etc
	};

	enum eTILE_INDEX : unsigned long
	{
		INDEX_EMPTY = 0,
		INDEX_SOLID = 1,
		INDEX_CEILING = 0,
		INDEX_FLOOR = 0,
		INDEX_PLATFORM = 0,
		INDEX_PLATFORM_LEFT_END = 0,
		INDEX_PLATFORM_RIGHT_END = 0,
		INDEX_PLATFORM_SECTION = 0,
		INDEX_WALL_BOTTOM = 0,
		INDEX_WALL_LEFT = 0,
		INDEX_WALL_LEFT_TO_CEILING_BELOW = 0,
		INDEX_WALL_LEFT_TO_CEILING_ABOVE = 0,
		INDEX_WALL_LEFT_TO_FLOOR_ABOVE = 0,
		INDEX_WALL_LEFT_TO_FLOOR_BELOW = 0,
		INDEX_WALL_RIGHT = 0,
		INDEX_WALL_RIGHT_TO_CEILING_ABOVE = 0,
		INDEX_WALL_RIGHT_TO_CEILING_BELOW = 0,
		INDEX_WALL_RIGHT_TO_FLOOR_ABOVE = 0,
		INDEX_WALL_RIGHT_TO_FLOOR_BELOW = 0,
		INDEX_WALL_SECTION = 0,
		INDEX_WALL_TOP = 0,
		INDEX_LADDER = 2,
		INDEX_SPIKED = 3,
		INDEX_SPIKED_CEILING = 3,
		INDEX_SPIKED_FLOOR = 3,
		INDEX_UNKNOWN = 1
	};
	// Constructors
	cTileSet(STRING imageFilePath, unsigned long tileWidth, unsigned long tileHeight);
	// Destructor
	~cTileSet();

	// Methods
	unsigned long TileWidth();
	unsigned long TileHeight();
	void DrawTile(cRect *destRect, unsigned long index);

private:
	unsigned long _tileWidth;
	unsigned long _tileHeight;
	std::vector<cRect*> _tiles;	
};