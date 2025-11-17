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
#include "cGraphicsManagerDX.h"

// CONSTRUCTORS
cGraphicsManagerDX::cGraphicsManagerDX(IWindowManager *window)
{
	this->_width = window->width();
	this->_height = window->height();
	this->_fullscreen = window->isFullscreen();

	this->_Initialize((cWindowManagerDX*)window);
}

void cGraphicsManagerDX::_Initialize(cWindowManagerDX *window)
{
	this->_hWnd = window->hWnd();
	// Initialize Direct3D
	this->_d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if(NULL == this->_d3d)
	{
		throw("cGraphicsManagerDX::cGraphicsManagerDX() - Could not initialize Direct3D.");
	}

	// set Direct3D presentation parameters
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = !this->_fullscreen;
	d3dpp.SwapEffect = D3DSWAPEFFECT_COPY;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8; //(fullscreen)?D3DFMT_UNKNOWN:D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = this->_width;
	d3dpp.BackBufferHeight = this->_height;
	d3dpp.hDeviceWindow = this->_hWnd;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

	this->_d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, this->_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &this->_d3ddev);
	if(NULL == this->_d3ddev)
	{
		throw("cGraphicsManagerDX::cGraphicsManagerDX() - Could not allocate a Direct3D device.");
	}
	// clear the backbuffer to white
	this->_d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);
	// Ensure that the current backbuffer is in context
	this->_d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &this->_backbuffer);

	// Set up the sprite handler
	D3DXCreateSprite(this->_d3ddev, &this->_spriteHandler);
	if(NULL == this->_spriteHandler)
	{
		throw("cGraphicsManagerDX::cGraphicsManagerDX() - Could not initialize the sprite handler.");
	}
}

// DESTRUCTOR
cGraphicsManagerDX::~cGraphicsManagerDX()
{
	if(NULL != this->_d3d)
	{
		this->Release();
	}
}

// INTERFACE METHODS
cCanvasDX* cGraphicsManagerDX::RegisterSurface(STRING key, unsigned long width, unsigned long height, cColor *bgColor)
{
	if(!this->_Exists(key))
	{
		this->_canvases[key] = new cCanvasDX(cGraphicsManagerDX::_GetSurface(width, height, bgColor), width, height);
		this->_references[key] = 0;
	}
	this->_references[key]++;
	return(this->_canvases[key]);
}
cCanvasDX* cGraphicsManagerDX::RegisterBackgroundImage(STRING imageFilePath, cColor *transparentColor, cColor *bgColor)
{
	if(!this->_Exists(imageFilePath))
	{
		D3DXIMAGE_INFO info = cGraphicsManagerDX::_GetImageInfo(imageFilePath);
		LPDIRECT3DSURFACE9 surface = cGraphicsManagerDX::_GetSurface(info.Width, info.Height, bgColor);
		cGraphicsManagerDX::_LoadSurface(surface, imageFilePath, transparentColor);
		this->_canvases[imageFilePath] = new cCanvasDX(surface, info.Width, info.Height);
		this->_references[imageFilePath] = 0;
	}
	this->_references[imageFilePath]++;
	return(this->_canvases[imageFilePath]);
}
cCanvasDX* cGraphicsManagerDX::RegisterSpriteSheet(STRING imageFilePath, cColor *transparentColor)
{
	if(!this->_Exists(imageFilePath))
	{
		D3DXIMAGE_INFO info = cGraphicsManagerDX::_GetImageInfo(imageFilePath);
		LPDIRECT3DTEXTURE9 texture = cGraphicsManagerDX::_LoadTexture(imageFilePath, info, transparentColor);
		this->_canvases[imageFilePath] = new cCanvasDX(texture, info.Width, info.Height);
		this->_references[imageFilePath] = 0;
	}
	this->_references[imageFilePath]++;
	return(this->_canvases[imageFilePath]);
}

void cGraphicsManagerDX::ReleaseSurface(STRING key)
{
	this->_Release(key);
}
void cGraphicsManagerDX::ReleaseBackgroundImage(STRING imageFilePath)
{
	this->_Release(imageFilePath);
}
void cGraphicsManagerDX::ReleaseSpriteSheet(STRING imageFilePath)
{
	this->_Release(imageFilePath);
}

void cGraphicsManagerDX::Clear(ICanvas *canvas)
{
	this->_Clear((cCanvasDX*)canvas, new cColor());
}
void cGraphicsManagerDX::Clear(ICanvas *canvas, cColor *bgColor)
{
	this->_Clear((cCanvasDX*)canvas, bgColor);
}
void cGraphicsManagerDX::_Clear(cCanvasDX *canvas, cColor *bgColor)
{
	throw("GraphicsManagerDX::_Clear() - Not yet implemented.");
}

