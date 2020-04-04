#pragma once
#include "GameObject.h"

class CMonHpBar;
class CBossBullet;
class CAStar;
class CMonster;
class CJelly;
class CBoss :
	public CGameObject
{
private:
	CMonHpBar*	m_pBossHpBar;
	CAStar*		AS_Test;
	vector<CBossBullet*> m_vecBullet;
private:
	CGameObject* m_pPlayer;
	wstring  m_wstrStateKey;
	FRAME    m_tFrame;
	FRAME	 m_TargetFrame;
	FRAME	 m_ImpactFrame;
	FRAME    m_ShieldFrame;
	FRAME    m_HoldingFrame;
	INFO	 m_tHoldInfo;
	float    m_RightCheck;
	bool     m_TargetCheck;	
	bool	 m_MonsterHitCheck;
	bool	 m_bCollCheck;
	bool     m_bBackRenderCheck;
	bool	 m_MonsterAttackCheck;
	bool	 m_bImpactCheck;
	bool     m_bShieldCheck;
	bool     m_bHoldingCheck;
	int		 m_iShieldCount;
	int		 m_iHoldingCount;
	float	 m_fWalkSpeed;
	float	 m_fBossTerm;
private:
	float	 m_tJellyPattern;
	float	 m_tShieldPattern;
	float    m_tHoldingPattern;
public:
	bool	 m_bPlayerHitCheck;
private:
	eCollisionDir m_MonColDir;
	eMonsterState m_MonState;
	bool    m_bRunCheck;
	bool    m_bAttachCheck;
	bool    m_bSkillCheck;
	bool    m_bAStarCheck;
	bool    m_bChangeCheck;
private:
	bool    m_PhaseOne;
	bool	m_PhaseTwo;
	bool	m_PhaseThree;
	vector<CMonster*>  m_vecJelly;
	vector<CMonster*>  m_vecBackJelly;
private:
	int		m_iHp;
	int		m_iMaxHp;
	float	m_OriginPosY;
	float	m_fAttackTerm;
public:
	RECT*   GetMonsterRect(void)
	{
		return &m_rc;
	}
	bool	GetTargetCheck(void)
	{
		return m_TargetCheck;
	}
	bool GetMonsterHitCheck(void)
	{
		return m_MonsterHitCheck;
	}
	bool GetBackRenderCheck(void)
	{
		return m_bBackRenderCheck;
	}
	float GetBossRightCheck(void)
	{
		return m_RightCheck;
	}
	bool GetPlayerHitCheck(void)
	{
		return m_bPlayerHitCheck;
	}
	vector<CBossBullet*>* GetBossBullet(void)
	{
		return &m_vecBullet;
	}
	vector<CMonster*>*	  GetJelly(void)
	{
		return &m_vecJelly;
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
	virtual HRESULT	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(void);
	virtual void	Release(void);

private:
	void AI(void);
	void MonsterState(void);
	void MonsterDir(int MoveIndex);
	void MyMatrixCheck(void);
	void AStarMove(void);
	void MyFrameCheck(void);
	void MonsterDamage(void);

private:
	void YSorting(void);
	void YSortJelly(void);
public:
	void BackRender(void);
public:
	CBoss();
	virtual ~CBoss();
};

