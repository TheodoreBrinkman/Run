/**************************************************************************\
*                                                                          *
*	Copyright © 2009-2010 Theo Brinkman. All rights reserved.              *
*	See COPYING.TXT for details.                                           *
*                                                                          *
*	This software is distributed WITHOUT ANY WARRANTY; without even        *
*	the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR    *
*	PURPOSE.  See the above copyright notices for more information.        *
*                                                                          *
\**************************************************************************/
#include "cCanvasDX.h"

// CONSTRUCTORS
cCanvasDX::cCanvasDX(LPDIRECT3DTEXTURE9 d3dTexture, unsigned long width, unsigned long height)
{
	this->_texture = d3dTexture;
	this->_surface = NULL;
	this->_width = width;
	this->_height = height;
}

cCanvasDX::cCanvasDX(LPDIRECT3DSURFACE9 d3dSurface, unsigned long width, unsigned long height)
{
	this->_surface = d3dSurface;
	this->_texture = NULL;
	this->_width = width;
	this->_height = height;
}

// DESTRUCTOR
cCanvasDX::~cCanvasDX()
{
	this->Release();
}

LPDIRECT3DSURFACE9 cCanvasDX::GetSurface()
{
	return(this->_surface);
}

LPDIRECT3DTEXTURE9 cCanvasDX::GetTexture()
{
	return(this->_texture);
}

// PRIVATE METHODS
cRect* cCanvasDX::Size()
{
	return(new cRect(this->_width, this->_height));
}

void cCanvasDX::Release()
{
	if(NULL != this->_texture)
	{
		this->_texture->Release();
		this->_texture = NULL;
	}
	if(NULL != this->_surface)
	{
		this->_surface->Release();
		this->_surface = NULL;
	}
}

