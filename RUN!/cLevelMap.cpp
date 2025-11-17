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
#include "cLevelMap.h"

// STATIC INITIALIZATION

// CONSTRUCTORS
cLevelMap::cLevelMap()
//	: cImage()
{
	this->_Init(NULL);
}
cLevelMap::cLevelMap(STRING levelName, unsigned long width, unsigned long height, cTileSet *tileSet)
//	: cImage(levelName, width * tileSet->TileWidth(), height * tileSet->TileHeight(), new cColor(255,255,255))
{
	this->_Init(tileSet);
	this->_widthInTiles = width;
	this->_heightInTiles = height;
}

// DESTRUCTOR
cLevelMap::~cLevelMap()
{
}

// PUBLIC METHODS
// Set the view port based on the player's position
void cLevelMap::SetWindow(cRect* window)
{
	this->_window = window;
}
void cLevelMap::UpdateWindow()
{
	long top = (long)(this->_player->Position().y - (this->_window->Height() / 2));
	long left = (long)(this->_player->Position().x - (this->_window->Width() / 2));
	this->_window->ShiftTo(left, top);
	if(this->_window->Left < 0)
	{
		this->_window->ShiftTo(0, this->_window->Top);
	}
	if(this->_window->Right > (this->_widthInTiles * this->_tileSet->TileWidth()))
	{
		this->_window->ShiftTo(this->_widthInTiles * this->_tileSet->TileWidth() - (this->_window->Right - this->_window->Left), this->_window->Top);
	}
	if(this->_window->Top < 0)
	{
		this->_window->ShiftTo(this->_window->Left, 0);
	}
	if(this->_window->Bottom > (this->_heightInTiles * this->_tileSet->TileWidth()))
	{
		this->_window->ShiftTo(this->_window->Left, this->_heightInTiles * this->_tileSet->TileWidth() - (this->_window->Bottom - this->_window->Top));
	}
}

void cLevelMap::Render()
{
	if(cGraphicsManager::BeginScene())
	{
		this->DrawTiles();
		this->DrawObjects();
		cGraphicsManager::EndScene();
	}
}
void cLevelMap::DrawTiles()
{
	unsigned long topTile = (unsigned long)(this->_window->Top / this->_tileSet->TileHeight());
	unsigned long leftTile = (unsigned long)(this->_window->Left / this->_tileSet->TileWidth());
	unsigned long rightTile = (unsigned long)(this->_window->Right / this->_tileSet->TileWidth()) + 1;
	unsigned long bottomTile = (unsigned long)(this->_window->Bottom / this->_tileSet->TileHeight()) + 1;
	for(unsigned long y=topTile;y<bottomTile;y++)
	{
		for(unsigned long x=leftTile;x<rightTile;x++)
		{
			cRect *destRect = new cRect(this->_tileSet->TileWidth(), this->_tileSet->TileHeight());
			destRect->ShiftTo((long)((x-leftTile) * this->_tileSet->TileWidth()), (long)((y-topTile) * this->_tileSet->TileHeight()));
			double trimTop = this->_window->Top - (topTile * this->_tileSet->TileHeight());
			double trimLeft = this->_window->Left - (leftTile * this->_tileSet->TileWidth());
			destRect->Shift(-trimLeft, -trimTop);
			unsigned long mapIndex = (y * this->_widthInTiles) + x;
			if(mapIndex < this->_tileMap.size())
			{
				this->_tileSet->DrawTile(destRect, this->_tileMap[mapIndex]);
			}
		}
	}
}

void cLevelMap::UpdateObjects(double interval, double gravity)
{
	this->_scoreTime += interval;
#ifdef _DEBUG
	if(cInputManager::KeyPress(Input::KEY_P))
	{
		this->_player->SetPosition(this->GetPlayerStart());
	}
#endif
	this->UpdateWindow();
	POINT2D playerCenter = this->_player->PositionBox()->Center();
	unsigned long x = (unsigned long)(playerCenter.x / this->_tileSet->TileWidth());
	unsigned long y = (unsigned long)(playerCenter.y / this->_tileSet->TileHeight());
	this->_player->OnLadder(cTileSet::INDEX_LADDER == (this->_tileMap[this->TileIndex(x, y)] & cTileSet::INDEX_LADDER));
	for(unsigned long i=0;i<this->_objects.size();i++)
	{
		IObject *object = this->_objects[i];
		object->Update(interval, gravity);
	}
}

