#pragma once
#include "GameObject.h"

#include "Include.h"

class CWeapon :
	public CGameObject
{
private:
	wstring m_wstrStateKey;
	FRAME	m_tFrame;
	float   m_RightCheck;
	ePlayerState PlayerState;
	eWeaponState m_eState;
	bool	m_bRunCheck;
	bool    m_bChangeCheck;
	bool	m_bRenderCheck;

public:
	void SetINFO(INFO Info)
	{
		m_tInfo = Info;
	}

public:
	virtual HRESULT	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(void);
	virtual void	Release(void);

public:
	void	Update(INFO Info,  eDir Dir, ePlayerState State);

private:
	void SetSwordPosFromPlayer(INFO Info);
	void SetDirFromPlayer(eDir Dir);
	void SetStateFromPlayer(ePlayerState State);
	void WeaponState(void);
	void MyMatrixCheck(void);
	void MyFrameCheck(void);

public:
	CWeapon();
	virtual ~CWeapon();
};

