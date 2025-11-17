/******************************************************************************\
*                                                                              *
*	Copyright © 2010 Theo Brinkman. All rights reserved.                       *
*                                                                              *
*	This work is licensed under a Creative Commons                             *
*	Attribution-Noncommercial-No Derivative Works 3.0 United States License.   *
*                                                                              *
*	See COPYING.TXT for details.                                               *
*                                                                              *
\******************************************************************************/
#pragma once
#include "Enums.h"
#include "TYPEDEFS.h"

class IWindowManager
{
#pragma message("-- IWindowManager is included")
public:
	// Public Properties
	virtual STRING title() = 0;
	virtual unsigned long width() = 0;
	virtual unsigned long height() = 0;
	virtual bool isFullscreen() = 0;
	virtual WindowManager::eWindowType windowType() = 0;
	virtual GraphicsManager::eRenderingMethod renderingMethod() = 0;
	virtual InputManager::eInputMethod inputMethod() = 0;
	virtual AudioManager::eAudioMethod audioMethod() = 0;

	// Public Methods
	virtual void Release() = 0;

	virtual ~IWindowManager(){};
};