unsigned long cLevelMap::TileIndex(unsigned long x, unsigned long y)
{
	return((y * this->_widthInTiles) + x);
}

void cLevelMap::CheckCollisions()
{
	// check objects vs. tiles
	for each(IObject *object in this->_objects)
	{
		// check objects vs. adjacent tiles
		cRect *tileZone = this->TouchingTiles(object->PositionBox());
		unsigned long top = (unsigned long)tileZone->Top;
		unsigned long left = (unsigned long)tileZone->Left;
		unsigned long right = (unsigned long)tileZone->Right;
		unsigned long bottom = (unsigned long)tileZone->Bottom;

		for(unsigned long y=top;y<=bottom;y++)
		{
			for(unsigned long x=left;x<=right;x++)
			{
				bool isSolid = false;
				unsigned long tileType = cTileSet::INDEX_EMPTY;
				if(x > 0 && x < this->_widthInTiles && y > 0 && y < this->_heightInTiles)
				{
					tileType = this->_tileMap[this->TileIndex(x, y)];
					isSolid = (cTileSet::INDEX_SOLID == (tileType & cTileSet::INDEX_SOLID));
				}
				if(isSolid)
				{
					std::pair<cRect*,cRect*> bCollision;
					cRect* tileBox = this->_TileCollisionBox(x, y);
					std::pair<cRect*,cRect*> oBoxes = object->CollisionBox();
					bCollision.first = oBoxes.first->Intersects(tileBox);
					bCollision.second = oBoxes.second->Intersects(tileBox);
					object->TileCollision(bCollision);
					bool isLethal = (cTileSet::INDEX_SPIKED == (tileType & cTileSet::INDEX_SPIKED));
					if(isLethal)
					{
						if(object == this->_player)
						{
							if(NULL != bCollision.first)
							{
								this->_scoreLives++;
								this->_player->SetPosition(this->GetPlayerStart());
							}
						}
					}
				}
			}
		}

		// check player vs. objects
		if(NULL != object && object != this->_player)
		{
			std::pair<cRect*, cRect*> oBoxes = object->CollisionBox();
			std::pair<cRect*,cRect*> pBoxes = this->_player->CollisionBox();
			std::pair<cRect*,cRect*> bCollision;
			bCollision.first = pBoxes.first->Intersects(oBoxes.first);
			bCollision.second = pBoxes.second->Intersects(oBoxes.second);
			if(object == this->_exit && NULL != bCollision.second)
			{
				// you win!
				this->_levelComplete = true;
			}
			else
			{
				this->_player->ObjectCollision(bCollision, object);
			}
		}
		// check creature vs. objects
		//if(NULL != object && object != this->_creature)
		//{
		//	std::pair<cRect*, cRect*> oBoxes = object->CollisionBox();
		//	std::pair<cRect*,cRect*> cBoxes = this->_creature->CollisionBox();
		//	std::pair<cRect*,cRect*> bCollision;
		//	bCollision.first = cBoxes.first->Intersects(oBoxes.first);
		//	bCollision.second = cBoxes.second->Intersects(oBoxes.second);
		//	this->_creature->ObjectCollision(bCollision, object);
		//}
	}
}

void cLevelMap::DrawObjects()
{
	for(unsigned long i=0;i<this->_objects.size();i++)
	{
		IObject *object = this->_objects[i];
		if(object->PositionBox()->Intersects(this->_window))
		{
			cRect *destRect = object->PositionBox();
			destRect->Shift(-(this->_window->Left), -(this->_window->Top));
			object->Draw(destRect);
		}
	}
}

