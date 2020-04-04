#pragma once
#include "UserInterface.h"

#include "include.h"

class CHpBar :
	public CUserInterface
{
private:
	int		m_iHp;
	int		m_iMaxHp;
public:
	virtual HRESULT	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(void);
	virtual void	Release(void);
public:
	int    GetHp(void)
	{
		return m_iHp;
	}
public:
	CHpBar();
	virtual ~CHpBar();
};

