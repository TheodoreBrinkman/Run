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
#include "IWindowManager.h"
#include "cWindowManager.h"
#include "IAudioManager.h"
#include "cAudioManagerDX.h"

class cAudioManager
{
#pragma message("-- cAudioManager is included")
public:
	static void Initialize();

	static void RegisterSound(STRING audioFilePath);
	static void ReleaseSound(STRING audioFilePath);

	static void Play(STRING audioFilePath);
	static void Loop(STRING audioFilePath);
	static void Stop(STRING audioFilePath);

	static void Release();

private:
	static IAudioManager * cAudioManager::_manager;
};