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
#include "cFontSheet.h"

// STATIC INITIALIZATION
STRING cFontSheet::IMAGE_FILE_PATH = TEXT("./Images/font.png");

// CONSTRUCTORS
cFontSheet::cFontSheet() : cImage(cFontSheet::IMAGE_FILE_PATH)
{
	int rowUpper = 0;
	int rowLower = 56;
	int rowSymbols = 111;
	int fontHeight = 54;
	// upper case
	this->_sprites[TEXT('A')] = new cRect(rowUpper, 0, 30, rowUpper+fontHeight);
	this->_sprites[TEXT('B')] = new cRect(rowUpper, 31, 56, rowUpper+fontHeight);
	this->_sprites[TEXT('C')] = new cRect(rowUpper, 57, 82, rowUpper+fontHeight);
	this->_sprites[TEXT('D')] = new cRect(rowUpper, 83, 113, rowUpper+fontHeight);
	this->_sprites[TEXT('E')] = new cRect(rowUpper, 114, 136, rowUpper+fontHeight);
	this->_sprites[TEXT('F')] = new cRect(rowUpper, 137, 159, rowUpper+fontHeight);
	this->_sprites[TEXT('G')] = new cRect(rowUpper, 160, 190, rowUpper+fontHeight);
	this->_sprites[TEXT('H')] = new cRect(rowUpper, 191, 218, rowUpper+fontHeight);
	this->_sprites[TEXT('I')] = new cRect(rowUpper, 219, 235, rowUpper+fontHeight);
	this->_sprites[TEXT('J')] = new cRect(rowUpper, 236, 261, rowUpper+fontHeight);
	this->_sprites[TEXT('K')] = new cRect(rowUpper, 262, 289, rowUpper+fontHeight);
	this->_sprites[TEXT('L')] = new cRect(rowUpper, 290, 311, rowUpper+fontHeight);
	this->_sprites[TEXT('M')] = new cRect(rowUpper, 312, 349, rowUpper+fontHeight);
	this->_sprites[TEXT('N')] = new cRect(rowUpper, 350, 379, rowUpper+fontHeight);
	this->_sprites[TEXT('O')] = new cRect(rowUpper, 380, 411, rowUpper+fontHeight);
	this->_sprites[TEXT('P')] = new cRect(rowUpper, 412, 438, rowUpper+fontHeight);
	this->_sprites[TEXT('Q')] = new cRect(rowUpper, 439, 471, rowUpper+fontHeight);
	this->_sprites[TEXT('R')] = new cRect(rowUpper, 472, 501, rowUpper+fontHeight);
	this->_sprites[TEXT('S')] = new cRect(rowUpper, 502, 524, rowUpper+fontHeight);
	this->_sprites[TEXT('T')] = new cRect(rowUpper, 525, 553, rowUpper+fontHeight);
	this->_sprites[TEXT('U')] = new cRect(rowUpper, 554, 581, rowUpper+fontHeight);
	this->_sprites[TEXT('V')] = new cRect(rowUpper, 582, 608, rowUpper+fontHeight);
	this->_sprites[TEXT('W')] = new cRect(rowUpper, 609, 656, rowUpper+fontHeight);
	this->_sprites[TEXT('X')] = new cRect(rowUpper, 657, 683, rowUpper+fontHeight);
	this->_sprites[TEXT('Y')] = new cRect(rowUpper, 684, 713, rowUpper+fontHeight);
	this->_sprites[TEXT('Z')] = new cRect(rowUpper, 714, 742, rowUpper+fontHeight);
	// lower case
	this->_sprites[TEXT('a')] = new cRect(rowLower, 2, 27, rowLower+fontHeight);
	this->_sprites[TEXT('b')] = new cRect(rowLower, 28, 50, rowLower+fontHeight);
	this->_sprites[TEXT('c')] = new cRect(rowLower, 51, 72, rowLower+fontHeight);
	this->_sprites[TEXT('d')] = new cRect(rowLower, 71, 95, rowLower+fontHeight);
	this->_sprites[TEXT('e')] = new cRect(rowLower, 96, 119, rowLower+fontHeight);
	this->_sprites[TEXT('f')] = new cRect(rowLower, 120, 137, rowLower+fontHeight);
	this->_sprites[TEXT('g')] = new cRect(rowLower, 138, 163, rowLower+fontHeight);
	this->_sprites[TEXT('h')] = new cRect(rowLower, 164, 188, rowLower+fontHeight);
	this->_sprites[TEXT('i')] = new cRect(rowLower, 189, 197, rowLower+fontHeight);
	this->_sprites[TEXT('j')] = new cRect(rowLower, 196, 215, rowLower+fontHeight);
	this->_sprites[TEXT('k')] = new cRect(rowLower, 216, 238, rowLower+fontHeight);
	this->_sprites[TEXT('l')] = new cRect(rowLower, 238, 249, rowLower+fontHeight);
	this->_sprites[TEXT('m')] = new cRect(rowLower, 251, 283, rowLower+fontHeight);
	this->_sprites[TEXT('n')] = new cRect(rowLower, 284, 306, rowLower+fontHeight);
	this->_sprites[TEXT('o')] = new cRect(rowLower, 307, 332, rowLower+fontHeight);
	this->_sprites[TEXT('p')] = new cRect(rowLower, 333, 354, rowLower+fontHeight);
	this->_sprites[TEXT('q')] = new cRect(rowLower, 355, 378, rowLower+fontHeight);
	this->_sprites[TEXT('r')] = new cRect(rowLower, 379, 398, rowLower+fontHeight);
	this->_sprites[TEXT('s')] = new cRect(rowLower, 399, 416, rowLower+fontHeight);
	this->_sprites[TEXT('t')] = new cRect(rowLower, 417, 436, rowLower+fontHeight);
	this->_sprites[TEXT('u')] = new cRect(rowLower, 437, 458, rowLower+fontHeight);
	this->_sprites[TEXT('v')] = new cRect(rowLower, 459, 480, rowLower+fontHeight);
	this->_sprites[TEXT('w')] = new cRect(rowLower, 481, 513, rowLower+fontHeight);
	this->_sprites[TEXT('x')] = new cRect(rowLower, 514, 537, rowLower+fontHeight);
	this->_sprites[TEXT('y')] = new cRect(rowLower, 538, 561, rowLower+fontHeight);
	this->_sprites[TEXT('z')] = new cRect(rowLower, 562, 585, rowLower+fontHeight);
	// numbers
	this->_sprites[TEXT('1')] = new cRect(rowSymbols, 0, 20, rowSymbols+fontHeight);
	this->_sprites[TEXT('2')] = new cRect(rowSymbols, 20, 43, rowSymbols+fontHeight);
	this->_sprites[TEXT('3')] = new cRect(rowSymbols, 44, 68, rowSymbols+fontHeight);
	this->_sprites[TEXT('4')] = new cRect(rowSymbols, 68, 92, rowSymbols+fontHeight);
	this->_sprites[TEXT('5')] = new cRect(rowSymbols, 92, 115, rowSymbols+fontHeight);
	this->_sprites[TEXT('6')] = new cRect(rowSymbols, 116, 137, rowSymbols+fontHeight);
	this->_sprites[TEXT('7')] = new cRect(rowSymbols, 138, 162, rowSymbols+fontHeight);
	this->_sprites[TEXT('8')] = new cRect(rowSymbols, 163, 186, rowSymbols+fontHeight);
	this->_sprites[TEXT('9')] = new cRect(rowSymbols, 187, 211, rowSymbols+fontHeight);
	this->_sprites[TEXT('0')] = new cRect(rowSymbols, 212, 239, rowSymbols+fontHeight);
	// symbols
	this->_sprites[TEXT(' ')] = new cRect(rowSymbols, 240, 257, rowSymbols+fontHeight);
	this->_sprites[TEXT('.')] = new cRect(rowSymbols, 258, 266, rowSymbols+fontHeight);
	this->_sprites[TEXT('?')] = new cRect(rowSymbols, 267, 290, rowSymbols+fontHeight);
	this->_sprites[TEXT('!')] = new cRect(rowSymbols, 291, 300, rowSymbols+fontHeight);
	this->_sprites[TEXT('\"')] = new cRect(rowSymbols, 301, 320, rowSymbols+fontHeight);
	this->_sprites[TEXT('\'')] = new cRect(rowSymbols, 321, 329, rowSymbols+fontHeight);
	this->_sprites[TEXT('+')] = new cRect(rowSymbols, 330, 354, rowSymbols+fontHeight);
	this->_sprites[TEXT('-')] = new cRect(rowSymbols, 355, 374, rowSymbols+fontHeight);
	this->_sprites[TEXT('*')] = new cRect(rowSymbols, 375, 393, rowSymbols+fontHeight);
	this->_sprites[TEXT('/')] = new cRect(rowSymbols, 394, 415, rowSymbols+fontHeight);
	this->_sprites[TEXT('\t')] = new cRect(rowSymbols, 420, 460, rowSymbols+fontHeight);
	this->_sprites[TEXT('&')] = this->_sprites[TEXT('+')];
}

