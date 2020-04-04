#pragma once
#include "gameobject.h"

class CBackGround :
	public CGameObject
{
private:
	BACK*        m_BackMainInfo;
	BACKINFO	 m_BackInfo;
	TCHAR		 *szBackType;

public:
	virtual HRESULT	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(void);
	virtual void	Release(void);

public:
	void LoadBackGround(void);
	void MouseScrollCheck(void);


public:
	CBackGround(void);
	virtual ~CBackGround(void);
};
