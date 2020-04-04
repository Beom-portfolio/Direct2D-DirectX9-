#pragma once
#include "GameObject.h"

#include "Include.h"


class CNormEffect :
	public CGameObject
{
protected:
	FRAME		 m_tFrame;
	wstring		 m_wstrStateKey;
	eEffectType  m_eEffectType;

public:
	virtual HRESULT	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(void);
	virtual void	Release(void);

public:
	int Update(D3DXVECTOR3 Pos);
	void MyMetrixCheck(D3DXVECTOR3 Pos);
	int MyFrameCheck(void);

public:
	CNormEffect();
	CNormEffect(D3DXVECTOR3 Pos, eEffectType EffectType);
	virtual ~CNormEffect();
};

