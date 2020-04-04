#include "stdafx.h"
#include "Test.h"
#include "TextureMgr.h"
#include "Device.h"
#include "Mouse.h"
#include "AStar.h"
#include "ObjMgr.h"
#include "Tile.h"
#include "TimeMgr.h"

HRESULT CTest::Initialize(void)
{
	m_tInfo.vPos = D3DXVECTOR3(1380.f, 1128.f, 0.f);

	m_wstrObjKey = L"Test";

	return S_OK;
}

int CTest::Update(void)
{
	KeyCheck();
	AStarMove();
	MyMatrixCheck();

	return 0;
}

void CTest::Render(void)
{
	D3DXMATRIX matTrans;

	const TEX_INFO* pTestTex =
		CTextureMgr::GetInstance()->GetTexture(
			m_wstrObjKey.c_str());

	D3DXMatrixTranslation(&matTrans
		, m_tInfo.vPos.x + m_vScroll.x	//0 : x
		, m_tInfo.vPos.y + m_vScroll.y	//1 : y
		, 0.f);

	CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

	float fCX = CENTER_POS(pTestTex->ImageInfo.Width) ;
	float fCY = CENTER_POS(pTestTex->ImageInfo.Height);

	CDevice::GetInstance()->GetSprite()->Draw(
		pTestTex->pTexture,
		NULL,
		&D3DXVECTOR3(fCX, fCY, 0.f),
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);
}

void CTest::Release(void)
{
}

void CTest::MyMatrixCheck(void)
{
	D3DXMATRIX matTrans;

	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x + m_vScroll.x,
		m_tInfo.vPos.y + m_vScroll.y,
		0.f
	);

	m_tInfo.matWorld = matTrans;
}

void CTest::KeyCheck(void)
{
	/*if (GetAsyncKeyState(VK_LBUTTON))
	{
		D3DXVECTOR3 vMouse = CMouse::GetMousePos();
		
		vMouse.x -= m_vScroll.x;
		vMouse.y -= m_vScroll.y;

		XYCOUNT AStarBackCount = Tile::g_BackCount;

		CAStar::GetInstance()->AStarStartPos(m_tInfo.vPos, vMouse);
	}*/
}

void CTest::AStarMove(void)
{
	/*list<int>* pBestList = CAStar::GetInstance()->GetBestList();

	if (pBestList->empty())
		return;

	const vector<TILE*>* pVecTile
		= CObjMgr::GetInstance()->FindGameObject<Tile>()->GetTile();

	if (pVecTile == NULL)
		return;

	int iMoveIndex = pBestList->front();

	m_tInfo.vDir = (*pVecTile)[iMoveIndex]->vPos - m_tInfo.vPos;

	float fDist = D3DXVec3Length(&m_tInfo.vDir);

	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

	m_tInfo.vPos += m_tInfo.vDir * GET_TIME * 500.f;

	if (fDist < 5.f)
	{
		pBestList->pop_front();
	}*/
}

CTest::CTest()
{
}


CTest::~CTest()
{
	Release();
}
