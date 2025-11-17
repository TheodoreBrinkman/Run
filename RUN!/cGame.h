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
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "cWindowManager.h"
#include "cInputManager.h"
#include "STRUCTURES.h"
#include "cTileSet.h"
#include "cLevelMap.h"
#include "cAudioManager.h"
#include "cMenu.h"
#include "cCredits.h"
#include "cNagScreen.h"
#include "cScoreScreen.h"
#include "cGraphicsManagerSDL.h"

class cGame
{
#pragma message("-- cGame is included")
public:
	// Constructors
	cGame();

	// Destructor
	~cGame();

	// Public Methods
	void Run(double interval);
	void End();
	bool IsGameOver();

private:
	// Private Members
	IWindowManager *_windowManager;

	unsigned long _width;
	unsigned long _height;
	bool _fullscreen;

	static double Gravity(double interval);
	static double _gravity;
	cTileSet *_tileSet;
	cLevelMap *_level;
	typedef enum GAME_STATE : unsigned short
	{
		SHOW_SPLASH,
		SHOW_MENU,
		SHOW_GAME,
		SHOW_SCORE,
		SHOW_CREDITS,
		SHOW_NAG,
		EXIT_GAME
	};
	cGame::GAME_STATE _gameState;
	cMenu *_menu;
	cScoreScreen *_score;
	cCredits *_credits;
	cNagScreen *_nag;

	void _CheckCollisions();
	void _Draw(cTileSet *tileSet);

	static STRING TILE_SET_PATH;
	static unsigned long TILE_WIDTH;
	static unsigned long TILE_HEIGHT;
	static STRING MAP_FILE_PATH;
};