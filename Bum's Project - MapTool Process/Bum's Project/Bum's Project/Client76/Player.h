#pragma once
#include "gameobject.h"

#include "Include.h"

class CAStar;
class CPlayer :
	public CGameObject
{
private:
	UNIT_DATA    m_tData;

private:
	CAStar*		 AS_Test;
	CGameObject* Player_Weapon;

public:
	static bool g_bCriCheck;
	static int	g_iPlayerMoney;
	static bool g_WalkCheck;
	static int	g_iLevel;
	static int  g_iAtt;
	static int  g_iDef;
	static int  g_iHp;
	static int  g_iMp;
	static int  g_iMaxHp;
	static int  g_iMaxMp;
private:
	wstring m_wstrStateKey;
	FRAME	m_tFrame;
	float   m_RightCheck;
	ePlayerState m_eState;
	bool    m_bAttachCheck;
	bool    m_bSkillCheck;
	bool	m_bRunCheck;
	bool    m_bAStarCheck;
	bool    m_bChangeCheck;
	bool    m_bYSortCheck;
	bool    m_MouseCollCheck;
	bool	m_MonsterMouseCheck;
	bool    m_MouseCollBossCheck;
	bool	m_BossMouseCheck;
	bool	m_bLevelUpCheck;
private:
	int		m_iMagicalDamage;
	int		m_iMonsterDamage;
	int		m_iBossDamage;
	int		m_iCriticalDamage;
	float	 m_fHoldTerm;
private:
	RECT m_testrc;
	FRAME  m_tLevelUp;
	FRAME  m_tLevelUp2;
	INFO   m_tLevelUpInfo;
public:
	void	SetPlayerMagicalDamage(int PlayerMagicDMG)
	{
		m_iMagicalDamage = PlayerMagicDMG;
	}
	void	SetPlayerCriticalDamage(int PlayerCriticalDMG)
	{
		m_iCriticalDamage = PlayerCriticalDMG;
	}
	void	SetMonsterDamage(int MonsterDMG)
	{
		m_iMonsterDamage = MonsterDMG;
	}
	void	SetBossDamage(int BossDMG)
	{
		m_iBossDamage = BossDMG;
	}
public:
	ePlayerState GetPlayerState(void)
	{
		return m_eState;
	}
	int		GetPlayerMagicalDamage(void)
	{
		return m_iMagicalDamage;
	}
	int		GetPlayerCriticalDamage(void)
	{
		return m_iCriticalDamage;
	}
	int		GetPlayerAttackDamage(void)
	{
		return m_iAttack;
	}
	UNIT_DATA* GetUnitData(void)
	{
		return &m_tData;
	}
public:
	virtual HRESULT	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(void);
	virtual void	Release(void);

private:
	void RenderPlayer(void);
	void RenderLevelUp(void);
private:
	void PlayerState(void);
	void PlayerDir(int MoveIndex);
	void MyMatrixCheck(void);
	void KeyCheck(void);
	void AStarMove(void);
	void MyFrameCheck(void);
	void PlayerScrollCheck(void);
	void PlayerDamage(int	Damage);



public:
	CPlayer(void);
	virtual ~CPlayer(void);
};
