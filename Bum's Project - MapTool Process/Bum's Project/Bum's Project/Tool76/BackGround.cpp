#include "StdAfx.h"
#include "BackGround.h"
#include "Device.h"
#include "TextureMgr.h"
#include "tool76view.h"



void CBackGround::SetStageTypeFromLoad(int	iBackType)
{
	if (iBackType == 0)
		m_Back_Type = STAGE_FIELD;
	else if (iBackType == 1)
		m_Back_Type = STAGE_DUNGEON;
	else if (iBackType == 2)
		m_Back_Type = STAGE_BOSS;
	else if (iBackType == 3)
		m_Back_Type = STAGE_HOUSE;
	else if (iBackType == 4)
		m_Back_Type = STAGE_SMITHY;
	else if (iBackType == 5)
		m_Back_Type = STAGE_SMITHY2;
	else if (iBackType == 6)
		m_Back_Type = STAGE_STORE;
	else if (iBackType == 7)
		m_Back_Type = STAGE_TOWN;
	else if (iBackType == 8)
		m_Back_Type = STAGE_TOWN2;
}

HRESULT CBackGround::Initialize(void)
{
	for(int i = STAGE_FIELD; i <= STAGE_TOWN2; ++i)
	{	
		BACK* pBack = new BACK;

		float fX = 0.f;
		float fY = 0.f;

		pBack->vPos = D3DXVECTOR3(fX, fY, 0.f);
		pBack->StageType = static_cast<eStageType>(i);

		float fCX = 0.f;
		float fCY = 0.f;

		switch(pBack->StageType)
		{
		case STAGE_FIELD:
			fCX = 3268.f;
			fCY = 1712.f;
			break;
		case STAGE_DUNGEON:
			fCX = 3418.f;
			fCY = 1730.f;
			break;
		case STAGE_BOSS:
			fCX =2668.f;
			fCY =1328.f;
			break;
		case STAGE_HOUSE:
			fCX =1174.f;
			fCY =882.f;
			break;
		case STAGE_SMITHY:
			fCX =1181.f;
			fCY =775.f;
			break;
		case STAGE_SMITHY2:
			fCX =1394.f;
			fCY =868.f;
			break;
		case STAGE_STORE:
			fCX =1277.f;
			fCY =991.f;
			break;
		case STAGE_TOWN:
			fCX =3502.f;
			fCY =2048.f;
			break;
		case STAGE_TOWN2:
			fCX =1600.f;
			fCY =1200.f;
			break;
		}

		pBack->vSize = D3DXVECTOR3((fCX / 2.f), (fCY / 2.f), 0.f);

		m_vecBack.push_back(pBack);
	}
	
	m_Back_Type = STAGE_FIELD;

	return S_OK;
}

int CBackGround::Update(void)
{
	return 0;
}

void CBackGround::Render(void)
{
	D3DXMATRIX matTrans;

	szBackType = L"";

	for(size_t i = 0; i < m_vecBack.size(); ++i)
	{
		if((m_vecBack[i]->StageType) ==  m_Back_Type)
		{
			switch(m_vecBack[i]->StageType)
			{
			case STAGE_FIELD:
				szBackType = L"Field";
				iBackType = 0;
				break;
			case STAGE_DUNGEON:
				szBackType = L"Dungeon";
				iBackType = 1;
				break;
			case STAGE_BOSS:
				szBackType = L"Boss";
				iBackType = 2;
				break;
			case STAGE_HOUSE:
				szBackType = L"House";
				iBackType = 3;
				break;
			case STAGE_SMITHY:
				szBackType = L"Smithy";
				iBackType = 4;
				break;
			case STAGE_SMITHY2:
				szBackType = L"Smithy2";
				iBackType = 5;
				break;
			case STAGE_STORE:
				szBackType = L"Store";
				iBackType = 6;
				break;
			case STAGE_TOWN:
				szBackType = L"Town";
				iBackType = 7;
				break;
			case STAGE_TOWN2:
				szBackType = L"Town2";
				iBackType = 8;
				break;
			}


			const TEX_INFO* pStageTex = 
				CTextureMgr::GetInstance()->GetTexture(szBackType);

			D3DXMatrixTranslation(&matTrans
				, m_vecBack[i]->vPos.x - m_pMainView->GetScrollPos(0)	//0 : x
				, m_vecBack[i]->vPos.y - m_pMainView->GetScrollPos(1)	//1 : y
				, 0.f);


			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(
				pStageTex->pTexture,
				NULL, 
				&D3DXVECTOR3(0.f
				, 0.f
				, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255)
				);

			return;
		}
	}
}

void CBackGround::Release(void)
{
	for(size_t i = 0; i < m_vecBack.size(); ++i)
	{
		safe_delete(m_vecBack[i]);
	}
	m_vecBack.clear();
}

void CBackGround::MiniMapRender(void)
{
	D3DXMATRIX matTrans, matScale, matWorld;

	TCHAR	*szBackType;


	for(size_t i = 0; i < m_vecBack.size(); ++i)
	{
		if((m_vecBack[i]->StageType) ==  m_Back_Type)
		{
			switch(m_vecBack[i]->StageType)
			{
			case STAGE_FIELD:
				szBackType = L"Field";
				break;
			case STAGE_DUNGEON:
				szBackType = L"Dungeon";
				break;
			case STAGE_BOSS:
				szBackType = L"Boss";
				break;
			case STAGE_HOUSE:
				szBackType = L"House";
				break;
			case STAGE_SMITHY:
				szBackType = L"Smithy";
				break;
			case STAGE_SMITHY2:
				szBackType = L"Smithy2";
				break;
			case STAGE_STORE:
				szBackType = L"Store";
				break;
			case STAGE_TOWN:
				szBackType = L"Town";
				break;
			case STAGE_TOWN2:
				szBackType = L"Town2";
				break;
			}

			const TEX_INFO* pStageTex = 
				CTextureMgr::GetInstance()->GetTexture(szBackType);

			D3DXMatrixScaling(&matScale, m_MiniSize.fXSize, m_MiniSize.fYSize, m_MiniSize.fZSize);

			D3DXMatrixTranslation(&matTrans
				, m_vecBack[i]->vPos.x * m_MiniSize.fXSize
				, m_vecBack[i]->vPos.y * m_MiniSize.fYSize
				, 0.f);

			matWorld = matScale * matTrans;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

			CDevice::GetInstance()->GetSprite()->Draw(
				pStageTex->pTexture,
				NULL, 
				&D3DXVECTOR3(0.f
				, 0.f
				, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255)
				);
		}
	}
}

CBackGround::CBackGround(void)
{
	//미니 사이즈
	m_MiniSize.fXSize = 0.2f;
	m_MiniSize.fYSize = 0.2f;
	m_MiniSize.fZSize = 0.2f;
}

CBackGround::~CBackGround(void)
{
	Release();
}
