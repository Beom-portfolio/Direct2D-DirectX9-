#pragma once

#include "Include.h"

class CNormEffect;
class CDamage;
class CCritical;
class CGameObject
{

protected:
	INFO		m_tInfo;
	eDir        m_eDir;
	RECT		m_rc;
	RECT		m_AttackRange;
	wstring		m_wstrObjKey;
	eRenderType m_RenderType;
	float		fSpeed;
	float		m_fTime;

	vector<CDamage*>	 m_vecDamage;
	vector<CNormEffect*> m_vecDmgEffect;
	vector<CCritical*>   m_vecCriEffect;
protected:
	int			m_iHp;
	int			m_iAttack;

	//
	bool		m_bDeadCheck;
	float		m_fUp;
	int			m_Alpa;

public:
	const wstring& GetObjKey(void)
	{
		return m_wstrObjKey;
	}
	INFO   GetNormInfo(void)
	{
		return m_tInfo;
	}
	const INFO* GetInfo(void)
	{
		return &m_tInfo;
	}
	eDir   GetDir(void)
	{
		return m_eDir;
	}
	RECT* GetRect(void)
	{
		return &m_rc;
	}
	RECT* GetAttackRange(void)
	{
		return &m_AttackRange;
	}
	eRenderType GetRenderType(void)
	{
		return m_RenderType;
	}
	int		GetAttack(void)
	{
		return m_iAttack;
	}
public:
	void SetRenderType(eRenderType Type)
	{
		m_RenderType = Type;
	}
	void   SetNormInfo(INFO info)
	{
		m_tInfo = info;
	}
public:
	static D3DXVECTOR3 m_vScroll;

public:
	virtual HRESULT	Initialize(void)PURE;
	virtual int		Update(void)PURE;
	virtual void	Render(void)PURE;
	virtual void	Release(void)PURE;

public:
	void SetPos(const D3DXVECTOR3& _vPos)
	{
		m_tInfo.vPos = _vPos;
	}

	void SetPos(const float& fX, const float& fY)
	{
		m_tInfo.vPos.x = fX;
		m_tInfo.vPos.y = fY;
		m_tInfo.vPos.z = 0.f;
	}

public:
	CGameObject(void);
	virtual ~CGameObject(void);
};
