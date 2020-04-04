#include "StdAfx.h"
#include "Tile.h"
#include "Device.h"
#include "TextureMgr.h"
#include "tool76view.h"
#include "MainFrm.h"

int CTile::GetTileIndex(const D3DXVECTOR3& vPos)
{
	//Ÿ�� �˻�
	for(size_t i = 0; i < m_vecTile.size(); ++i)
	{
		if(Picking(vPos, i) )
		{
			return i;
		}
	}

	return -1;
}

void CTile::TileChange(const D3DXVECTOR3& vMousePos
							 , const int& iDrawID)
{
	int iTileIndex = GetTileIndex(vMousePos);

	if(iTileIndex == -1)
		return;

	//�⺻ Ÿ��(���� ����)
	if (iDrawID == 0)
		m_vecTile[iTileIndex]->byOption = 0;

	//�浹 Ÿ�� �϶��� ���� ����.
	else if(iDrawID == 1)
		m_vecTile[iTileIndex]->byOption = 1;
	
	//��ŻŸ��
	else if (iDrawID == 2)
		m_vecTile[iTileIndex]->byOption = 2;

	//��Ÿ��
	else if (iDrawID == 3)
		m_vecTile[iTileIndex]->byOption = 3;

	//����������ŻŸ��
	else if (iDrawID == 4)
		m_vecTile[iTileIndex]->byOption = 4;

	m_vecTile[iTileIndex]->byDrawID = iDrawID;		//= iDrawID;
}

bool CTile::Picking(const D3DXVECTOR3& vMousePos,
						  const int& iIndex)
{
	//Ÿ���� ��ġ����
	D3DXVECTOR3 vPoint[4] = 
	{
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x,
		m_vecTile[iIndex]->vPos.y - TILECY / 2.f,
		0.f),

		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x + TILECX / 2.f,
		m_vecTile[iIndex]->vPos.y,
		0.f),

		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x,
		m_vecTile[iIndex]->vPos.y + TILECY / 2.f,
		0.f),

		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x - TILECX / 2.f,
		m_vecTile[iIndex]->vPos.y,
		0.f)
	};


	//������ �������� ���⺤�͸� ������.
	D3DXVECTOR3 vDirection[4] = 
	{
		vPoint[1] - vPoint[0],
		vPoint[2] - vPoint[1],
		vPoint[3] - vPoint[2],
		vPoint[0] - vPoint[3]
	};


	//�������͸� ����� ����.
	D3DXVECTOR3 vNormal[4] = 
	{
		D3DXVECTOR3(vDirection[0].y, 
		-vDirection[0].x,
		0.f),

		D3DXVECTOR3(vDirection[1].y, 
		-vDirection[1].x,
		0.f),

		D3DXVECTOR3(vDirection[2].y, 
		-vDirection[2].x,
		0.f),

		D3DXVECTOR3(vDirection[3].y, 
		-vDirection[3].x,
		0.f)
	};


	//�������ͷ� ����� ����.
	for(int i = 0; i < 4; ++i)
		D3DXVec3Normalize(&vNormal[i], &vNormal[i]);

	for(int i = 0; i < 4; ++i)
	{
		D3DXVECTOR3 vTemp = vMousePos - vPoint[i];

		D3DXVec3Normalize(&vTemp, &vTemp);

		float fDotResult = D3DXVec3Dot(&vTemp, &vNormal[i]);

		//������ ����� ����� Ÿ���� �ܺ��̰�.
		//				������ Ÿ���� �����̴�.

		if(fDotResult > 0.f)
			return false;
	}

	return true;
}

HRESULT CTile::Initialize(void)
{
	Release();

	for(int i = 0; i < m_xyCount.iYCount; ++i)	
	{
		for(int j = 0; j < m_xyCount.iXCount; ++j)
		{
			TILE* pTile = new TILE;

			float fX = j * TILECX + ((i % 2) * (TILECX / 2.f));
			float fY = i * (TILECY * 0.5f);

			pTile->vPos = D3DXVECTOR3(fX, fY, 0.f);
			pTile->vSize = D3DXVECTOR3( (float)TILECX, (float)TILECY, 0.f );

			pTile->byOption = 0;
			pTile->byDrawID = 0;

			m_vecTile.push_back(pTile);
		}
	}

	//�̴� ������
	m_MiniSize.fXSize = 0.2f;
	m_MiniSize.fYSize = 0.2f;
	m_MiniSize.fZSize = 0.2f;

	m_RenderCheck_Text = false;

	return S_OK;
}

