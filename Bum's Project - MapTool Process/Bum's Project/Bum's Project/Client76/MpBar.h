#pragma once
#include "UserInterface.h"

#include "Include.h"

class CMpBar :
	public CUserInterface
{
private:
	int		m_iMp;
	int		m_iMaxMp;
public:
	virtual HRESULT	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(void);
	virtual void	Release(void);
public:
	int    GetMp(void)
	{
		return m_iMp;
	}
public:
	CMpBar();
	virtual ~CMpBar();
};

