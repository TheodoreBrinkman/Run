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
#include "cAudioManagerDX.h"

// CONSTRUCTORS
cAudioManagerDX::cAudioManagerDX(IWindowManager *window, unsigned long dwCoopLevel)
{
	this->_Initialize((cWindowManagerDX*)window, dwCoopLevel);
}

// DESTRUCTOR
cAudioManagerDX::~cAudioManagerDX()
{
	this->_sounds.clear();
}

// PUBLIC METHODS
void cAudioManagerDX::RegisterSound(STRING audioFilePath)
{
	if(!this->_Exists(audioFilePath))
	{
		// did not exist
		cSoundDX* sound = NULL;
		TCHAR *path = new TCHAR[audioFilePath.length() + 1];
		audioFilePath.assign(path);
		this->_soundManager->Create(&sound, path, 0, GUID_NULL, 1);
		this->_sounds[audioFilePath] = sound;
		this->_references[audioFilePath] = 0;
	}
	this->_references[audioFilePath]++;
}

void cAudioManagerDX::ReleaseSound(STRING audioFilePath)
{
	if(this->_Exists(audioFilePath))
	{
		this->_references[audioFilePath]--;
		if(this->_references[audioFilePath] > 0)
		{
			this->_sounds.erase(audioFilePath);
		}
	}
}

void cAudioManagerDX::Play(STRING audioFilePath)
{
	this->_sounds[audioFilePath]->Play();
}
void cAudioManagerDX::Loop(STRING audioFilePath)
{
	this->_sounds[audioFilePath]->Play(0, DSBPLAY_LOOPING);
}
void cAudioManagerDX::Stop(STRING audioFilePath)
{
	this->_sounds[audioFilePath]->Stop();
}

void cAudioManagerDX::Release()
{
}

//PRIVATE METHODS
bool cAudioManagerDX::_Exists(STRING audioFilePath)
{
	return(this->_references.end() != this->_references.find(audioFilePath));
}

void cAudioManagerDX::_Initialize(cWindowManagerDX *window, unsigned long dwCoopLevel)
{
	this->_soundManager = new cSoundManagerDX();
	this->_soundManager->Initialize(window->hWnd(), dwCoopLevel);
}