void cGraphicsManagerDX::Draw(cRect *destRect, ICanvas *srcCanvas)
{
	this->_Draw(destRect, (cCanvasDX*)srcCanvas, srcCanvas->Size(), false);
}
void cGraphicsManagerDX::Draw(cRect *destRect, ICanvas *srcCanvas, bool flipped)
{
	this->_Draw(destRect, (cCanvasDX*)srcCanvas, srcCanvas->Size(), flipped);
}
void cGraphicsManagerDX::Draw(cRect *destRect, ICanvas *srcCanvas, cRect *srcRect)
{
	this->_Draw(destRect, (cCanvasDX*)srcCanvas, srcRect, false);
}
void cGraphicsManagerDX::Draw(cRect *destRect, ICanvas *srcCanvas, cRect *srcRect, bool flipped)
{
	this->_Draw(destRect, (cCanvasDX*)srcCanvas, srcRect, flipped);
}
void cGraphicsManagerDX::Draw(ICanvas *destCanvas, cRect *destRect, ICanvas *srcCanvas, cRect *srcRect)
{
	this->_Draw((cCanvasDX*)destCanvas, destRect, (cCanvasDX*)srcCanvas, srcRect, false);
}
void cGraphicsManagerDX::Draw(ICanvas *destCanvas, cRect *destRect, ICanvas *srcCanvas, cRect *srcRect, bool flipped)
{
	this->_Draw((cCanvasDX*)destCanvas, destRect, (cCanvasDX*)srcCanvas, srcRect, flipped);
}

void cGraphicsManagerDX::_Draw(cCanvasDX *destCanvas, cRect *destRect, cCanvasDX *srcCanvas, cRect *srcRect, bool flipped)
{
	if(NULL == this->_d3d)
	{
		throw("cGraphicsManagerDX::_Draw() - DirectX is not initialized!");
	}
	HRESULT result;
	if(NULL != srcCanvas->GetTexture())
	{
		D3DXVECTOR3 dest = ToVector(destRect);
		D3DXMATRIX flip, out, now;
		this->_spriteHandler->GetTransform(&now);
		if(flipped)
		{
			D3DXMatrixScaling(&flip, -1, 1, 1);
			dest.x += (float)destRect->Width();
			dest.x = -dest.x;
		}
		else
		{
			D3DXMatrixScaling(&flip, 1, 1, 1);
		}
		D3DXMatrixMultiply(&out, &flip, &now);
		this->_spriteHandler->SetTransform(&out);
		result = this->_spriteHandler->Draw(srcCanvas->GetTexture(), &ToRect(srcRect), NULL, &dest, D3DCOLOR_XRGB(255,255,255));
//		result = this->_spriteHandler->Draw(srcCanvas->GetTexture(), &ToRect(srcRect), &ToCenter(destRect), &ToVector(destRect), D3DCOLOR_XRGB(255,255,255));
		this->_spriteHandler->SetTransform(&now);
	}
	else if(NULL != srcCanvas->GetSurface() && NULL != destCanvas->GetSurface())
	{
		result = this->_d3ddev->StretchRect(srcCanvas->GetSurface(), &ToRect(srcRect), destCanvas->GetSurface(), &ToRect(destRect), D3DTEXF_NONE);
	}
	if(D3D_OK != result)
	{
		throw("cGraphicsManagerDX::_Draw() - Failed.");
	}
}

void cGraphicsManagerDX::_Draw(cRect *destRect, cCanvasDX *srcCanvas, cRect *srcRect, bool flipped)
{
	this->_Draw(new cCanvasDX(this->_backbuffer, this->_width, this->_height), destRect, srcCanvas, srcRect, flipped);
}

bool cGraphicsManagerDX::BeginScene()
{
	this->_d3ddev->ColorFill(this->_backbuffer, NULL, D3DCOLOR_XRGB(255, 255, 255));
	HRESULT result = this->_d3ddev->BeginScene();
	this->_spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	return(S_OK == result);
}
void cGraphicsManagerDX::EndScene()
{
	this->_spriteHandler->End();
	this->_d3ddev->EndScene();
	this->_d3ddev->Present(NULL, NULL, NULL, NULL);
}

