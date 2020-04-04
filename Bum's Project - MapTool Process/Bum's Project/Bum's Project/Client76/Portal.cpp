#include "stdafx.h"
#include "Portal.h"
#include "Device.h"
#include "TextureMgr.h"
#include "ObjMgr.h"
#include "TimeMgr.h"
#include "Cursor.h"
#include "CollisionMgr.h"
#include "Mouse.h"

HRESULT CPortal::Initialize(void)
{
	m_wstrObjKey = L"Resorce";
	m_wstrStateKey = L"WarpGate";

	m_tInfo.fCX = 150;
	m_tInfo.fCY = 200;

	m_tFrame = FRAME(0.f, 24.f, 24.f);


	m_RenderType = RENDER_WORLD;

	return S_OK;
}

int CPortal::Update(void)
{
	D3DXVECTOR3 vMouse = CMouse::GetMousePos();

	MyMatrix();
	MyFrame();

	CCursor::m_bGateCheck = CCollisionMgr::GetInstance()
		->InvenDragCheckCollisionCheck(m_rc, vMouse);

	

	return 0;
}

void CPortal::Render(void)
{
	const TEX_INFO*	pPortalTex =
		CTextureMgr::GetInstance()->GetTexture(m_wstrObjKey.c_str(),
			m_wstrStateKey.c_str(),
			static_cast<int>(m_tFrame.fIndex)
		);

	if (pPortalTex == NULL)
	{
		ERROR_MSG(L"Æ÷Å» ÀÌ¹ÌÁö X");
		return;
	}

	float fX = CENTER_POS(pPortalTex->ImageInfo.Width);
	float fY = CENTER_POS(pPortalTex->ImageInfo.Height);

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	CDevice::GetInstance()->GetSprite()->Draw(
		pPortalTex->pTexture,
		NULL,
		&D3DXVECTOR3(fX, fY, 0.f),
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);
}

void CPortal::Release(void)
{
}

void CPortal::MyMatrix(void)
{
	m_rc = RectMake(m_tInfo.vPos.x + m_vScroll.x
		, m_tInfo.vPos.y + m_vScroll.y
		, m_tInfo.fCX, m_tInfo.fCY);

	D3DXMATRIX matTrans;

	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x + m_vScroll.x,
		m_tInfo.vPos.y + m_vScroll.y,
		0.f);

	m_tInfo.matWorld = matTrans;
}

void CPortal::MyFrame(void)
{
	m_tFrame.fIndex += GET_TIME * m_tFrame.fCount * MOTION_SPEED_PLAYER;

	if (m_tFrame.fIndex >= m_tFrame.fMax)
		m_tFrame.fIndex = 0.f;
}

CPortal::CPortal()
{
}


CPortal::~CPortal()
{
}
