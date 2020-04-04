#pragma once
#include "UserInterface.h"
class JHpBar :
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
	JHpBar();
	virtual ~JHpBar();
};

