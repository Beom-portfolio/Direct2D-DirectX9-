#pragma once
#include "GameObject.h"

#include "Include.h"

class CCritical :
	public CGameObject
{
private:
	D3DXVECTOR3 m_tsize;
	float	    m_fForce;
	float		m_Up;
	int			m_Alpa;
	int			m_iBottom;
protected:
	FRAME		 m_tFrame;
	wstring		 m_wstrStateKey;
	eEffectType  m_eEffectType;
private:
	bool    m_big;
	bool    m_small;

public:
	virtual HRESULT	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(void);
	virtual void	Release(void);

public:
	int Update(D3DXVECTOR3 Pos);

public:
	CCritical();
	CCritical(D3DXVECTOR3 Pos, int Bottom);
	virtual ~CCritical();
};

