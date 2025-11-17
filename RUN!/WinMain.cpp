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
#include "cWindowManager.h"
#include "cGame.h"
#include "cTimer.h"

// App Name
#define APP_TITLE TEXT("RUN!")

// screen resolution
#ifdef _DEBUG
#define FULLSCREEN false
#else
#define FULLSCREEN true
#endif

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

//#define WINDOW_TYPE WindowManager::DirectX
#define WINDOW_TYPE WindowManager::SDL

#define SPF (1.0f / 60.0f)

// entry point for a Windows program
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// declare variables
	MSG msg;
	bool done = false;
	double frameStart = 0.0;
	double frameEnd = 0.0;
	double interval = 0.0;

	switch(WINDOW_TYPE)
	{
		case WindowManager::DirectX:
			cWindowManager::CreateWindowDX(APP_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT, FULLSCREEN, hInstance, nCmdShow);
			break;
		case WindowManager::SDL:
			cWindowManager::CreateWindowSDL(APP_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT, FULLSCREEN);
			break;
		case WindowManager::OpenGL:
			break;
		case WindowManager::CoreAnimation:
			break;
		case WindowManager::Raw:
			break;
	}

	if(cWindowManager::IsInitialized())
	{
		// Initialize the game
		cTimer *timer = new cTimer();
//		timer->Wait(120.0);
		cGame *game = new cGame();
		if(NULL == game)
		{
			return(0);
		}
		frameStart = timer->GetTime();

		// main message loop
		while(!done)
		{
			if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				// look for quit message
				switch(msg.message)
				{
					case WM_QUIT:
						done = true;
						break;
				}

				// decode and pass messages on to WndProc
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			// process game loop (else prevents running after window is closed)
			frameEnd = timer->GetTime();
			interval = frameEnd - frameStart;
			frameStart = frameEnd;
			try
			{
	//			game->Run(interval);
				game->Run(SPF);
				if(game->IsGameOver())
				{
					done = true;
					cWindowManager::Release();
				}
			}
			catch(STRING ex)
			{
				STRING result = (STRING)ex;
				done = true;
			}
			if(interval < SPF)
			{
				timer->Wait(SPF - interval);
			}
		}
		game->End();
		return(msg.wParam);
	}
	else
	{
		return(-31337);
	}
}