#pragma once
#include "EffectBridge.h"

class CPlayer;
class CBoss;
class CMonster;
class CEffectBuffer :
	public CEffectBridge
{
public:
	static bool	g_bAllSkillCheck;
private:
	float m_fRotateAngle;
	float m_fTime;
	bool m_bOnceCheck;
	float m_myTime;


private:
	int	 m_iPlayerAttack;
	int	 m_iMagicalDamage;
	int  m_iCriticalDamage;
	CPlayer*		m_pPlayer;

private:
	vector<CMonster*>* pMonvector;
	vector<CMonster*>* pMonBackvector;
	CMonster* pMonster;
	CBoss*	  pBoss;
private:
	void WorldMatrixCheck(INFO& rInfo);
	void FrameMove(void);

public:
	virtual HRESULT Initialize(eSkill SkillType);
	virtual int		Update(INFO& rInfo);
	virtual void	Render(void);
	virtual void	Release(void);

public:
	CEffectBuffer();
	virtual ~CEffectBuffer();
};

