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
#include "cScrollingText.h"

// STATIC INITIALIZATION

// CONSTRUCTORS
cScrollingText::cScrollingText(unsigned long width, unsigned long height, double speed)
{
	this->_screenWidth = width;
	this->_screenHeight = height;
	this->_speed = speed;
	this->_lines.clear();
	this->_fontSheet = new cFontSheet();
}

// DESTRUCTOR
cScrollingText::~cScrollingText(void)
{
	this->_lines.clear();
}

// PUBLIC METHODS
void cScrollingText::LoadText(STRING filePath)
{
	this->_lines.clear();
	this->_lines = cFileManager::ReadFile(filePath);
}

void cScrollingText::LoadText(std::vector<STRING> text)
{
	this->_lines.clear();
	for each(STRING line in text)
	{
		this->_lines.push_back(line);
	}
}

void cScrollingText::Show()
{
	double interval = (1.0 / 30.0);
	double offset = this->_screenHeight;
	while(!cInputManager::KeyPress(Input::KEY_ESCAPE))
	{
		double maxBottom = 0.0;
		if(cGraphicsManager::BeginScene())
		{
			offset -= (this->_speed * interval);
			for(unsigned long i=0;i<this->_lines.size();i++)
			{
				STRING line = this->_lines[i];
				if(TEXT("") != line.c_str())
				{
					POINT2D textSize = this->_fontSheet->GetSize(line);
					long left = (unsigned long)((this->_screenWidth - textSize.x) / 2);
					long top = (unsigned long)((i * textSize.y) + offset);

					cRect *destRect = new cRect(top, left, left + (unsigned long)textSize.x, top + (unsigned long)textSize.y);
					if(maxBottom < destRect->Bottom)
					{
						maxBottom = destRect->Bottom;
					}
					if(destRect->Bottom > 0 && destRect->Top <= this->_screenHeight)
					{
						this->_fontSheet->Draw(destRect, line);
					}
				}
			}
			cGraphicsManager::EndScene();
		}
		if(maxBottom > 0)
		{
			Sleep((unsigned long)(interval * 1000));
			cInputManager::PollInputs();
		}
		else
		{
			break;
		}
	}
}