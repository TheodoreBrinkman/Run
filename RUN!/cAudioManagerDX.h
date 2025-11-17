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
#include <stdlib.h>
#include <map>
#include <dsound.h>
#include "TYPEDEFS.h"
#include "IWindowManager.h"
#include "cWindowManager.h"
#include "IAudioManager.h"
#include "dsutil.h"

class cAudioManagerDX :
	public IAudioManager
{
public:
	cAudioManagerDX(IWindowManager *window, unsigned long dwCoopLevel);
	virtual ~cAudioManagerDX();

	virtual void RegisterSound(STRING audioFilePath);
	virtual void ReleaseSound(STRING audioFilePath);

	virtual void Play(STRING audioFilePath);
	virtual void Loop(STRING audioFilePath);
	virtual void Stop(STRING audioFilePath);

	virtual void Release();

private:
	HWND _hWnd;
	cSoundManagerDX *_soundManager;
	std::map<STRING, cSoundDX*> _sounds;
	std::map<STRING, unsigned long> _references;

	bool _Exists(STRING audioFilePath);
	void _Initialize(cWindowManagerDX *window, unsigned long dwCoopLevel);
};