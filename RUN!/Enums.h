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
#pragma message("-- Enums is included")

namespace WindowManager
{
	enum eWindowType : unsigned short
	{
		DirectX = 0,
		OpenGL = 1,
		CoreAnimation = 2,
		SDL = 3,
		Raw = 255
	};
}

namespace GraphicsManager
{
	enum eRenderingMethod : unsigned short
	{
		Direct3D = 0,		// Windows
		OpenGL = 1,			// OpenGL
		CoreAnimation = 2,	// Mac OS X
		SDL = 3,			// Simple Direct-Media Layer
		Raw = 255
	};
}

namespace InputManager
{
	enum eInputMethod : unsigned short
	{
		DirectInput = 0,		// Windows
		OpenGL = 1,			// OpenGL
		CoreInput = 2,		// Mac OS X
		SDL = 3,				// Simple Direct-Media Layer
		Raw = 255			// Raw
	};
}

namespace AudioManager
{
	enum eAudioMethod : unsigned short
	{
		DirectSound = 0,		// Windows
		OpenGL = 1,			// OpenGL
		CoreAudio = 2,		// Mac OS X
		SDL = 3,				// Simple Direct-Media Layer
		Raw = 255			// Raw
	};
}