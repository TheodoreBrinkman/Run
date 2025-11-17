/******************************************************************************\
*                                                                              *
*	Copyright © 2010 Andrew Dabrowski, Theo Brinkman. All rights reserved.     *
*                                                                              *
*	This work is licensed under a Creative Commons                             *
*	Attribution-Noncommercial-No Derivative Works 3.0 United States License.   *
*                                                                              *
*	See COPYING.TXT for details.                                               *
*                                                                              *
\******************************************************************************/
#include "cGraphicsManagerSDL.h"

// CONSTRUCTORS
cGraphicsManagerSDL::cGraphicsManagerSDL(IWindowManager *window)
{
	this->_title = window->title();
	this->_width = window->width();
	this->_height = window->height();
	this->_fullscreen = window->isFullscreen();

	this->_Initialize((cWindowManagerSDL*)window);
}

// DESTRUCTOR
cGraphicsManagerSDL::~cGraphicsManagerSDL()
{
	this->Release();
}

void cGraphicsManagerSDL::_Initialize(cWindowManagerSDL *window)
{
	SDL_FillRect(this->_GetSurface(), &this->_GetSurface()->clip_rect, SDL_MapRGB(this->_GetSurface()->format, 0xFF, 0xFF, 0xFF));
}

cCanvasSDL* cGraphicsManagerSDL::RegisterSurface(STRING key, unsigned long width, unsigned long height, cColor *bgColor)
{
	if(!this->_Exists(key))
	{
		cRect *rect = new cRect(width, height);
		SDL_Surface *surface = new SDL_Surface();
		SDL_FillRect(surface, &cGraphicsManagerSDL::ToRect(rect), (Uint32)cGraphicsManagerSDL::ToColor(bgColor));
		this->_canvases[key] = new cCanvasSDL(this->_GetSurface(), width, height);
		this->_references[key] = 0;
	}
	this->_references[key]++;
	return(this->_canvases[key]);
}

cCanvasSDL* cGraphicsManagerSDL::RegisterBackgroundImage(STRING imageFilePath, cColor *transparentColor, cColor *bgColor)
{
	if(!this->_Exists(imageFilePath))
	{
		SDL_Surface *surface = cGraphicsManagerSDL::_LoadTexture(imageFilePath, transparentColor);
		this->_canvases[imageFilePath] = new cCanvasSDL(surface, surface->w, surface->h);
		this->_references[imageFilePath] = 0;
	}
	this->_references[imageFilePath]++;
	return(this->_canvases[imageFilePath]);
}

cCanvasSDL* cGraphicsManagerSDL::RegisterSpriteSheet(STRING imageFilePath)
{
	return(this->RegisterSpriteSheet(imageFilePath, NULL));
}

cCanvasSDL* cGraphicsManagerSDL::RegisterSpriteSheet(STRING imageFilePath, cColor *transparentColor)
{
	if(!this->_Exists(imageFilePath))
	{
		SDL_Surface *surface = cGraphicsManagerSDL::_LoadTexture(imageFilePath, transparentColor);
		this->_canvases[imageFilePath] = new cCanvasSDL(surface, surface->w, surface->h);
		this->_references[imageFilePath] = 0;
	}
	this->_references[imageFilePath]++;
	return(this->_canvases[imageFilePath]);
}

void cGraphicsManagerSDL::ReleaseSurface(STRING key)
{
	this->_Release(key);
}

void cGraphicsManagerSDL::ReleaseBackgroundImage(STRING imageFilePath)
{
	this->_Release(imageFilePath);
}

void cGraphicsManagerSDL::ReleaseSpriteSheet(STRING imageFilePath)
{
	this->_Release(imageFilePath);
}

void cGraphicsManagerSDL::Clear(ICanvas *canvas)
{
	this->_Clear((cCanvasSDL*)canvas, new cColor());
}

void cGraphicsManagerSDL::Clear(ICanvas *canvas, cColor *bgColor)
{
	this->_Clear((cCanvasSDL*)canvas, bgColor);
}

void cGraphicsManagerSDL::_Clear(cCanvasSDL* canvas, cColor *bgColor)
{
	throw("GraphicsManagerSDL::_Clear() - Not yet implemented.");
}

void cGraphicsManagerSDL::Draw(cRect *destRect, ICanvas *srcCanvas)
{
	this->_Draw(destRect, (cCanvasSDL*)srcCanvas, srcCanvas->Size(), false);
}

void cGraphicsManagerSDL::Draw(cRect *destRect, ICanvas *srcCanvas, bool flipped)
{
	this->_Draw(destRect, (cCanvasSDL*)srcCanvas, srcCanvas->Size(), flipped);
}

void cGraphicsManagerSDL::Draw(cRect *destRect, ICanvas *srcCanvas, cRect *srcRect)
{
	this->_Draw(destRect, (cCanvasSDL*)srcCanvas, srcRect, false);
}

void cGraphicsManagerSDL::Draw(cRect *destRect, ICanvas *srcCanvas, cRect *srcRect, bool flipped)
{
	this->_Draw(destRect, (cCanvasSDL*)srcCanvas, srcRect, flipped);
}

