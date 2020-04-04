#pragma once
#include "UserInterface.h"

class CUserInterface;
class CStatus :
	public CUserInterface
{
public:
	static bool m_bRenderCheckStatus;
private:
	bool		m_bDragCheck;
	RECT		m_rcDragStatus;
	CUserInterface *m_pUI;
private:
	INFO		m_tLevel;
	INFO		m_tName;
	INFO		m_tAtt;
	INFO		m_tDef;
	INFO		m_tHp;
	INFO		m_tMp;
public:
	virtual HRESULT	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(void);
	virtual void	Release(void);
public:
	void	UpdateFont(void);
	void    RenderFont(void);
public:
	CStatus();
	virtual ~CStatus();
};

