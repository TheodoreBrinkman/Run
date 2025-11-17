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
#include <map>
#include "cImage.h"
#include "cTileSet.h"
#include "cSprite.h"
#include "IObject.h"
#include "cSmallBox.h"
#include "cMediumBox.h"
#include "cLargeBox.h"
#include "cSecret.h"
#include "cAvatar.h"
#include "cFileManager.h"
#include "cDoor.h"

class cLevelMap
//	: public cImage
{
public:
	cLevelMap(STRING levelName, unsigned long width, unsigned long height, cTileSet *tileSet);
	~cLevelMap();

	void SetWindow(cRect *window);
	void UpdateWindow();
	void UpdateObjects(double interval, double gravity);
	unsigned long TileIndex(unsigned long x, unsigned long y);
	void CheckCollisions();
	void Render();
	void DrawTiles();
	void DrawObjects();
	bool LevelComplete();
	cRect* TouchingTiles(cRect *rect);
	POINT2D GetPlayerPosition();
	POINT2D GetPlayerStart();
	POINT2D GetCreatureStart();
	double ScoreTime();
	unsigned long ScoreLives();
	unsigned long ScoreSecrets();

	static cLevelMap* LoadFromFile(STRING levelFileName, cTileSet *tileSet);

private:
	unsigned long _widthInTiles;
	unsigned long _heightInTiles;
	std::vector<unsigned long> _tileMap;
	std::vector<IObject*> _objects;
	cAvatar *_player;
	cTileSet *_tileSet;
	POINT2D _playerStart;
	POINT2D _creatureStart;
	cDoor* _exit;
	cSecret* _secret;
	POINT2D _secretExit;
	cRect *_window;
	double _scoreTime;
	unsigned long _scoreLives;
	unsigned long _scoreSecrets;
	bool _levelComplete;

	cLevelMap();
	void _AddDoor(unsigned long x, unsigned long y, bool locked);
	void _AddExit(unsigned long x, unsigned long y, bool locked);
	void _AddPlayer(unsigned long x, unsigned long y);
	void _AddSecret(unsigned long x, unsigned long y);
	void _AddSmallBoxes(unsigned long x, unsigned long y, cSmallBox::Layout layout);
	void _AddMediumBox(unsigned long x, unsigned long y);
	void _AddLargeBox(unsigned long x, unsigned long y);
	void _ProcessTiles();
	void _DrawStatic(cTileSet *tileSet);
	cRect* _TileCollisionBox(unsigned long x, unsigned long y);

	void _Init(cTileSet *tileSet);

	static const unsigned long cLevelMap::MAX_LEVEL_WIDTH = 4096;
};