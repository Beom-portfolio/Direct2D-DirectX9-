#include "stdafx.h"
#include "ToolObject.h"
#include "Device.h"
#include "TextureMgr.h"
#include "Tool76View.h"
#include "MainFrm.h"
#include "Mouse.h"

bool CToolObject::ObjActiveCheck = false;

HRESULT CToolObject::Initialize(void)
{
	Release();

	D3DXVECTOR3 MousePos = CMouse::GetMousePos();

	m_pObj = new OBJINFO;

	m_pObj->vPos = MousePos;
	m_pObj->vSize = D3DXVECTOR3(1.f, 1.f, 1.f);

	m_pObj->byDrawID = 0;

	//미니 사이즈
	m_MiniSize.fXSize = 0.2f;
	m_MiniSize.fYSize = 0.2f;
	m_MiniSize.fZSize = 0.2f;

	return S_OK;
}

int CToolObject::Update(void)
{
	D3DXVECTOR3 MousePos = CMouse::GetMousePos();

	m_pObj->vPos = MousePos;

	return 0;
}

void CToolObject::Render(void)
{
	D3DXMATRIX matTrans;

	if(ObjActiveCheck == true)
	{

		const TEX_INFO* pTileTex =
			CTextureMgr::GetInstance()->GetTexture(L"Tree",
				L"Object",
				m_pObj->byDrawID);

		D3DXMatrixTranslation(&matTrans
			, m_pObj->vPos.x //- m_pMainView->GetScrollPos(0)	//0 : x
			, m_pObj->vPos.y// - m_pMainView->GetScrollPos(1)	//1 : y
			, 0.f);

		CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

		float fCenterX = pTileTex->ImageInfo.Width / 2.f;
		float fCenterY = pTileTex->ImageInfo.Height / 1.25f;

		CDevice::GetInstance()->GetSprite()->Draw(
			pTileTex->pTexture,
			NULL,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f),
			NULL,
			D3DCOLOR_ARGB(150, 255, 255, 255)
		);
	}

	if (!(m_vecObjInfo.empty()))
	{
		vector<OBJINFO*>::iterator iter = m_vecObjInfo.begin();
		vector<OBJINFO*>::iterator iter_end = m_vecObjInfo.end();

		for (vector<OBJINFO*>::iterator i = iter; i != iter_end; ++i)
		{

			const TEX_INFO* pTileTex =
				CTextureMgr::GetInstance()->GetTexture(L"Tree",
					L"Object",
					(*i)->byDrawID);

			D3DXMatrixTranslation(&matTrans
				, (*i)->vPos.x - m_pMainView->GetScrollPos(0)	//0 : x
				, (*i)->vPos.y - m_pMainView->GetScrollPos(1)	//1 : y
				, 0.f);

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			float fCenterX = pTileTex->ImageInfo.Width / 2.f;
			float fCenterY = pTileTex->ImageInfo.Height / 1.25f;

			CDevice::GetInstance()->GetSprite()->Draw(
				pTileTex->pTexture,
				NULL,
				&D3DXVECTOR3(fCenterX, fCenterY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255)
			);
		}
	}
}

void CToolObject::Release(void)
{
	for (size_t i = 0; i < m_vecObjInfo.size(); ++i)
	{
		safe_delete(m_vecObjInfo[i]);
	}
	m_vecObjInfo.clear();
}

void CToolObject::MiniMapRender(void)
{
	D3DXMATRIX matWorld;
	D3DXMATRIX matTrans;
	D3DXMATRIX matScale;

	if (!(m_vecObjInfo.empty()))
	{
		vector<OBJINFO*>::iterator iter = m_vecObjInfo.begin();
		vector<OBJINFO*>::iterator iter_end = m_vecObjInfo.end();

		for (vector<OBJINFO*>::iterator i = iter; i != iter_end; ++i)
		{

			const TEX_INFO* pTileTex =
				CTextureMgr::GetInstance()->GetTexture(L"Tree",
					L"Object",
					(*i)->byDrawID);

			D3DXMatrixScaling(&matScale, m_MiniSize.fXSize, m_MiniSize.fYSize, m_MiniSize.fZSize);

			D3DXMatrixTranslation(&matTrans
				, (*i)->vPos.x * m_MiniSize.fXSize	//0 : x
				, (*i)->vPos.y * m_MiniSize.fYSize	//1 : y
				, 0.f);

			matWorld = matScale * matTrans;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

			float fCenterX = pTileTex->ImageInfo.Width / 2.f;
			float fCenterY = pTileTex->ImageInfo.Height / 1.25f;

			CDevice::GetInstance()->GetSprite()->Draw(
				pTileTex->pTexture,
				NULL,
				&D3DXVECTOR3(fCenterX, fCenterY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255)
			);
		}
	}
}

void CToolObject::ClickLButton(D3DXVECTOR3& vMousePos)
{
	OBJINFO* Temp = new OBJINFO;

	Temp->vPos = vMousePos;
	Temp->vSize = D3DXVECTOR3(1.f, 1.f, 1.f);
	Temp->byDrawID = m_pObj->byDrawID;

	m_vecObjInfo.push_back(Temp);
}

CToolObject::CToolObject()
{
}


CToolObject::~CToolObject()
{
	Release();
}