cRect* cLevelMap::TouchingTiles(cRect *rect)
{
	cRect* ret = new cRect();
	ret->Top = (unsigned long)(rect->Top / this->_tileSet->TileHeight());
	ret->Left = (unsigned long)(rect->Left / this->_tileSet->TileWidth());
	ret->Right = (unsigned long)(rect->Right / this->_tileSet->TileWidth());
	ret->Bottom = (unsigned long)(rect->Bottom / this->_tileSet->TileHeight());
	return(ret);
}

POINT2D cLevelMap::GetPlayerPosition()
{
	POINT2D ps;
	ps.x = this->_player->Position().x;
	ps.y = this->_player->Position().y;
	return(ps);
}
POINT2D cLevelMap::GetPlayerStart()
{
	POINT2D ps;
	ps.x = this->_playerStart.x * this->_tileSet->TileWidth();
	ps.y = (this->_playerStart.y-1) * this->_tileSet->TileHeight();
	return(ps);
}
POINT2D cLevelMap::GetCreatureStart()
{
	POINT2D cs;
	cs.x = this->_creatureStart.x * this->_tileSet->TileWidth();
	cs.y = this->_creatureStart.y * this->_tileSet->TileHeight();
	return(cs);
}

bool cLevelMap::LevelComplete()
{
	return(this->_levelComplete);
}

double cLevelMap::ScoreTime()
{
	return(this->_scoreTime);
}

unsigned long cLevelMap::ScoreLives()
{
	return(this->_scoreLives);
}

unsigned long cLevelMap::ScoreSecrets()
{
	return(this->_scoreSecrets);
}

// PUBLIC STATIC METHODS
cLevelMap* cLevelMap::LoadFromFile(STRING mapFileName, cTileSet *tileSet)
{
	std::vector<STRING> lines = cFileManager::ReadFile(mapFileName);

	// Do whatever with the lines
	unsigned long height = lines.size();
	if(0 == height)
	{
		throw("cLevelMap::LoadFromFile() - Map file has no data.");
	}
	unsigned long width = lines.at(0).length();
	if(width == 0)
	{
		throw("cLevelMap::LoadFromFile() - First line of file was empty.");
	}

	// Initialize Map
	cLevelMap *map = new cLevelMap(mapFileName, width, height, tileSet);
	for(unsigned long y=0;y<map->_heightInTiles;y++)	// for each line
	{
		if(lines.at(y).length() != map->_widthInTiles)
		{
			throw("cLevelMap::LoadFromFile() - Invalid Map.  All lines must be the same length.");
		}
		for(unsigned long x=0;x<map->_widthInTiles;x++)	// for each character
		{
			unsigned long tileIndex = 0;
			TCHAR tile = lines[y][x];
			switch(tile)
			{
				case TEXT('#'):	// solid
					tileIndex = cTileSet::INDEX_SOLID;
					break;
				case TEXT('H'):	// ladder
					tileIndex = cTileSet::INDEX_LADDER;
					break;
				case TEXT('^'):	// lethal
					tileIndex = cTileSet::INDEX_SPIKED;
					break;
				case TEXT('p'): // player start
					tileIndex = cTileSet::INDEX_EMPTY;
					map->_playerStart.x = x;
					map->_playerStart.y = y;
					map->_AddPlayer(x, y);
//					map->_AddSecret(x, y);
					break;
				case TEXT('c'): // creature start
					tileIndex = cTileSet::INDEX_EMPTY;
					map->_creatureStart.x = x;
					map->_creatureStart.y = y;
//					map->_AddCreature(x, y);
					break;
				case TEXT('s'): // secret
					tileIndex = cTileSet::INDEX_EMPTY;
					map->_AddSecret(x, y);
					break;
				case TEXT('x'): // normal exit
					tileIndex = cTileSet::INDEX_EMPTY;
					map->_AddExit(x, y, false);
					break;
				case TEXT('e'): // secret-enabled exit
					tileIndex = cTileSet::INDEX_EMPTY;
					map->_secretExit.x = x;
					map->_secretExit.y = y;
					break;
				case TEXT('B'):
					tileIndex = cTileSet::INDEX_EMPTY;
					map->_AddLargeBox(x, y);
					break;
				case TEXT('b'):
					tileIndex = cTileSet::INDEX_EMPTY;
					map->_AddMediumBox(x, y);
					break;
				case TEXT('1'):
					tileIndex = cTileSet::INDEX_EMPTY;
					map->_AddSmallBoxes(x, y, cSmallBox::ONE_LEFT);
					break;
				case TEXT('2'):
					tileIndex = cTileSet::INDEX_EMPTY;
					map->_AddSmallBoxes(x, y, cSmallBox::ONE_RIGHT);
					break;
				case TEXT('3'):
					tileIndex = cTileSet::INDEX_EMPTY;
					map->_AddSmallBoxes(x, y, cSmallBox::ONE_LEFT_ONE_RIGHT);
					break;
				case TEXT('4'):
					tileIndex = cTileSet::INDEX_EMPTY;
					map->_AddSmallBoxes(x, y, cSmallBox::TWO_LEFT);
					break;
				case TEXT('5'):
					tileIndex = cTileSet::INDEX_EMPTY;
					map->_AddSmallBoxes(x, y, cSmallBox::TWO_RIGHT);
					break;
				case TEXT('6'):
					tileIndex = cTileSet::INDEX_EMPTY;
					map->_AddSmallBoxes(x, y, cSmallBox::TWO_LEFT_ONE_RIGHT);
					break;
				case TEXT('7'):
					tileIndex = cTileSet::INDEX_EMPTY;
					map->_AddSmallBoxes(x, y, cSmallBox::ONE_LEFT_TWO_RIGHT);
					break;
				case TEXT('8'):
					tileIndex = cTileSet::INDEX_EMPTY;
					map->_AddSmallBoxes(x, y, cSmallBox::TWO_LEFT_TWO_RIGHT);
					break;
				case TEXT(' '):	// empty
				default:
					tileIndex = cTileSet::INDEX_EMPTY;
					break;
			}
			map->_tileMap.push_back(tileIndex);
		}
	}
	if(map->_tileMap.size() != (map->_widthInTiles * map->_heightInTiles))
	{
		throw("cLevelMap::LoadFromTile() - Wrong number of tiles.");
	}
	map->_ProcessTiles();
//	map->_DrawStatic(tileSet);
	return(map);
}

