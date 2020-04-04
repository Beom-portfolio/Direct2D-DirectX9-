#include "stdafx.h"
#include "Tree.h"
#include "SceneMgr.h"
#include "Device.h"
#include "TextureMgr.h"
#include "Player.h"
#include "ObjMgr.h"

HRESULT CTree::Initialize(void)
{
	LoadTree();

	m_wstrObjKey = L"Object";
	m_wstrStateKey = L"Tree";

	m_RenderType = RENDER_WORLD;

	return S_OK;
}

int CTree::Update(void)
{

	YSorting();
	AlpaCheck();


	return 0;
}

void CTree::Render(void)
{
	D3DXMATRIX matWorld;
	D3DXMATRIX matTrans;

	vector<OBJINFO*>::iterator iter = m_vecTree.begin();
	vector<OBJINFO*>::iterator iter_end = m_vecTree.end();

	for (vector<OBJINFO*>::iterator i = iter; i != iter_end; ++i)
	{
		m_testrc = RectMake((*i)->vPos.x + m_vScroll.x,
			(*i)->vPos.y + m_vScroll.y + TTT,
			(*i)->fCX,
			(*i)->fCY);

		//Rectangle(GetDC(g_hWnd), m_testrc.left, m_testrc.top, m_testrc.right, m_testrc.bottom);

		const TEX_INFO* pTileTex =
			CTextureMgr::GetInstance()->GetTexture(m_wstrObjKey.c_str(),
				m_wstrStateKey.c_str(),
				(*i)->byDrawID);

		D3DXMatrixTranslation(&matTrans
			, (*i)->vPos.x + m_vScroll.x	//0 : x
			, (*i)->vPos.y + m_vScroll.y	//1 : y
			, 0.f);

		(*i)->rc = RectMake((*i)->vPos.x + m_vScroll.x,
			(*i)->vPos.y + m_vScroll.y + TTT,
			(*i)->fCX,
			(*i)->fCY);

		CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

		float fCenterX = pTileTex->ImageInfo.Width / 2.f;
		float fCenterY = pTileTex->ImageInfo.Height / 1.25f;
		
		if ((*i)->bAlpa == true)
		{
			CDevice::GetInstance()->GetSprite()->Draw(
				pTileTex->pTexture,
				NULL,
				&D3DXVECTOR3(fCenterX, fCenterY, 0.f),
				NULL,
				D3DCOLOR_ARGB(180, 255, 255, 255)
			);
		}
		else
		{
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

void CTree::Release(void)
{
	for (size_t i = 0; i < m_vecTree.size(); ++i)
	{
		safe_delete(m_vecTree[i]);
	}
	m_vecTree.clear();
}

void CTree::YSorting(void)
{
	vector<OBJINFO*>::iterator iter_back = m_vecTree_Back.begin();
	vector<OBJINFO*>::iterator iter_back_end = m_vecTree_Back.end();

	vector<OBJINFO*>::iterator iter_front = m_vecTree.begin();
	vector<OBJINFO*>::iterator iter_front_end = m_vecTree.end();

	CPlayer* m_pPlayer = CObjMgr::GetInstance()->FindGameObject<CPlayer>();
	
	//앞 -> 뒤
	if (!(m_vecTree.empty()))
	{
		for (auto i = iter_front; i != iter_front_end;)
		{
			INFO PlayerInfo = m_pPlayer->GetNormInfo();
			OBJINFO *TreeInfo = (*i);

			if ((PlayerInfo.vPos.y + PlayerInfo.fCY / 2.f) >
				((TreeInfo->vPos.y + TreeInfo->fCY / 2.f) + YYY))
			{
				m_vecTree_Back.push_back(*i);
				i = m_vecTree.erase(i);

				iter_front_end = m_vecTree.end();
			}
			else
			{
				if ((PlayerInfo.vPos.y + PlayerInfo.fCY / 2.f) <
					((TreeInfo->vPos.y - TreeInfo->fCY / 2.f) - 60))
				{
					m_vecTree_Back.push_back(*i);
					i = m_vecTree.erase(i);

					iter_front_end = m_vecTree.end();
				}
				else
				{
					++i;
				}
			}
				
		}
	}

	//뒤 -> 앞
	if (!(m_vecTree_Back.empty()))
	{
		iter_back = m_vecTree_Back.begin();
		iter_back_end = m_vecTree_Back.end();

		for (auto i = iter_back; i != iter_back_end;)
		{
			INFO PlayerInfo = m_pPlayer->GetNormInfo();
			OBJINFO *TreeInfo = (*i);

			if ((PlayerInfo.vPos.y + PlayerInfo.fCY / 2.f) <
				(TreeInfo->vPos.y + TreeInfo->fCY / 2.f) + YYY)
			{
				if ((PlayerInfo.vPos.y + PlayerInfo.fCY / 2.f) <
					((TreeInfo->vPos.y - TreeInfo->fCY / 2.f) - 60))
				{
					++i;
				}
				else
				{
					m_vecTree.push_back(*i);
					i = m_vecTree_Back.erase(i);

					iter_back_end = m_vecTree_Back.end();
				}
			}
			else
			{
				++i;
			}

		}
	}
}

void CTree::AlpaCheck(void)
{
	vector<OBJINFO*>::iterator iter_front = m_vecTree.begin();
	vector<OBJINFO*>::iterator iter_front_end = m_vecTree.end();

	vector<OBJINFO*>::iterator iter_back = m_vecTree_Back.begin();
	vector<OBJINFO*>::iterator iter_back_end = m_vecTree_Back.end();

	CPlayer* m_pPlayer = CObjMgr::GetInstance()->FindGameObject<CPlayer>();

	//알파블랜딩
	//뒤
	if (!(m_vecTree_Back.empty()))
	{
		for (auto i = iter_back; i != iter_back_end;++i)
		{
			(*i)->bAlpa = false;
		}
	}
	//앞
	if (!(m_vecTree.empty()))
	{
		for (auto i = iter_front; i != iter_front_end;)
		{
			INFO PlayerInfo = m_pPlayer->GetNormInfo();
			OBJINFO *TreeInfo = (*i);

			float PlayerLeft = (PlayerInfo.vPos.x - PlayerInfo.fCX / 2.f);
			float PlayerRight = (PlayerInfo.vPos.x + PlayerInfo.fCX / 2.f);
			float TreeLeft = (TreeInfo->vPos.x + m_vScroll.x) - (TreeInfo->fCX / 2.f);
			float TreeRight = (TreeInfo->vPos.x + m_vScroll.x) + (TreeInfo->fCX / 2.f);



			if (PlayerInfo.vPos.x + m_vScroll.x >= TreeLeft &&
				PlayerInfo.vPos.x + m_vScroll.x <= TreeRight)
			{
				(*i)->bAlpa = true;
				++i;
			}
			else
			{
				(*i)->bAlpa = false;
				++i;
			}

		}
	}
}

void CTree::RenderBack(void)
{
	D3DXMATRIX matTrans;

	vector<OBJINFO*>::iterator iter = m_vecTree_Back.begin();
	vector<OBJINFO*>::iterator iter_end = m_vecTree_Back.end();

	for (vector<OBJINFO*>::iterator i = iter; i != iter_end; ++i)
	{
		m_testrc = RectMake((*i)->vPos.x + m_vScroll.x,
			(*i)->vPos.y + m_vScroll.y + TTT,
			(*i)->fCX,
			(*i)->fCY);

		//Rectangle(GetDC(g_hWnd), m_testrc.left, m_testrc.top, m_testrc.right, m_testrc.bottom);

		const TEX_INFO* pTileTex =
			CTextureMgr::GetInstance()->GetTexture(m_wstrObjKey.c_str(),
				m_wstrStateKey.c_str(),
				(*i)->byDrawID);

		D3DXMatrixTranslation(&matTrans
			, (*i)->vPos.x + m_vScroll.x	//0 : x
			, (*i)->vPos.y + m_vScroll.y	//1 : y
			, 0.f);

		(*i)->rc = RectMake((*i)->vPos.x + m_vScroll.x,
			(*i)->vPos.y + m_vScroll.y + TTT,
			(*i)->fCX,
			(*i)->fCY);

		CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

		float fCenterX = pTileTex->ImageInfo.Width / 2.f;
		float fCenterY = pTileTex->ImageInfo.Height / 1.25f;

		if ((*i)->bAlpa == true)
		{
			CDevice::GetInstance()->GetSprite()->Draw(
				pTileTex->pTexture,
				NULL,
				&D3DXVECTOR3(fCenterX, fCenterY, 0.f),
				NULL,
				D3DCOLOR_ARGB(255, 255, 255, 255)
			);
		}
		else
		{
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

void CTree::LoadTree(void)
{
	DWORD dwByte = 0;

	HANDLE hFile;

	eSceneType eType = CSceneMgr::GetInstance()->GetSceneType();

	int i = eType;

	switch (eType)
	{
	case SCENE_FIELD:
		hFile = CreateFile(
			L"../Data/Object/Field.dat",
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
			L"../Data/Object/Town.dat",
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

	while (true)
	{
		OBJINFO* pObjData = new OBJINFO;

		ReadFile(hFile, pObjData, sizeof(OBJINFO), &dwByte, NULL);

		if (dwByte == 0)
		{
			safe_delete(pObjData);
			break;
		}

		m_vecTree.push_back(pObjData);
	}

	CloseHandle(hFile);
}

CTree::CTree()
{
}


CTree::~CTree()
{
}
