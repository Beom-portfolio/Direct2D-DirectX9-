#pragma once
#include "GameObject.h"

class CPlayer;
class CBoss;
class CBossBullet :
	public CGameObject
{
private:
	CPlayer* m_pPlayer;
	CBoss*	 m_pBoss;
	float	 fAngle;
	float    fAngle2;
	float    fSpinAngle;
	wstring  m_wstrStateKey;
	FRAME    m_tFrame;
	float	 m_tRemainTime;
private:
	FRAME	 m_EndFrame;
	bool     m_bEndCheck;
	bool     m_bDeleteCheck;
public:
	virtual HRESULT	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(void);
	virtual void	Release(void);

private:
	void AI(void);
	void MyMatrixCheck(void);
	void MyFrameCheck(void);

public:
	CBossBullet();
	CBossBullet(INFO Boss);
	virtual ~CBossBullet();
};

