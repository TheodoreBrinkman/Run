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
#include "cAudioManager.h"

// STATIC INITIALIZATION
IAudioManager* cAudioManager::_manager = NULL;

// FACTORY METHODS
void cAudioManager::Initialize()
{
	cAudioManager::Release();
	cAudioManager::_manager = NULL;
	switch(cWindowManager::window()->audioMethod())
	{
		case AudioManager::DirectSound:
			cAudioManager::_manager = new cAudioManagerDX(cWindowManager::window(), DSSCL_PRIORITY);
			break;
		case AudioManager::SDL:
			// This space intentionally left blank due to time constraints.
			break;
		case AudioManager::OpenGL:
		case AudioManager::CoreAudio:
		default:
			throw("Not yet implemented.");
			break;
	}
}

// PUBLIC METHODS
void cAudioManager::RegisterSound(STRING audioFilePath)
{
	if(NULL != cAudioManager::_manager)
	{
		cAudioManager::_manager->RegisterSound(audioFilePath);
	}
}

void cAudioManager::Play(STRING audioFilePath)
{
	if(NULL != cAudioManager::_manager)
	{
		cAudioManager::_manager->Play(audioFilePath);
	}
}

void cAudioManager::Loop(STRING audioFilePath)
{
	if(NULL != cAudioManager::_manager)
	{
		cAudioManager::_manager->Loop(audioFilePath);
	}
}

void cAudioManager::Stop(STRING audioFilePath)
{
	if(NULL != cAudioManager::_manager)
	{
		cAudioManager::_manager->Stop(audioFilePath);
	}
}

void cAudioManager::ReleaseSound(STRING audioFilePath)
{
	if(NULL != cAudioManager::_manager)
	{
		cAudioManager::_manager->ReleaseSound(audioFilePath);
	}
}

void cAudioManager::Release()
{
	if(NULL != cAudioManager::_manager)
	{
		cAudioManager::_manager->Release();
		cAudioManager::_manager = NULL;
	}
}

// PRIVATE METHODS
