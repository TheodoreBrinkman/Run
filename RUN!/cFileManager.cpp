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
#include "cFileManager.h"

// STATIC INITIALIZATION
unsigned long cFileManager::MAX_LINE_WIDTH = 4096;

//void Initialize(unsigned long maxLineWidth)
//{
//	cFileManager::MAX_LINE_WIDTH = maxLineWidth;
//}

std::vector<STRING> cFileManager::ReadFile(STRING fileName)
{
	std::vector<STRING> lines;
	// Load file into stream
	IFSTREAM infile(fileName.c_str());
	if(infile.is_open())
	{
		while (!infile.eof())
		{
			TCHAR *line = new TCHAR[cFileManager::MAX_LINE_WIDTH+1]();
			infile.getline(line, cFileManager::MAX_LINE_WIDTH);
			lines.push_back(STRING(line));
		}
		infile.close();
	}
	else
	{
		throw("cFileManager::ReadFile() - Could not open file.");
	}

	return(lines);
}