#pragma once
#include "stdafx.h"
#include "Include.h"

class CSoundMgr
{
	DECLARE_SINGLETON(CSoundMgr)
public:
	enum ChannelID { Channel_Player, Channel_Mon, Channel_BGM, Channel_Eff, Channel_End };

public:
	CSoundMgr(void);
	~CSoundMgr(void);

public:
	void Initialize();
	void LoadSoundFile();
	void PlaySound(TCHAR* pSoundKey, ChannelID eID);
	void PlayBGM(TCHAR* pSoundKey, ChannelID eID);
	void UpdateSound();
	void StopSound(ChannelID eID);
	void StopAll();
	void Release();

private:
	FMOD_SYSTEM*	m_pSystem;
	FMOD_CHANNEL*	m_pChannelArr[Channel_End]; // 채널은 중첩되지 않게 준비.

	map<const TCHAR*, FMOD_SOUND*>	m_MapSound;
};