void cGraphicsManagerSDL::Draw(ICanvas *destCanvas, cRect *destRect, ICanvas *srcCanvas, cRect *srcRect)
{
	this->_Draw((cCanvasSDL*)destCanvas, destRect, (cCanvasSDL*)srcCanvas, srcRect, false);
}

void cGraphicsManagerSDL::Draw(ICanvas *destCanvas, cRect *destRect, ICanvas *srcCanvas, cRect *srcRect, bool flipped)
{
	this->_Draw((cCanvasSDL*)destCanvas, destRect, (cCanvasSDL*)srcCanvas, srcRect, flipped);
}

void cGraphicsManagerSDL::_Draw(cRect *destRect, cCanvasSDL *srcCanvas, cRect *srcRect, bool flipped)
{
	cWindowManagerSDL *window = ((cWindowManagerSDL*)cWindowManager::window());
	this->_Draw(window->screen(), destRect, srcCanvas->GetSurface(), srcRect, flipped);
}

void cGraphicsManagerSDL::_Draw(cCanvasSDL *destCanvas, cRect *destRect, cCanvasSDL *srcCanvas, cRect *srcRect, bool flipped)
{
	this->_Draw(destCanvas->GetSurface(), destRect, srcCanvas->GetSurface(), srcRect, flipped);
}

void cGraphicsManagerSDL::_Draw(SDL_Surface *destSurface, cRect *destRect, SDL_Surface *srcSurface, cRect *srcRect, bool flipped)
{
	// This branch must remain like this, because running through the copy process
	// on every item to be drawn is prohibitively expensive.  Since only the avatar
	// actually needs to be flipped, the performance is still good this way.
	if(flipped)
	{
		SDL_Surface *src = cGraphicsManagerSDL::_CopyRect(srcSurface, srcRect);
		cGraphicsManagerSDL::_FlipSurface(src);
		if(destRect != NULL)
		{
			SDL_BlitSurface(src, &src->clip_rect, destSurface, &ToRect(destRect));
		}
		else
		{
			SDL_BlitSurface(src, &src->clip_rect, destSurface, NULL);
		}
		// Freeing this surface causes a crash.  Not sure why, since I think you're
		// *supposed* to free a surface when you know you're done with it.
		// Could be a memory leak.
		//SDL_FreeSurface(src);
	}
	else
	{
		if(destRect != NULL)
		{
			SDL_BlitSurface(srcSurface, &ToRect(srcRect), destSurface, &ToRect(destRect));
		}
		else
		{
			SDL_BlitSurface(srcSurface, &ToRect(srcRect), destSurface, NULL);
		}
	}
}

bool cGraphicsManagerSDL::BeginScene()
{
	SDL_Surface* surface = this->_GetSurface();
	if(NULL == surface)
	{
		return false;
	}
	if(SDL_MUSTLOCK(surface))
	{
		if(-1 == SDL_LockSurface(surface))
		{
			throw("Could not lock the screen!");
		}
	}
	SDL_FillRect(surface, &surface->clip_rect, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF ) );
	return true;
}

void cGraphicsManagerSDL::EndScene()
{
	SDL_Surface* surface = this->_GetSurface();
	if(SDL_MUSTLOCK(surface))
	{
		SDL_UnlockSurface(surface);
	}
	SDL_UpdateRect(surface, 0, 0, 0, 0);
	if(-1 == SDL_Flip(surface))
	{
		throw("cGraphicsManagerSDL::EndScene() - Error updating the screen.");
	}
}

void cGraphicsManagerSDL::Release()
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

	SDL_Quit();
}

SDL_Surface* cGraphicsManagerSDL::_GetSurface()
{
	return(((cWindowManagerSDL*)cWindowManager::window())->screen());
}

void cGraphicsManagerSDL::_LoadSurface(SDL_Surface *surface, STRING imageFilePath, cColor *transparentColor)
{
	surface = cGraphicsManagerSDL::_LoadTexture(imageFilePath, transparentColor);
}

SDL_Surface* cGraphicsManagerSDL::_LoadTexture(STRING imageFilePath, cColor *transparentColor)
{
    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimizedImage = NULL;

	std::string ConvertedPath(imageFilePath.begin(), imageFilePath.end());
	ConvertedPath.assign(imageFilePath.begin(), imageFilePath.end());

	loadedImage = IMG_Load(ConvertedPath.c_str());
	if(NULL == loadedImage)
	{
		throw("cGraphicsManagerSDL::_LoadTexture() - Could not load image from file.");
	}
	else
    {
        optimizedImage = SDL_DisplayFormatAlpha(loadedImage);
		if(NULL == optimizedImage)
		{
			throw("cGraphicsManagerSDL::_LoadTexture() - Could not optimize image.");
		}
		if(loadedImage != optimizedImage)
		{
	        SDL_FreeSurface(loadedImage);
		}
        if(NULL != transparentColor)
        {
			SDL_Color *color = ToColor(transparentColor);
            SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB(optimizedImage->format, color->r, color->g, color->b));
        }
    }

    return optimizedImage;
}

