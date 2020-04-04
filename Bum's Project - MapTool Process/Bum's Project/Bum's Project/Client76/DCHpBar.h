#pragma once
#include "UserInterface.h"

#include "Include.h"

class CDCHpBar :
	public CUserInterface
{
private:
	int		m_iHp;
public:
	virtual HRESULT	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(void);
	virtual void	Release(void);
public:
	CDCHpBar();
	virtual ~CDCHpBar();
};

