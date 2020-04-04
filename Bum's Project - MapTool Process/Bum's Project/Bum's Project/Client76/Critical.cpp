#include "stdafx.h"
#include "Critical.h"
#include "Device.h"
#include "TextureMgr.h"
#include "TimeMgr.h"



HRESULT CCritical::Initialize(void)
{
	m_RenderType = RENDER_EFFECT;

	m_tsize= D3DXVECTOR3(1.f, 1.f, 0.f);

	m_wstrObjKey = L"Effect";
	m_wstrStateKey = L"Critical";
	m_tFrame = FRAME(0.f, 0.f, 0.f);
	m_Up = 0.f;
	m_Alpa = 255;

	m_fForce = 1.f;

	m_big = false;
	m_small = false;

	return S_OK;
}

int CCritical::Update(void)
{
	return 0;
}


int CCritical::Update(D3DXVECTOR3 Pos)
{
	if (m_Up < 100.f)
	{
		if (m_big == false)
		{
			if (m_tsize.y < 2.5f)
			{
				m_tsize.x += 0.25f;
				m_tsize.y += 0.25f;
			}
			else
			{
				m_big = true;
			}
		}
		else if (m_big == true)
		{
			if (m_tsize.y > 1.2f)
			{
				m_tsize.x -= 0.10f;
				m_tsize.y -= 0.10f;
			}
			else
			{
				m_small = true;
			}
		}


		if (m_small == true)
		{
			m_Up += m_fForce * 0.5f;
		}

		if (m_Up > 60.f)
		{
			m_Alpa -= 2;
		}

		m_tInfo.vPos = D3DXVECTOR3(Pos.x, (Pos.y - m_iBottom) - m_Up, Pos.z);

		D3DXMATRIX matTrans, matScale;

		D3DXMatrixScaling(&matScale, m_tsize.x, m_tsize.y, 0.f);
		D3DXMatrixTranslation(&matTrans,
			m_tInfo.vPos.x + m_vScroll.x + 10.f,
			m_tInfo.vPos.y + m_vScroll.y + 30.f,
			0.f);

		m_tInfo.matWorld = matScale * matTrans;

		m_fTime += GET_TIME;

		return 1;
	}
	else if (m_Up > 140.f)
	{
		m_fTime += GET_TIME;

		return 0;
	}


	/*if (m_big == false)
	{
		if (m_tsize.y < 2.5f)
		{
			m_tsize.x += 0.25f;
			m_tsize.y += 0.25f;
		}
		else
		{
			m_big = true;
		}
	}
	else if (m_big == true)
	{
		if (m_tsize.y > 1.2f)
		{
			m_tsize.x -= 0.10f;
			m_tsize.y -= 0.10f;
		}
		else
		{
			m_small = true;
		}
	}


	m_tInfo.vPos = D3DXVECTOR3(Pos.x, (Pos.y - m_iBottom) - m_Up, Pos.z);

	D3DXMATRIX matTrans, matScale;

	D3DXMatrixScaling(&matScale, m_tsize.x, m_tsize.y, 0.f);
	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x + m_vScroll.x + 10.f,
		m_tInfo.vPos.y + m_vScroll.y + 30.f,
		0.f);

	m_tInfo.matWorld = matScale * matTrans;

	if (m_small == true)
	{
		m_fTime += GET_TIME;

		return 0;
	}

	m_fTime += GET_TIME;

	return 1;*/

	

	return 0;
}

void CCritical::Render(void)
{
	const TEX_INFO* pCriTexture = CTextureMgr::GetInstance()->
		GetTexture(m_wstrObjKey.c_str(),
			m_wstrStateKey.c_str(),
			static_cast<int>(m_tFrame.fIndex)
		);

	if (pCriTexture == NULL)
	{
		ERROR_MSG(L"크리 이펙트 이미지 X");
		return;
	}

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	float fX = CENTER_POS(pCriTexture->ImageInfo.Width);
	float fY = CENTER_POS(pCriTexture->ImageInfo.Height);

	CDevice::GetInstance()->GetSprite()->Draw(
		pCriTexture->pTexture,
		NULL,
		&D3DXVECTOR3(fX, fY, 0.f),
		NULL,
		D3DCOLOR_ARGB(m_Alpa, 255, 255, 255));
}

void CCritical::Release(void)
{
}

CCritical::CCritical()
{
}

CCritical::CCritical(D3DXVECTOR3 Pos, int Bottom)
{
	m_iBottom = Bottom;
	m_tInfo.vPos = Pos;
}


CCritical::~CCritical()
{
}
