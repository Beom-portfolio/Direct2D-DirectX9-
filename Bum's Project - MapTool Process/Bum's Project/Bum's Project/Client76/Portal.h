#pragma once
#include "GameObject.h"
class CPortal :
	public CGameObject
{
private:
	wstring		m_wstrStateKey;
	FRAME		m_tFrame;
public:
	virtual HRESULT	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(void);
	virtual void	Release(void);
public:
	void MyMatrix(void);
	void MyFrame(void);
public:
	CPortal();
	virtual ~CPortal();
};

