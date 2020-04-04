#include "stdafx.h"
#include "Tile.h"
#include "SceneMgr.h"
#include "Mouse.h"
#include "TimeMgr.h"
#include "Device.h"
#include "TextureMgr.h"

bool Tile::m_RenderCheck = false;
XYCOUNT Tile::g_BackCount;

HRESULT Tile::Initialize(void)
{
	m_fTime = 0.f;

	m_wstrObjKey = L"Resorce";
	m_wstrStateKey = L"Tile";

	LoadTile();

	//컬링
	m_ptTileRender.x = WINCX / TILECX + 3;
	m_ptTileRender.y = static_cast<LONG>(WINCY / (TILECY / 2.f) + 2);

	m_RenderType = RENDER_BACKGROUND;

	return S_OK;
}

int Tile::Update(void)
{
	//MouseScrollCheck();
	KeyInput();

	m_fTime += GET_TIME;
	return 0;
}

void Tile::Render(void)
{
	D3DXMATRIX matTrans;

	TCHAR szIndexText[MIDDLE_STR] = L"";

	if (Tile::m_RenderCheck == true)
	{
		for (int i = 0; i < m_ptTileRender.y; ++i)
		{
			for (int j = 0; j < m_ptTileRender.x; ++j)
			{
				int iCullX = int(-m_vScroll.x) / TILECX;
				int iCullY = int((-m_vScroll.y) / (TILECY / 2.f));

				int iIndex = (i + iCullY) * m_BackCount.iXCount + (j + iCullX);

				if (iIndex < 0 || m_BackCount.iXCount * m_BackCount.iYCount <= iIndex)
					break;

				const TEX_INFO* pTileTex =
					CTextureMgr::GetInstance()->GetTexture(
						m_wstrObjKey.c_str(),
						m_wstrStateKey.c_str(),
						m_vecTile[iIndex]->byDrawID);

				D3DXMatrixTranslation(&matTrans
					, m_vecTile[iIndex]->vPos.x + m_vScroll.x	//0 : x
					, m_vecTile[iIndex]->vPos.y + m_vScroll.y	//1 : y
					, 0.f);

				CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

				CDevice::GetInstance()->GetSprite()->Draw(
					pTileTex->pTexture,
					NULL,
					&D3DXVECTOR3(47.f, 24.f, 0.f),
					NULL,
					D3DCOLOR_ARGB(255, 255, 255, 255)
				);

				//타일 인덱스 출력

				
				wsprintf(szIndexText, L"%d", iIndex);

				RECT rc = { 0, -5, 0, 0 };

				CDevice::GetInstance()->GetFont()->DrawTextW(
					CDevice::GetInstance()->GetSprite(),
					szIndexText,
					lstrlen(szIndexText),
					&rc,
					DT_CENTER | DT_NOCLIP,
					D3DCOLOR_ARGB(255, 255, 255, 255)
				);

			}
		}
	}
}

void Tile::Release(void)
{
	for (size_t i = 0; i < m_vecTile.size(); ++i)
	{
		safe_delete(m_vecTile[i]);
	}
	m_vecTile.clear();
}

void Tile::KeyInput(void)
{
	if (GetAsyncKeyState('Q') && m_fTime > 1.f )
	{
		if(m_RenderCheck == false)
		{
			m_RenderCheck = true;
		}
		else
		{
			m_RenderCheck = false;
		}

		m_fTime = 0.f;
	}
	
}

void Tile::LoadTile(void)
{
	DWORD dwByte = 0;

	HANDLE hFile;

	eSceneType eType = CSceneMgr::GetInstance()->GetSceneType();

	int i = eType;

	switch (eType)
	{
	case SCENE_FIELD:
		hFile = CreateFile(
			L"../Data/Map/Field.dat",
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,		//기본값으로 파일을 생성하라는옵션.
			NULL
		);
		break;

	case SCENE_STAGE:
		hFile = CreateFile(
			L"../Data/Map/Stage.dat",
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,		//기본값으로 파일을 생성하라는옵션.
			NULL
		);
		break;

	case SCENE_BOSSSTAGE:
		hFile = CreateFile(
			L"../Data/Map/BossStage.dat",
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,		//기본값으로 파일을 생성하라는옵션.
			NULL
		);
		break;

	case SCENE_HOUSE:
		hFile = CreateFile(
			L"../Data/Map/House.dat",
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,		//기본값으로 파일을 생성하라는옵션.
			NULL
		);
		break;

	case SCENE_SMITHY:
		hFile = CreateFile(
			L"../Data/Map/Smithy.dat",
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,		//기본값으로 파일을 생성하라는옵션.
			NULL
		);
		break;

	case SCENE_SMITHY2:
		hFile = CreateFile(
			L"../Data/Map/Smithy2.dat",
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,		//기본값으로 파일을 생성하라는옵션.
			NULL
		);
		break;

	case SCENE_STORE:
		hFile = CreateFile(
			L"../Data/Map/Store.dat",
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,		//기본값으로 파일을 생성하라는옵션.
			NULL
		);
		break;

	case SCENE_TOWN:
		hFile = CreateFile(
			L"../Data/Map/Town.dat",
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,		//기본값으로 파일을 생성하라는옵션.
			NULL
		);
		break;

	case SCENE_TOWN2:
		hFile = CreateFile(
			L"../Data/Map/Town2.dat",
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,		//기본값으로 파일을 생성하라는옵션.
			NULL
		);
		break;
	}

	Release();

	//안쓰는 데이터를 불러넘김
	BACKINFO m_BackInfo;
	ReadFile(hFile, &m_BackInfo, sizeof(BACKINFO), &dwByte, NULL);
	//
	
	//
	ReadFile(hFile, &m_BackCount, sizeof(XYCOUNT), &dwByte, NULL);

	//다른 곳에서 공유하면서 쓸 BackCount
	g_BackCount = m_BackCount;

	while (true)
	{
		TILE* pTileData = new TILE;

		ReadFile(hFile, pTileData, sizeof(TILE), &dwByte, NULL);

		if (dwByte == 0)
		{
			safe_delete(pTileData);
			break;
		}

		m_vecTile.push_back(pTileData);
	}

	CloseHandle(hFile);
}

void Tile::MouseScrollCheck(void)
{
	//D3DXVECTOR3 vMousePos = CMouse::GetMousePos();

	//float fTime = CTimeMgr::GetInstance()->GetTime();

	//if (0 > vMousePos.x)
	//{
	//	m_vScroll.x += fTime * fSpeed;
	//}

	//if (WINCX < vMousePos.x)
	//{
	//	m_vScroll.x -= fTime * fSpeed;
	//}

	//if (0 > vMousePos.y)
	//{
	//	m_vScroll.y += fTime * fSpeed;
	//}

	//if (WINCY < vMousePos.y)
	//{
	//	m_vScroll.y -= fTime * fSpeed;
	//}
}

Tile::Tile()
{
}


Tile::~Tile()
{
}

