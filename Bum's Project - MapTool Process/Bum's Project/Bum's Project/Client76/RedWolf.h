#pragma once
#include "Monster.h"

//블루 울프와는 다르게 맞았을시 경직없음

class CAStar;
class CRedWolf :
	public CMonster
{
private:
	CAStar* AS_Test;

private:
	bool	m_bCollCheck;
	eCollisionDir m_MonColDir;
	bool    m_bRunCheck;
	bool    m_bAttachCheck;
	bool    m_bSkillCheck;
	bool    m_bAStarCheck;
	bool    m_bChangeCheck;

public:
	RECT*   GetMonsterRect(void)
	{
		return &m_rc;
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

public:
	CRedWolf();
	virtual ~CRedWolf();
};