cFontSheet::~cFontSheet()
{
	this->_sprites.clear();
	this->_canvas->Release();
}

void cFontSheet::Draw(cRect *destRect, STRING string)
{
	unsigned long i = 0;
	while(i < string.length())
	{
		this->DrawCharacter(destRect, string[i]);
		i++;
	}
}

void cFontSheet::DrawCharacter(cRect *destRect, TCHAR character)
{
	try
	{
	cRect *c = this->_GetRect(character);
	cGraphicsManager::Draw(destRect, this->GetCanvas(), c);
	destRect->Shift(c->Width(), 0.0);
	}
	catch(STRING ex)
	{
		STRING temp = ex;
	}
}

POINT2D cFontSheet::GetSize(STRING string)
{
	POINT2D size;
	size.x = 0;
	size.y = 0;

	for(unsigned int i=0;i<string.length();i++)
	{
		cRect* c = this->_GetRect(string[i]);
		size.x += c->Width();
		size.y = (c->Height() > size.y)?c->Height():size.y;
	}
	return(size);	
}
cRect* cFontSheet::_GetRect(TCHAR character)
{
	cRect *c = NULL;
	if(this->_sprites.end() != this->_sprites.find(character))
	{
		c = this->_sprites[character];
	}
	else
	{
		c = this->_sprites[TEXT('/')];
	}
	return(c);
}