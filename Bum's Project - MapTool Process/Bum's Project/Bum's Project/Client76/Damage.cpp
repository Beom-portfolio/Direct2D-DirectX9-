#include "stdafx.h"
#include "Damage.h"
#include "Device.h"
#include "TextureMgr.h"
#include "TimeMgr.h"

HRESULT CDamage::Initialize(void)
{
	m_RenderType = RENDER_EFFECT;

	m_wstrObjKey = L"Font";
	m_wstrStateKey = L"DmgFont";
	m_tFrame = FRAME(0.f, 10.f, 10.f);
	m_iFar = 22;
	m_X = 0.f;
	m_Y = 0.f;

	m_fTime = 0.f;
	m_Alpa = 255;
	m_tsize = D3DXVECTOR3(1.f, 1.f, 0.f);

	for (int i = 1;;)
	{
		if (float(m_iDamage / i) < 1.f)
		{
			m_iNum = i;
			break;
		}
		else
		{
			i *= 10;
		}
	}

	m_big = false;
	m_small = false;

	m_iFirstPos = 0;
	return S_OK;
}

int CDamage::Update(void)
{
	return 0;
}

int CDamage::Update(D3DXVECTOR3 Pos)
{
	//
	m_X = 40.f * cos(D3DXToRadian(45)) * m_fTime;
	m_Y = 10.f * sin(D3DXToRadian(45)) - 9.8f * m_fTime * m_fTime / 2;

	//처음 위치
	if (m_iDamage < 10)
	{
		m_iFirstPos = 0;
	}
	else if (m_iDamage < 100)
	{
		m_iFirstPos = 8;
	}
	else if (m_iDamage < 1000)
	{
		m_iFirstPos = 16;
	}
	else if (m_iDamage < 10000)
	{
		m_iFirstPos = 24;
	}
	else
	{
		m_iFirstPos = 32;
	}

	if (m_X < 100.f)
	{
		if (m_big == false)
		{
			if (m_tsize.y < 2.2f)
			{
				m_tsize.x +=  0.25f;
				m_tsize.y +=  0.25f;
			}
			else
			{
				m_big = true;
			}
		}
		else if (m_big == true)
		{
			if (m_tsize.y > 1.f)
			{
				m_tsize.x -=  0.05f;
				m_tsize.y -=  0.05f;
			}
			else
			{
				m_small = true;
			}
		}


		if (m_X > 40.f)
		{
			m_Alpa -= 2;
		}

		m_tInfo.vPos = D3DXVECTOR3(Pos.x + m_X, (Pos.y - m_iBottom) - m_Y, Pos.z);

		D3DXMATRIX matTrans, matScale;

		D3DXMatrixScaling(&matScale, m_tsize.x, m_tsize.y, 0.f);
		D3DXMatrixTranslation(&matTrans,
			m_tInfo.vPos.x + m_vScroll.x + m_iFirstPos,
			m_tInfo.vPos.y + m_vScroll.y + 20.f,
			0.f);

		m_tInfo.matWorld = matScale * matTrans;

		m_fTime += GET_TIME * 4.f;

		return 1;
	}
	else if (m_X > 200.f)
	{
		m_fTime += GET_TIME;

		return 0;
	}

	return 0;
}

void CDamage::Render(void)
{
	int i = 10;
	int iNum = 0;
	int iBackNum = 0;

	while (i <= m_iNum)
	{
		int Index;

		if (i > 10)
		{
			Index = (m_iDamage % i) / (i / 10);
			iBackNum += Index * (i / 10);
		}
		else
		{
			Index = m_iDamage % i;
			iBackNum += Index * (i / 10);
		}
		

		const TEX_INFO* pDmgTexture = CTextureMgr::GetInstance()->
			GetTexture(m_wstrObjKey.c_str(),
					   m_wstrStateKey.c_str(),
					   Index
					   );

		if (pDmgTexture == NULL)
		{
			ERROR_MSG(L"폰트 이미지 X");
			return;
		}

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		float fX = CENTER_POS(pDmgTexture->ImageInfo.Width);
		float fY = CENTER_POS(pDmgTexture->ImageInfo.Height);

		CDevice::GetInstance()->GetSprite()->Draw(
			pDmgTexture->pTexture,
			NULL,
			&D3DXVECTOR3(fX + (m_iFar * iNum), fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(m_Alpa, 255, 255, 255));

		++iNum;
		i *= 10;
	}
}

void CDamage::Release(void)
{
}

CDamage::CDamage()
{
}

CDamage::CDamage(D3DXVECTOR3 Pos, float Force, int Damage, int Bottom)
{
	m_iBottom = Bottom;
	m_tInfo.vPos = Pos;
	m_tInfo.vPos.y = Pos.y - m_iBottom;
	m_fForce = 1.f;
	m_iDamage = Damage;
}


CDamage::~CDamage()
{
}
