#pragma once
#include "GameObject.h"
class CMonHpBar :
	public CGameObject
{
private:
	int			m_iBottom;
	int			m_iMaxHp;
	int		    m_iHp;
	INFO		m_tHP;
	float       m_fHP;
	RECT		m_rcHP;
public:
	virtual HRESULT	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(void);
	virtual void	Release(void);

public:
	int Update(D3DXVECTOR3 Pos, int Hp);

public:
	void SetHp(int Hp)
	{
		m_iHp = Hp;
	}

public:
	CMonHpBar();
	CMonHpBar(D3DXVECTOR3 Pos, int Hp, int Bottom);
	virtual ~CMonHpBar();
};

