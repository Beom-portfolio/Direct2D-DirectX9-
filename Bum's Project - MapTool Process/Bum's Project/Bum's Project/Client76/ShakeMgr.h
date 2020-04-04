#pragma once

#include "Include.h"

class CShakeMgr
{
	DECLARE_SINGLETON(CShakeMgr);
private:
	eShakeType		m_eShakeType;
	float			m_fPower;
	float			m_fDividePower;
	D3DXVECTOR3		m_vecDir;

	bool			m_bActive;
	bool			m_bBack;
	D3DXVECTOR3&	m_vecScroll;
	int				m_iRand;

	float			m_fAngle;
	D3DXMATRIX		m_matRotZ;
	float			m_fTime;

public:
	void			Progress(void);
	void			SetShake(eShakeType eShakeType, float fPower, D3DXVECTOR3 vecDir = D3DXVECTOR3());

private:
	CShakeMgr();
public:
	~CShakeMgr();
};

