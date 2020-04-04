#include "stdafx.h"
#include "Weapon.h"
#include "SceneMgr.h"
#include "TextureMgr.h"
#include "Device.h"
#include "TimeMgr.h"
#include "Mouse.h"
#include "AStar.h"
#include "ObjMgr.h"
#include "Tile.h"
#include "Player.h"


CWeapon::CWeapon()
{
}


CWeapon::~CWeapon()
{
}

HRESULT CWeapon::Initialize(void)
{
	//SetSwordPosFromPlayer();

	m_wstrObjKey = L"SwordStand";
	m_wstrStateKey = L"Down";

	m_tFrame = FRAME(0.f, 5.f, 5.f);

	m_RightCheck = 1.f;

	m_fTime = 0.f;

	m_bChangeCheck = false;

	m_bRenderCheck = true;

	return S_OK;
}

int CWeapon::Update(void)
{
	return 0;
}

void CWeapon::Render(void)
{
	if (m_bRenderCheck == true)
	{
		const TEX_INFO* pSwordTex =
			CTextureMgr::GetInstance()->GetTexture(
				m_wstrObjKey.c_str(),
				m_wstrStateKey.c_str(),
				static_cast<int>(m_tFrame.fIndex)
			);

		if (pSwordTex == NULL)
		{
			ERROR_MSG(L"무기 이미지 X");
			return;
		}

		float fX = CENTER_POS(pSwordTex->ImageInfo.Width);
		float fY = CENTER_POS(pSwordTex->ImageInfo.Height) + 30;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(
			pSwordTex->pTexture,
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255)
		);
	}
}

void CWeapon::Release(void)
{
}

void CWeapon::Update(INFO Info,eDir Dir, ePlayerState State)
{
	SetSwordPosFromPlayer(Info);
	SetDirFromPlayer(Dir);
	SetStateFromPlayer(State);
	WeaponState();
	MyMatrixCheck();
	MyFrameCheck();

	m_fTime += GET_TIME;
}

void CWeapon::SetSwordPosFromPlayer(INFO Info)
{
	SetPos(Info.vPos);
}

void CWeapon::SetDirFromPlayer(eDir Dir)
{
    m_eDir = Dir;
}

void CWeapon::SetStateFromPlayer(ePlayerState State)
{
	if (PlayerState != State)
	{
		PlayerState = State;

		switch (PlayerState)
		{
		case PLAYER_STAND:
			m_eState = WEAPON_STAND;
			m_bChangeCheck = true;
			break;
		case PLAYER_WALK:
		case PLAYER_RUN:
			m_bRenderCheck = false;
			break;
		case PLAYER_BASH:
			m_eState = WEAPON_BASH;
			m_bChangeCheck = true;
			break;
		case PLAYER_SLASH:
			m_eState = WEAPON_SLASH;
			m_bChangeCheck = true;
			break;
		case PLAYER_SKILL:
			m_bRenderCheck = false;
			break;
		case PLAYER_DAMAGE:
			m_bRenderCheck = false;
			break;
		}
	}
}

void CWeapon::WeaponState(void)
{
	switch (m_eDir)
	{
	case DIR_U:
		m_wstrStateKey = L"Up";
		m_RightCheck = 1.f;
		break;
	case DIR_D:
		m_wstrStateKey = L"Down";
		m_RightCheck = 1.f;
		break;
	case DIR_L:
		m_wstrStateKey = L"Left";
		m_RightCheck = 1.f;
		break;
	case DIR_R:
		m_wstrStateKey = L"Left";
		m_RightCheck = -1.f;
		break;
	case DIR_RU:
		m_wstrStateKey = L"LU";
		m_RightCheck = -1.f;
		break;
	case DIR_RD:
		m_wstrStateKey = L"LD";
		m_RightCheck = -1.f;
		break;
	case DIR_LU:
		m_wstrStateKey = L"LU";
		m_RightCheck = 1.f;
		break;
	case DIR_LD:
		m_wstrStateKey = L"LD";
		m_RightCheck = 1.f;
		break;
	}

	//상태 변환.
	if (m_bChangeCheck == true)
	{
		switch (m_eState)
		{
		case WEAPON_STAND:
			m_wstrObjKey = L"SwordStand";
			m_tFrame = FRAME(0.f, 5.f, 5.f);
			break;
		case WEAPON_BASH:
			m_wstrObjKey = L"SwordBash";
			if (m_wstrStateKey == L"Up")
				m_tFrame = FRAME(0.f, 2.f, 2.f);
			else
				m_tFrame = FRAME(0.f, 6.f, 6.f);
			break;
		case WEAPON_SLASH:
			m_wstrObjKey = L"SwordSlash";
			m_tFrame = FRAME(0.f, 5.f, 5.f);
			break;
		}

		m_bRenderCheck = true;
		m_bChangeCheck = false;
	}
}

void CWeapon::MyMatrixCheck(void)
{
	D3DXMATRIX matTrans;
	D3DXMATRIX matScale;


	D3DXMatrixScaling(&matScale,
		m_RightCheck, 1.f, 1.f);

	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x + m_vScroll.x,
		m_tInfo.vPos.y + m_vScroll.y,
		0.f
	);

	m_tInfo.matWorld = matScale * matTrans;
}

void CWeapon::MyFrameCheck(void)
{
	if (m_eState == WEAPON_STAND)
	{
		m_tFrame.fIndex += GET_TIME * m_tFrame.fCount * MOTION_SPEED_PLAYER;

		if (m_tFrame.fIndex >= m_tFrame.fMax)
			m_tFrame.fIndex = 0.f;
	}
	else
	{
		m_tFrame.fIndex += GET_TIME * m_tFrame.fCount * ATTACK_SPEED_WEAPON;

		if (m_tFrame.fIndex >= m_tFrame.fMax)
			m_tFrame.fIndex = 0.f;
	}
}
