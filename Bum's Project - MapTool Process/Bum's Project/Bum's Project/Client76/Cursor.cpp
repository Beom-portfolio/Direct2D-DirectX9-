#include "stdafx.h"
#include "Cursor.h"
#include "Device.h"
#include "TextureMgr.h"
#include "UserInterface.h"
#include "ObjMgr.h"
#include "TimeMgr.h"
#include "CollisionMgr.h"
#include "Mouse.h"

bool CCursor::m_bBattleCheck = false;
bool CCursor::m_bGateCheck = false;

HRESULT CCursor::Initialize(void)
{
	m_wstrObjKey = L"Mouse";
	m_wstrStateKey = L"Normal";

	m_tInfo.vPos = D3DXVECTOR3(400.f, 300.f, 0.f);

	m_tFrame = FRAME(0.f, 13.f, 13.f);

	m_RenderType = RENDER_UI;

	m_fTime = 0.f;

	m_bChangeCheck = false;

	m_eMouseState = MOUSE_NORMAL;

	return S_OK;
}

int CCursor::Update(void)
{
	if (m_bBattleCheck == true)
	{
		m_eMouseState = MOUSE_BATTLE;
		m_bChangeCheck = true;
	}

	if (m_bGateCheck == true)
	{
		m_eMouseState = MOUSE_GATE;
		m_bChangeCheck = true;
	}


	if (m_bGateCheck == false && m_bBattleCheck == false)
	{
		m_eMouseState = MOUSE_NORMAL;
		m_bChangeCheck = true;
	}


	MyMatrix();
	StateCheck();
	MyFrame();

	m_fTime += GET_TIME;

	return 0;
}

void CCursor::Render(void)
{
	const TEX_INFO*	pCursorTex =
		CTextureMgr::GetInstance()->GetTexture(m_wstrObjKey.c_str(),
			m_wstrStateKey.c_str(),
			static_cast<int>(m_tFrame.fIndex)
		);

	if (pCursorTex == NULL)
	{
		ERROR_MSG(L"마우스 이미지 X");
		return;
	}

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	CDevice::GetInstance()->GetSprite()->Draw(
		pCursorTex->pTexture,
		NULL,
		&D3DXVECTOR3(0.f, 0.f, 0.f),
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);

}

void CCursor::Release(void)
{
}

void CCursor::MyMatrix(void)
{
	D3DXVECTOR3 vMouse = CMouse::GetMousePos();

	D3DXMATRIX matTrans;

	D3DXMatrixTranslation(&matTrans,
		vMouse.x,
		vMouse.y,
		0.f);

	m_tInfo.matWorld = matTrans;
}

void CCursor::MyFrame(void)
{
	m_tFrame.fIndex += GET_TIME * m_tFrame.fCount * 1.f;

	if (m_tFrame.fIndex >= m_tFrame.fMax)
	{
		m_tFrame.fIndex = 0.f;
	}
}

void CCursor::StateCheck(void)
{
	if (m_bChangeCheck == true)
	{
		switch (m_eMouseState)
		{
		case MOUSE_NORMAL:
			m_wstrStateKey = L"Normal";
			m_tFrame.fCount = 13.f;
			m_tFrame.fMax = 13.f;
			break;
		case MOUSE_GATE:
			m_wstrStateKey = L"Gate";
			m_tFrame.fCount = 4.f;
			m_tFrame.fMax = 4.f;
			//m_tFrame = FRAME(0.f, 4.f, 4.f);
			break;
		case MOUSE_BATTLE:
			m_wstrStateKey = L"Battle";
			m_tFrame.fCount = 7.f;
			m_tFrame.fMax = 7.f;
			//m_tFrame = FRAME(0.f, 7.f, 7.f);
			break;
		}

		m_bChangeCheck = false;
	}
}

CCursor::CCursor()
{
}


CCursor::~CCursor()
{
}
