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
#include "cGame.h"

// STATIC INITIALIZATIONS
STRING cGame::TILE_SET_PATH = TEXT("./Images/BasicTileSet.png");
unsigned long cGame::TILE_WIDTH = 64;
unsigned long cGame::TILE_HEIGHT = 64;
STRING cGame::MAP_FILE_PATH = TEXT("./Levels/Test.lvl");
double cGame::_gravity = (9.8 * cGame::TILE_HEIGHT);	// 1 tile = 1m, 9.8m = 627.2px

// CONSTRUCTORS
cGame::cGame()
{
	this->_width = cWindowManager::width();
	this->_height = cWindowManager::height();
	this->_fullscreen = cWindowManager::isFullscreen();
	cInputManager::Initialize();
	cGraphicsManager::Initialize();
	cAudioManager::Initialize();

	// initialize level
	this->_tileSet = new cTileSet(cGame::TILE_SET_PATH, cGame::TILE_WIDTH, cGame::TILE_HEIGHT);
	this->_level = cLevelMap::LoadFromFile(cGame::MAP_FILE_PATH, this->_tileSet);
	this->_level->SetWindow(new cRect(this->_width, this->_height));
	this->_gameState = cGame::SHOW_SPLASH;
	this->_menu = NULL;
	this->_score = NULL;
	this->_credits = NULL;
	this->_nag = NULL;
}

// DESTRUCTOR
cGame::~cGame()
{
	cGraphicsManager::Release();
	cInputManager::Release();
}

// PUBLIC METHODS
void cGame::Run(double interval)
{
	cInputManager::PollInputs();
	switch(this->_gameState)
	{
		case cGame::SHOW_SPLASH:
			this->_gameState = cGame::SHOW_MENU;
			break;
		case cGame::SHOW_GAME:
			this->_level->UpdateObjects(interval, cGame::Gravity(interval));
			this->_level->CheckCollisions();
			this->_level->Render();
			if(this->_level->LevelComplete())
			{
				this->_gameState = cGame::SHOW_SCORE;
			}
			else if(cInputManager::KeyPress(Input::KEY_ESCAPE))
			{
				this->_gameState = cGame::SHOW_MENU;
			}
			break;
		case cGame::SHOW_SCORE:
			this->_score = new cScoreScreen(this->_width, this->_height, 64);
			// add score info
			this->_score->SetScore(this->_level->ScoreTime(), this->_level->ScoreLives(), this->_level->ScoreSecrets());
			this->_score->Show();
			delete(this->_score);
			this->_gameState = cGame::SHOW_MENU;
			break;
		case cGame::SHOW_MENU:
			this->_menu = new cMenu(this->_width, this->_height, TEXT("RUN!"));
			this->_menu->Show();
			if(0 == this->_menu->Selection().compare(cMenu::ESCAPE))
			{
				this->_gameState = cGame::SHOW_GAME;
			}
			if(0 == this->_menu->Selection().compare(cMenu::PLAY))
			{
				this->_gameState = cGame::SHOW_GAME;
			}
			if(0 == this->_menu->Selection().compare(cMenu::CREDITS))
			{
				this->_gameState = cGame::SHOW_CREDITS;
			}
			if(0 == this->_menu->Selection().compare(cMenu::EXIT))
			{
				this->_gameState = cGame::SHOW_NAG;
			}
			delete(this->_menu);
			this->_menu = NULL;
			break;
		case cGame::SHOW_CREDITS:
			this->_credits = new cCredits(this->_width, this->_height, 64);
			this->_credits->Show();
			delete(this->_credits);
			this->_gameState = cGame::SHOW_MENU;
			break;
		case cGame::SHOW_NAG:
			this->_nag = new cNagScreen(this->_width, this->_height, 64);
			this->_nag->Show();
			delete(this->_nag);
			this->_nag = NULL;
			this->_gameState = cGame::EXIT_GAME;
			break;
	}
}

void cGame::End()
{
	delete(this->_level);
	this->_level = NULL;
	cGraphicsManager::Release();
	cAudioManager::Release();
	cInputManager::Release();
}

bool cGame::IsGameOver()
{
	return(cGame::EXIT_GAME == this->_gameState);
}

double cGame::Gravity(double interval)
{
	return(cGame::_gravity * interval * interval * 4.0);
}