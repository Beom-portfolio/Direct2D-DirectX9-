#pragma once
#include "GameObject.h"

class CMonHpBar;
class CPlayer;
class CMonster :
	public CGameObject
{
protected:
	UNIT_DATA		m_tData;

protected:
	vector<CMonster*>   m_vecMon;
	vector<CMonster*>   m_vecMon_Back;
	const TEX_INFO*		m_pMonTex;
	eMonsterState		m_MonState;
	//플레이어
	CGameObject*		m_pPlayer;
	//UI
	CMonHpBar*			m_pMonHpBar;

protected:
	FRAME				m_tFrame;
	wstring				m_wstrStateKey;
	eDir                m_Dir;
	float				m_RightCheck;

protected:
	FRAME				m_TargetFrame;
	bool				m_TargetCheck;
	bool				m_MonsterHitCheck;
	bool				m_MonsterAttackCheck;
public:
	bool				m_bPlayerHitCheck;

public:
	virtual HRESULT	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(void);
	virtual void	Release(void);

public:
	void YSorting(void);
	void RenderBack(void);
public:
	vector<CMonster*>*	GetMonsterVec(void)
	{
		return &m_vecMon;
	}
	vector<CMonster*>*	GetMonsterBackVec(void)
	{
		return &m_vecMon_Back;
	}
	bool GetTargetCheck(void)
	{
		return m_TargetCheck;
	}
	bool GetMonsterHitCheck(void)
	{
		return m_MonsterHitCheck;
	}
	bool GetPlayerHitCheck(void)
	{
		return m_bPlayerHitCheck;
	}
	eMonsterState GetMonsterState(void)
	{
		return m_MonState;
	}

public:
	void setTargetCheck(bool Check)
	{
		m_TargetCheck = Check;
	}
	void SetMonsterHitCheck(bool Check)
	{
		m_MonsterHitCheck = Check;
	}
	void SetPlayerHitCheck(bool Check)
	{
	    m_bPlayerHitCheck = Check;
	}

public:
	void LoadMonster(void);
	CMonster* MonsterType(BYTE Type);

public:
	CMonster();
	virtual ~CMonster();
};

