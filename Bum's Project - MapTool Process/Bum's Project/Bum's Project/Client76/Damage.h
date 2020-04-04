#pragma once
#include "GameObject.h"
#include "UserInterface.h"

class CDamage :
	public CUserInterface
{
//Å©±â
private:
	D3DXVECTOR3 m_tsize;
	float	    m_fForce;
	float		m_X;
	float		m_Y;
	int			m_Alpa;
private:
	FRAME   m_tFrame;
	int		m_iDamage;
	int     m_iBottom;
	int		m_iFar;
	int		m_iNum;
	int		m_iFirstPos;
private:
	bool    m_big;
	bool    m_small;

public:
	virtual HRESULT	Initialize(void);
	virtual int		Update(void);
	virtual void	Render(void);
	virtual void	Release(void);

public:
	int Update(D3DXVECTOR3 Pos);

	
public:
	CDamage();
	CDamage(D3DXVECTOR3 Pos, float Force, int Damage, int Bottom);
	virtual ~CDamage();
};