void cGraphicsManagerDX::Release()
{
	for each(std::pair<STRING, unsigned long> item in this->_references)
	{
		STRING key = item.first;
		if(item.second > 0)
		{
			this->_Release(key);
		}
	}
	this->_canvases.clear();
	this->_references.clear();
	this->_backbuffer->Release();
	this->_backbuffer = NULL;
	this->_d3ddev->Release();
	this->_d3ddev = NULL;
	this->_d3d->Release();
	this->_d3d = NULL;
}
// PRIVATE METHODS
D3DXIMAGE_INFO cGraphicsManagerDX::_GetImageInfo(STRING imageFilePath)
{
	D3DXIMAGE_INFO info;
	// get width and height from bitmap file
	HRESULT result = D3DXGetImageInfoFromFile(imageFilePath.c_str(), &info);
	if(D3D_OK != result)
	{
		throw("cGraphicsManager::GetSurface() - Failed to get image info from file.");
	}
	return(info);
}

LPDIRECT3DSURFACE9 cGraphicsManagerDX::_GetSurface(unsigned long width, unsigned long height, cColor *bgColor)
{
	LPDIRECT3DSURFACE9 surface = NULL;
	// create surface
	HRESULT result = this->_d3ddev->CreateOffscreenPlainSurface(width, height, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &surface, NULL);
	if(D3D_OK != result)
	{
		throw("cGraphicsManager::_GetSurface() - Could not allocate a surface.");
	}
	if(NULL != bgColor)
	{
		RECT size;
		size.top = 0;
		size.left = 0;
		size.right = width - 1;
		size.bottom = height - 1;
		result = this->_d3ddev->ColorFill(surface, &size, ToColor(bgColor));
		if(D3D_OK != result)
		{
			throw("cGraphicsManager::_GetSurface() - Could not apply background color.");
		}
	}
	return(surface);
}

void cGraphicsManagerDX::_LoadSurface(LPDIRECT3DSURFACE9 surface, STRING imageFilePath, cColor *transparentColor)
{
	// load image from file into newly created surface
	D3DCOLOR tcolor = cGraphicsManagerDX::ToColor(transparentColor);
	HRESULT result = D3DXLoadSurfaceFromFile(surface, NULL, NULL, imageFilePath.c_str(), NULL, D3DX_DEFAULT, tcolor, NULL);
	if(D3D_OK != result)
	{
		throw("cGraphicsManager::_LoadSurface() - Could not load image from file.");
	}
}

LPDIRECT3DTEXTURE9 cGraphicsManagerDX::_LoadTexture(STRING imageFilePath, D3DXIMAGE_INFO info, cColor *transparentColor)
{
	LPDIRECT3DTEXTURE9 texture = NULL;
	// load image from file into newly created texture
	D3DCOLOR tcolor = cGraphicsManagerDX::ToColor(transparentColor);
	HRESULT result = D3DXCreateTextureFromFileEx(this->_d3ddev, imageFilePath.c_str(), info.Width, info.Height, 1, D3DPOOL_DEFAULT, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, tcolor, &info, NULL, &texture);

	if(D3D_OK != result)
	{
		throw("cGraphicsManagerDX::_LoadTexture() - Could not load image from file.");
	}
	return(texture);
}

bool cGraphicsManagerDX::_Exists(STRING key)
{
	return(this->_references.end() != this->_references.find(key));
}

void cGraphicsManagerDX::_Release(STRING key)
{
	if(this->_Exists(key))
	{
		this->_references[key]--;
		if(this->_references[key] > 0)
		{
			this->_canvases[key]->Release();
			this->_canvases.erase(key);
		}
	}
}

// PRIVATE STATIC METHODS
RECT cGraphicsManagerDX::ToRect(cRect *rect)
{
	RECT r;
	r.top = (long)rect->Top;
	r.left = (long)rect->Left;
	r.right = (long)rect->Right;
	r.bottom = (long)rect->Bottom;
	return(r);
}
D3DXVECTOR3 cGraphicsManagerDX::ToVector(cRect *rect)
{
	D3DXVECTOR3 v;
	v.x = (float)rect->Left;
	v.y = (float)rect->Top;
	v.z = 0;
	return(v);
}
D3DXVECTOR3 cGraphicsManagerDX::ToCenter(cRect *rect)
{
	D3DXVECTOR3 v;
	POINT2D c = rect->Center();
	v.x = (float)c.x;
	v.y = (float)c.y;
	v.z = 0.0;
	return(v);
}

cRect* cGraphicsManagerDX::ToRect(RECT rect)
{
	return(new cRect(rect.top, rect.left, rect.right, rect.bottom));
}

D3DCOLOR cGraphicsManagerDX::ToColor(cColor* color)
{
	if(NULL == color)
	{
		return(NULL);
	}
	else
	{
		return(D3DCOLOR_RGBA(color->Red, color->Green, color->Blue, color->Alpha));
	}
}

cColor* cGraphicsManagerDX::ToColor(D3DCOLOR color)
{
	return(new cColor(color));
}