// PRIVATE METHODS
void cLevelMap::_DrawStatic(cTileSet *tileSet)
{
//	for(unsigned long y=0;y<this->_height;y++)
//	{
//		for(unsigned long x=0;x<this->_width;x++)
//		{
//			cRect *destRect = new cRect(0,(unsigned long)0,tileSet->TileWidth(), tileSet->TileHeight());
//			destRect->ShiftTo((double)(x * tileSet->TileWidth()), (double)(y * tileSet->TileHeight()));
//			unsigned long mapIndex = (y*this->_width) + x;
//			this->_tileSet->DrawTile(this->_canvas, destRect, mapIndex);
//		}
//	}
}

void cLevelMap::_ProcessTiles()
{
	// this method will eventually massage the 'solid' tiles into
	// the versions with the proper border based on surrounding tiles
}


void cLevelMap::_AddPlayer(unsigned long x, unsigned long y)
{
	this->_player = new cAvatar(x * this->_tileSet->TileWidth(), (y-1) * this->_tileSet->TileHeight());
	this->_objects.push_back(this->_player);
}
void cLevelMap::_AddSecret(unsigned long x, unsigned long y)
{
	this->_objects.push_back(new cSecret(x * this->_tileSet->TileWidth(), (y-1) * this->_tileSet->TileHeight()));
}
void cLevelMap::_AddDoor(unsigned long x, unsigned long y, bool locked)
{
	this->_objects.push_back(new cDoor(x * this->_tileSet->TileWidth(), (y-2) * this->_tileSet->TileHeight(), locked));
}
void cLevelMap::_AddExit(unsigned long x, unsigned long y, bool locked)
{
	this->_exit = new cDoor(x * this->_tileSet->TileWidth(), (y-2) * this->_tileSet->TileHeight(), locked);
	this->_objects.push_back(this->_exit);
}
void cLevelMap::_AddSmallBoxes(unsigned long x, unsigned long y, cSmallBox::Layout layout)
{
	double topOfTopRow = y * this->_tileSet->TileHeight();
	double topOfBottomRow = (0.5 + y) * this->_tileSet->TileHeight();
	double leftOfLeftCol = x * this->_tileSet->TileWidth();
	double leftOfRightCol = (0.5 + x) * this->_tileSet->TileWidth();
	switch(layout)
	{
		case cSmallBox::ONE_LEFT:
			this->_objects.push_back(new cSmallBox(leftOfLeftCol, topOfBottomRow)); 
			break;
		case cSmallBox::ONE_RIGHT:
			this->_objects.push_back(new cSmallBox(leftOfRightCol, topOfBottomRow)); 
			break;
		case cSmallBox::ONE_LEFT_ONE_RIGHT:
			this->_objects.push_back(new cSmallBox(leftOfLeftCol, topOfBottomRow)); 
			this->_objects.push_back(new cSmallBox(leftOfRightCol, topOfBottomRow)); 
			break;
		case cSmallBox::TWO_LEFT:
			this->_objects.push_back(new cSmallBox(leftOfLeftCol, topOfBottomRow)); 
			this->_objects.push_back(new cSmallBox(leftOfLeftCol, topOfTopRow));
			break;
		case cSmallBox::TWO_RIGHT:
			this->_objects.push_back(new cSmallBox(leftOfRightCol, topOfBottomRow)); 
			this->_objects.push_back(new cSmallBox(leftOfRightCol, topOfTopRow));
			break;
		case cSmallBox::TWO_LEFT_ONE_RIGHT:
			this->_objects.push_back(new cSmallBox(leftOfLeftCol, topOfBottomRow)); 
			this->_objects.push_back(new cSmallBox(leftOfLeftCol, topOfTopRow));
			this->_objects.push_back(new cSmallBox(leftOfRightCol, topOfBottomRow)); 
			break;
		case cSmallBox::ONE_LEFT_TWO_RIGHT:
			this->_objects.push_back(new cSmallBox(leftOfLeftCol, topOfBottomRow)); 
			this->_objects.push_back(new cSmallBox(leftOfRightCol, topOfBottomRow)); 
			this->_objects.push_back(new cSmallBox(leftOfRightCol, topOfTopRow));
			break;
		case cSmallBox::TWO_LEFT_TWO_RIGHT:
			this->_objects.push_back(new cSmallBox(leftOfLeftCol, topOfBottomRow)); 
			this->_objects.push_back(new cSmallBox(leftOfLeftCol, topOfTopRow));
			this->_objects.push_back(new cSmallBox(leftOfRightCol, topOfBottomRow)); 
			this->_objects.push_back(new cSmallBox(leftOfRightCol, topOfTopRow));
			break;
		default:
			break;
	}
}
void cLevelMap::_AddMediumBox(unsigned long x, unsigned long y)
{
	this->_objects.push_back(new cMediumBox(x * this->_tileSet->TileWidth(), y * this->_tileSet->TileHeight()));
}
void cLevelMap::_AddLargeBox(unsigned long x, unsigned long y)
{
	this->_objects.push_back(new cLargeBox(x * this->_tileSet->TileWidth(), (y-1) * this->_tileSet->TileHeight()));
}

cRect* cLevelMap::_TileCollisionBox(unsigned long x, unsigned long y)
{
	unsigned long top = y * this->_tileSet->TileHeight();
	unsigned long left = x * this->_tileSet->TileWidth();
	return(new cRect(top, left, left + this->_tileSet->TileWidth(), top + this->_tileSet->TileHeight()));
}

void cLevelMap::_Init(cTileSet *tileSet)
{
	this->_tileSet = tileSet;
	this->_levelComplete = false;
	this->_scoreTime = 0.0;
	this->_scoreLives = 0;
	this->_scoreSecrets = 0;
}

//Empty Space = [space]
//Solid Space = #
//Spikes = ^
//Ladder = H
//Player Start = p
//Creature Start = c
//Exit = x
//Secret = s
//Secret Exit = e
//Office Door (locked) = o
//Bottomless Pit = [empty space on bottom row of map]