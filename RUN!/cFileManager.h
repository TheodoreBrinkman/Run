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
#include <vector>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <TCHAR.h>
#include "TYPEDEFS.h"

class cFileManager
{
public:
	static unsigned long cFileManager::MAX_LINE_WIDTH;
	static std::vector<STRING> ReadFile(STRING fileName);
//	static void Initialize(unsigned long maxLineWidth);

private:
};
