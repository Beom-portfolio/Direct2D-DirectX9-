#include "stdafx.h"
#include "Monster.h"
#include "Device.h"
#include "TextureMgr.h"
#include "Tool76View.h"
#include "MainFrm.h"
#include "Mouse.h"

bool Monster::MonActiveCheck = false;

HRESULT Monster::Initialize(void)
{
	Release();

	D3DXVECTOR3 MousePos = CMouse::GetMousePos();

	m_pMon = new MONINFO;

	m_pMon->vPos = MousePos;
	m_pMon->vSize = D3DXVECTOR3(1.f, 1.f, 1.f);

	m_pMon->byDrawID = 0;

	//미니 사이즈
	m_MiniSize.fXSize = 0.2f;
	m_MiniSize.fYSize = 0.2f;
	m_MiniSize.fZSize = 0.2f;

	return S_OK;
}

int Monster::Update(void)
{
	D3DXVECTOR3 MousePos = CMouse::GetMousePos();

	m_pMon->vPos = MousePos;

	return 0;
}

void Monster::Render(void)
{
	D3DXMATRIX matTrans;

	if (MonActiveCheck == true)
	{

		const TEX_INFO* pMonTex =
			CTextureMgr::GetInstance()->GetTexture(L"Monster",
				L"Monster",
				m_pMon->byDrawID);

		D3DXMatrixTranslation(&matTrans
			, m_pMon->vPos.x //- m_pMainView->GetScrollPos(0)	//0 : x
			, m_pMon->vPos.y// - m_pMainView->GetScrollPos(1)	//1 : y
			, 0.f);

		CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

		float fCenterX = pMonTex->ImageInfo.Width / 2.f;
		float fCenterY = pMonTex->ImageInfo.Height / 1.25f;

		CDevice::GetInstance()->GetSprite()->Draw(
			pMonTex->pTexture,
			NULL,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f),
			NULL,
			D3DCOLOR_ARGB(150, 255, 255, 255)
		);
	}

	if (!(m_vecMonInfo.empty()))
	{
		vector<MONINFO*>::iterator iter = m_vecMonInfo.begin();
		vector<MONINFO*>::iterator iter_end = m_vecMonInfo.end();

		for (vector<MONINFO*>::iterator i = iter; i != iter_end; ++i)
		{

			const TEX_INFO* pMonTex =
				CTextureMgr::GetInstance()->GetTexture(L"Monster",
					L"Monster",
					(*i)->byDrawID);

			D3DXMatrixTranslation(&matTrans
				, (*i)->vPos.x - m_pMainView->GetScrollPos(0)	//0 : x
				, (*i)->vPos.y - m_pMainView->GetScrollPos(1)	//1 : y
				, 0.f);

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			float fCenterX = pMonTex->ImageInfo.Width / 2.f;
			float fCenterY = pMonTex->ImageInfo.Height / 1.25f;

			CDevice::GetInstance()->GetSprite()->Draw(
				pMonTex->pTexture,
				NULL,
				&D3DXVECTOR3(fCenterX, fCenterY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255)
			);
		}
	}
}

void Monster::Release(void)
{
	for (size_t i = 0; i < m_vecMonInfo.size(); ++i)
	{
		safe_delete(m_vecMonInfo[i]);
	}
	m_vecMonInfo.clear();
}

void Monster::MiniMapRender(void)
{
	D3DXMATRIX matWorld;
	D3DXMATRIX matTrans;
	D3DXMATRIX matScale;

	if (!(m_vecMonInfo.empty()))
	{
		vector<MONINFO*>::iterator iter = m_vecMonInfo.begin();
		vector<MONINFO*>::iterator iter_end = m_vecMonInfo.end();

		for (vector<MONINFO*>::iterator i = iter; i != iter_end; ++i)
		{

			const TEX_INFO* pMonTex =
				CTextureMgr::GetInstance()->GetTexture(L"Monster",
					L"Monster",
					(*i)->byDrawID);

			D3DXMatrixScaling(&matScale, m_MiniSize.fXSize, m_MiniSize.fYSize, m_MiniSize.fZSize);

			D3DXMatrixTranslation(&matTrans
				, (*i)->vPos.x * m_MiniSize.fXSize	//0 : x
				, (*i)->vPos.y * m_MiniSize.fYSize	//1 : y
				, 0.f);

			matWorld = matScale * matTrans;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

			float fCenterX = pMonTex->ImageInfo.Width / 2.f;
			float fCenterY = pMonTex->ImageInfo.Height / 1.25f;

			CDevice::GetInstance()->GetSprite()->Draw(
				pMonTex->pTexture,
				NULL,
				&D3DXVECTOR3(fCenterX, fCenterY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255)
			);
		}
	}
}

void Monster::ClickLButton(D3DXVECTOR3 & vMousePos)
{
	MONINFO* Temp = new MONINFO;

	Temp->vPos = vMousePos;
	Temp->vSize = D3DXVECTOR3(1.f, 1.f, 1.f);
	Temp->byDrawID = m_pMon->byDrawID;

	m_vecMonInfo.push_back(Temp);
}

Monster::Monster()
{
}


Monster::~Monster()
{
}
