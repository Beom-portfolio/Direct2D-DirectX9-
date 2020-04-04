#include "stdafx.h"
#include "ShakeMgr.h"
#include "GameObject.h"
#include "TimeMgr.h"

IMPLEMENT_SINGLETON(CShakeMgr);

void CShakeMgr::Progress(void)
{
	if (m_bActive)
	{
		if (m_eShakeType == SHAKE_SINGLE)
		{
			if (m_fDividePower < m_fPower && m_bBack == false)
			{
				m_vecScroll.x += m_vecDir.x * m_fPower * GET_TIME * 30;
				m_vecScroll.y += m_vecDir.y * m_fPower * GET_TIME * 30;
				m_fDividePower += m_fPower * GET_TIME * 30;

				if (m_fDividePower >= m_fPower)
					m_bBack = true;
			}
			else if (m_fDividePower > 0)
			{
				m_vecScroll.x -= m_vecDir.x * m_fPower * GET_TIME * 30;
				m_vecScroll.y -= m_vecDir.y * m_fPower * GET_TIME * 30;
				m_fDividePower -= m_fPower * GET_TIME * 30;
			}
			else
			{
				m_bBack = false;
				m_bActive = false;
				m_eShakeType = SHAKE_NON;
			}
		}
		else if (m_eShakeType == SHAKE_RANDOM)
		{
			if (m_bActive)
			{
				if (m_fTime < 0)
				{
					D3DXVECTOR3 vecDir(1.f, 0.f, 0.f);

					if (m_bBack)
					{
						m_vecScroll.x += m_vecDir.x * m_fPower;
						m_vecScroll.y += m_vecDir.y * m_fPower;

						m_bBack = false;
						--m_iRand;
					}
					else
					{
						m_fAngle = S_CAST(float, rand() % 360);
						D3DXMatrixRotationZ(&m_matRotZ, D3DXToRadian(m_fAngle));
						D3DXVec3TransformNormal(&m_vecDir, &vecDir, &m_matRotZ);

						m_vecScroll.x -= m_vecDir.x * m_fPower;
						m_vecScroll.y -= m_vecDir.y * m_fPower;

						m_bBack = true;
					}

					m_fTime = 0.02f;
				}

				m_fTime -= GET_TIME;

				if (m_iRand == 0)
				{
					m_eShakeType = SHAKE_NON;
					m_bActive = false;
				}
			}
		}
	}
}

void CShakeMgr::SetShake(eShakeType eShakeType, float fPower, D3DXVECTOR3 vecDir)
{
	if (m_eShakeType == SHAKE_SINGLE)
	{
		if (eShakeType == SHAKE_RANDOM)
		{
			m_bBack = false;
			m_bActive = false;
			m_eShakeType = SHAKE_NON;


			SetShake(eShakeType, fPower, vecDir);
		}
		else
		{
			m_eShakeType = eShakeType;
			m_vecDir = vecDir;
			m_fPower = fPower;
			m_bActive = true;
			m_iRand = (rand() % 3) + 5;
		}
	}
	else if (m_eShakeType == SHAKE_RANDOM)
	{
		if (m_eShakeType == eShakeType)
			m_iRand = (rand() % 3) + 5;
	}
	else
	{
		m_eShakeType = eShakeType;
		m_vecDir = vecDir;
		m_fPower = fPower;
		m_bActive = true;
		m_iRand = (rand() % 3) + 5;
	}
}

 
CShakeMgr::CShakeMgr()
	:m_vecScroll(CGameObject::m_vScroll), m_eShakeType(SHAKE_NON),
	m_bActive(false), m_vecDir(D3DXVECTOR3()), m_fPower(0.f),
	m_fDividePower(0.f), m_bBack(false), m_fTime(0.02f)
{
}


CShakeMgr::~CShakeMgr()
{
}
