#pragma once
#include "GameObject.h"
class CCursor :
	public CGameObject
{
private:
	wstring		m_wstrStateKey;
	FRAME		m_tFrame;
	bool		m_bChangeCheck;
	eMouseState m_eMouseState;
public:
	static bool m_bBattleCheck;
	static bool m_bGateCheck;
public:
	virtual HRESULT	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(void);
	virtual void	Release(void);
public:
	void MyMatrix(void);
	void MyFrame(void);
	void StateCheck(void);
public:
	CCursor();
	virtual ~CCursor();
};

