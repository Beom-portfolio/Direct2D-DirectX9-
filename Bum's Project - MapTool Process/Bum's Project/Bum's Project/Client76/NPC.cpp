#include "stdafx.h"
#include "NPC.h"
#include "Device.h"
#include "TextureMgr.h"
#include "Inven.h"
#include "Shop.h"
#include "UserInterface.h"
#include "ObjMgr.h"
#include "TimeMgr.h"
#include "CollisionMgr.h"
#include "Mouse.h"



HRESULT CNPC::Initialize(void)
{
	m_wstrObjKey = L"NPC";
	m_wstrStateKey = L"Linda";

	m_tInfo.vPos = D3DXVECTOR3(850.f, 400.f, 0.f);

	m_tInfo.fCX = 128;
	m_tInfo.fCY = 128;

	m_tFrame = FRAME(0.f, 12.f, 12.f);

	m_rc = RectMake(m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.fCX, m_tInfo.fCY);

	m_RenderType = RENDER_WORLD;

	m_fTime = 0.f;

	m_bCollCheck = false;

	return S_OK;
}

int CNPC::Update(void)
{
	D3DXVECTOR3 vMouse = CMouse::GetMousePos();

	MyMatrix();
	MyFrame();

	m_bCollCheck = CCollisionMgr::GetInstance()
		->InvenDragCheckCollisionCheck(m_rc, vMouse);

	if (CShop::m_bRenderCheckShop == false &&
		m_bCollCheck == true		 && 
		GetAsyncKeyState(VK_LBUTTON) && 
		m_fTime > 0.2f)
	{
		CSoundMgr::GetInstance()->PlaySound(L"ShopClick.wav", CSoundMgr::Channel_Eff);

		CShop::m_bRenderCheckShop = true;
		CInven::m_bRenderCheckInven = true;

		m_fTime = 0.f;
	}

	m_fTime += GET_TIME;

	return 0;
}

void CNPC::Render(void)
{
	const TEX_INFO*	pNPCTex =
		CTextureMgr::GetInstance()->GetTexture(m_wstrObjKey.c_str(),
			m_wstrStateKey.c_str(),
			static_cast<int>(m_tFrame.fIndex)
		);

	if (pNPCTex == NULL)
	{
		ERROR_MSG(L"NPC ÀÌ¹ÌÁö X");
		return;
	}

	float fX = CENTER_POS(pNPCTex->ImageInfo.Width);
	float fY = CENTER_POS(pNPCTex->ImageInfo.Height);

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	CDevice::GetInstance()->GetSprite()->Draw(
		pNPCTex->pTexture,
		NULL,
		&D3DXVECTOR3(fX, fY, 0.f),
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	); 

	//Rectangle(GetDC(g_hWnd), m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);
}

void CNPC::Release(void)
{
}

void CNPC::MyMatrix(void)
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

void CNPC::MyFrame(void)
{
	m_tFrame.fIndex += GET_TIME * m_tFrame.fCount * MOTION_SPEED_PLAYER;

	if (m_tFrame.fIndex >= m_tFrame.fMax)
		m_tFrame.fIndex = 0.f;
}

CNPC::CNPC()
{
}


CNPC::~CNPC()
{
}
