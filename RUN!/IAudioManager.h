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
#include <string>
#include "TYPEDEFS.h"
#include "Enums.h"

class IAudioManager
{
#pragma message("-- IAudioManager is included")
public:
	virtual void RegisterSound(STRING audioFilePath) = 0;
	virtual void ReleaseSound(STRING audioFilePath) = 0;

	virtual void Play(STRING audioFilePath) = 0;
	virtual void Loop(STRING audioFilePath) = 0;
	virtual void Stop(STRING audioFilePath) = 0;

	virtual void Release() = 0;

	virtual ~IAudioManager() {};
};
