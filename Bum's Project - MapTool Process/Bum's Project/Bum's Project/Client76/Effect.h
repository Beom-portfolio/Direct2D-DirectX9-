#pragma once
#include "GameObject.h"



class CBridge;
class CEffect :
	public CGameObject
{
private:
	CBridge*       m_pBridge;

public:
	void SetBridge(CBridge* pBridge)
	{
		m_pBridge = pBridge;
	}

public:
	virtual HRESULT	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(void);
	virtual void    Release(void);

public:
	CEffect();
	virtual ~CEffect();
};