bool cGraphicsManagerSDL::_Exists(STRING key)
{
	return(this->_references.end() != this->_references.find(key));
}

void cGraphicsManagerSDL::_Release(STRING key)
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
SDL_Rect cGraphicsManagerSDL::ToRect(cRect* rect)
{
	//DirectX RECT
	//left:	The x-coordinate of the upper-left corner of the rectangle.
	//top:	The y-coordinate of the upper-left corner of the rectangle.
	//right:	The x-coordinate of the lower-right corner of the rectangle.
	//bottom:	The y-coordinate of the lower-right corner of the rectangle.

	//SDL SDL_Rect
	//x, y:	Position of the upper-left corner of the rectangle
	//w, h:	The width and height of the rectangle

	SDL_Rect r;
	//Width of rectangle
	r.w = (Uint16)rect->Right - (Uint16)rect->Left;

	//Height of rectangle
	r.h = (Uint16)rect->Bottom - (Uint16)rect->Top;

	//Upper Left X position
	r.x = (Sint16)rect->Left;

	//Upper Left Y position
	r.y = (Sint16)rect->Top;

	return(r);
}

cRect* cGraphicsManagerSDL::ToRect(SDL_Rect rect)
{
    //cRect: Top, left, right, bottom
    //SDL_Rect: y, x, x+w, y+h
    return(new cRect(rect.y, rect.x, rect.x + rect.w, rect.h + rect.y));
}

SDL_Color* cGraphicsManagerSDL::ToColor(cColor *color)
{
	SDL_Color *newColor = new SDL_Color();
	newColor->r = (Uint8)color->Red;
	newColor->g = (Uint8)color->Green;
	newColor->b = (Uint8)color->Blue;
	return(newColor);
}

cColor* cGraphicsManagerSDL::ToColor(SDL_Color *color)
{
	return(new cColor(color->r, color->g, color->b));
}

/*
D3DXVECTOR3 cGraphicsManagerDX::ToVector(cRect *rect)
{
	D3DXVECTOR3 v;
	v.x = (float)rect->Left;
	v.y = (float)rect->Top;
	v.z = 0;
	return(v);
}
*/

//Creates a copy of a section of an SDL_Surface.
SDL_Surface* cGraphicsManagerSDL::_CopyRect(SDL_Surface *surface, cRect *rect)
{
	SDL_Rect size = cGraphicsManagerSDL::ToRect(rect);
	SDL_Surface *copy = SDL_CreateRGBSurface(SDL_SWSURFACE, size.w, size.h, surface->format->BitsPerPixel, surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, surface->format->Amask);
	if(NULL == copy)
	{
		throw("cGraphicsManagerSDL::_CopyRect() - Unable to create surface!");
	}
	if(SDL_MUSTLOCK(copy))
	{
		SDL_LockSurface(copy);
	}
	// Copy the pixel values to maintain transparancy
	for(int x = 0; x < size.w; x++)
	{
		for(int y = 0; y < size.h; y++)
		{
			Uint32 pix = cGraphicsManagerSDL::_GetPixel(surface, size.x + x, size.y + y);
			cGraphicsManagerSDL::_SetPixel(copy, x, y, pix);
		}
	}
	if(SDL_MUSTLOCK(copy))
	{
		SDL_UnlockSurface(copy);
	}
	return(copy);
}

// Gets the value of a pixel in an SDL_Surface.
Uint32 cGraphicsManagerSDL::_GetPixel(SDL_Surface *surface, int x, int y)
{
	Uint32 *pixels = (Uint32*)surface->pixels;
    return pixels[(y * surface->w) + x];
}

// Sets the value of a pixel in an SDL_Surface.
void cGraphicsManagerSDL::_SetPixel(SDL_Surface *surface, int x, int y, Uint32 value)
{
	Uint32 *pixels = (Uint32 *)surface->pixels;
    pixels[(y * surface->w) + x] = value;

}

//Flips the contents of an SDL_Surface horizontally.
void cGraphicsManagerSDL::_FlipSurface(SDL_Surface *surface)
{
	// Flip the sprite before drawing it!!!
	if(SDL_MUSTLOCK(surface))
	{
		SDL_LockSurface(surface);
	}
	// flip the pixel values horizontally
	for(int x = 0; x < surface->w / 2; x++)
	{
		int rx = surface->w - x;
		for(int y = 0; y < surface->h; y++)
		{
			Uint32 pix1 = cGraphicsManagerSDL::_GetPixel(surface, x, y);
			Uint32 pix2 = cGraphicsManagerSDL::_GetPixel(surface, rx, y);

			cGraphicsManagerSDL::_SetPixel(surface, x, y, pix2);
			cGraphicsManagerSDL::_SetPixel(surface, rx, y, pix1);
		}
	}
	if(SDL_MUSTLOCK(surface))
	{
		SDL_UnlockSurface(surface);
	}
}