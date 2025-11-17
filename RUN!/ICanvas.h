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
//#include <windows.h>
#include <stdlib.h>
#include "cRect.h"

class ICanvas
{
#pragma message("-- ICanvas is included")
public:
	virtual cRect* Size() = 0;

	virtual void Release() = 0;

	virtual ~ICanvas(){};
};