int CTile::Update(void)
{
	return 0;
}

void CTile::Render(void)
{
	D3DXMATRIX matTrans;

	TCHAR szIndexText[MIDDLE_STR] = L"";

	for(int i = 0; i < m_xyCount.iYCount; ++i)
	{
		for(int j = 0; j < m_xyCount.iXCount; ++j)
		{
			int iIndex = i * m_xyCount.iXCount + j;

			if(iIndex < 0 || m_xyCount.iXCount * m_xyCount.iYCount <= iIndex)
				break;

			const TEX_INFO* pTileTex = 
				CTextureMgr::GetInstance()->GetTexture(L"Back",
				L"Tile",
				m_vecTile[iIndex]->byDrawID);

			D3DXMatrixTranslation(&matTrans
				, m_vecTile[iIndex]->vPos.x - m_pMainView->GetScrollPos(0)	//0 : x
				, m_vecTile[iIndex]->vPos.y - m_pMainView->GetScrollPos(1)	//1 : y
				, 0.f);

			CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

			CDevice::GetInstance()->GetSprite()->Draw(
				pTileTex->pTexture,
				NULL, 
				&D3DXVECTOR3(47.f, 24.f, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255)
				);

			//Ÿ�� �ε��� ���

			if (m_RenderCheck_Text == true)
			{
				wsprintf(szIndexText, L"%d", iIndex);

				RECT rc = { 0, -5, 0, 0 };

				CDevice::GetInstance()->GetFont()->DrawTextW(
					CDevice::GetInstance()->GetSprite(),
					szIndexText,
					lstrlen(szIndexText),
					&rc,
					DT_CENTER | DT_NOCLIP,
					D3DCOLOR_ARGB(255, 0, 0, 0)
				);
			}
		}
	}


}

void CTile::Release(void)
{
	for(size_t i = 0; i < m_vecTile.size(); ++i)
	{
		safe_delete(m_vecTile[i]);
	}
	m_vecTile.clear();
}

void CTile::MiniMapRender(void)
{
	D3DXMATRIX matTrans, matScale, matWorld;

	TCHAR szIndexText[MIDDLE_STR] = L"";

	const TEX_INFO* pStageTex = 
		CTextureMgr::GetInstance()->GetTexture(L"Stage");


	for(int i = 0; i < m_xyCount.iYCount; ++i)
	{
		for(int j = 0; j < m_xyCount.iXCount; ++j)
		{
			int iIndex = i * m_xyCount.iXCount + j;

			if(iIndex < 0 || m_xyCount.iXCount * m_xyCount.iYCount <= iIndex)
				break;

			const TEX_INFO* pTileTex = 
				CTextureMgr::GetInstance()->GetTexture(L"Back",
				L"Tile",
				m_vecTile[iIndex]->byDrawID);

			D3DXMatrixScaling(&matScale, m_MiniSize.fXSize, m_MiniSize.fYSize, m_MiniSize.fZSize);

			D3DXMatrixTranslation(&matTrans
				, m_vecTile[iIndex]->vPos.x * m_MiniSize.fXSize //- m_pMainView->GetScrollPos(0)	//0 : x
				, m_vecTile[iIndex]->vPos.y * m_MiniSize.fYSize //- m_pMainView->GetScrollPos(1)	//1 : y
				, 0.f);

			matWorld = matScale * matTrans;

			CDevice::GetInstance()->GetSprite()->SetTransform(&matWorld);

			CDevice::GetInstance()->GetSprite()->Draw(
				pTileTex->pTexture,
				NULL, 
				&D3DXVECTOR3(47.f, 24.f, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255)
				);
		}
	}
}

CTile::CTile(void)
{
	//ó�� Ÿ���� Tool76View�� ���� �޾ƿ´�.
	SetXYCount(((CMainFrame*)AfxGetMainWnd())->GetMainView()->GetXYCount());
}

CTile::~CTile(void)
{
	Release();
}

