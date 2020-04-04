#include "stdafx.h"
#include "BossBullet.h"
#include "Boss.h"
#include "Player.h"
#include "TextureMgr.h"
#include "ObjMgr.h"
#include "Device.h"
#include "TimeMgr.h"

HRESULT CBossBullet::Initialize(void)
{
	m_wstrObjKey = L"BB_EGG";
	m_wstrStateKey = L"UP";

	fSpeed = 0.7f;

	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 20.f;

	m_tInfo.vLook = D3DXVECTOR3(1.f, 0.f, 0.f);

	m_tFrame = FRAME(0.f, 1.f, 1.f);
	
	m_EndFrame = FRAME(0.f, 8.f, 8.f);

	m_bEndCheck = false;
	m_bDeleteCheck = false;

	fSpinAngle = 1.f;

	m_rc = RectMake(m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.fCX, m_tInfo.fCY);

	m_tRemainTime = 0.f;

	return S_OK;
}

int CBossBullet::Update(void)
{
	m_rc = RectMake(m_tInfo.vPos.x, m_tInfo.vPos.y, m_tInfo.fCX, m_tInfo.fCY);

	if (m_bEndCheck == false)
	{
		AI();
	}
	
	MyMatrixCheck();
	MyFrameCheck();

	m_tRemainTime += GET_TIME;

	if (m_tRemainTime > 3.f)
		m_bEndCheck = true;
	
	if (m_bDeleteCheck == true)
		return 0;
	else
		return 1;
}

void CBossBullet::Render(void)
{
	const TEX_INFO* pBulletTex =
		CTextureMgr::GetInstance()->GetTexture(
			m_wstrObjKey.c_str(),
			m_wstrStateKey.c_str(),
			static_cast<int>(m_tFrame.fIndex)
		);

	if (pBulletTex == NULL)
	{
		ERROR_MSG(L"º¸½º ºÒ¸´ ÀÌ¹ÌÁö X");
		return;
	}

	float fX = CENTER_POS(pBulletTex->ImageInfo.Width);
	float fY = CENTER_POS(pBulletTex->ImageInfo.Height);

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	CDevice::GetInstance()->GetSprite()->Draw(
		pBulletTex->pTexture,
		NULL,
		&D3DXVECTOR3(fX, fY, 0.f),
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);


	if (m_bEndCheck == true)
	{
		const TEX_INFO* pEffectTex =
			CTextureMgr::GetInstance()->GetTexture(
				L"Monster Skill",
				L"EnergyBall",
				static_cast<int>(m_EndFrame.fIndex)
			);

		if (pEffectTex == NULL)
		{
			ERROR_MSG(L"ºÒ¸´ÀÌÆå ÀÌ¹ÌÁö X");
			return;
		}

		fX = CENTER_POS(pEffectTex->ImageInfo.Width);
		fY = CENTER_POS(pEffectTex->ImageInfo.Height);

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(
			pEffectTex->pTexture,
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255)
		);
	}
}

void CBossBullet::Release(void)
{
}

void CBossBullet::AI(void)
{
	m_pPlayer = CObjMgr::GetInstance()->FindGameObject<CPlayer>();

	INFO Player = m_pPlayer->GetNormInfo();

	m_tInfo.vDir = Player.vPos - m_tInfo.vPos;

	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
	D3DXVec3Normalize(&m_tInfo.vLook, &m_tInfo.vLook);

	float fCos = D3DXVec3Dot(&m_tInfo.vDir, &m_tInfo.vLook);

	fAngle = acosf(fCos);
	fAngle2 = fAngle;
	if (m_tInfo.vPos.y < Player.vPos.y)
	{
		fAngle = 2 * D3DX_PI - fAngle;
	}

	m_tInfo.vPos.x += cosf(fAngle) * fSpeed;
	m_tInfo.vPos.y += -sinf(fAngle) * fSpeed;

	//fSpinAngle += 0.001f;
}

void CBossBullet::MyMatrixCheck(void)
{
	D3DXMATRIX matScale, matTrans, matRotZ;

	D3DXMatrixScaling(&matScale, 1.5f, 1.5f, 1.5f);
	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x + m_vScroll.x,
		m_tInfo.vPos.y + m_vScroll.y,
		0.f);
	D3DXMatrixRotationZ(&matRotZ, 2 * D3DX_PI - fAngle);

	m_tInfo.matWorld = matScale * matRotZ * matTrans;
}

void CBossBullet::MyFrameCheck(void)
{
	if (m_bEndCheck == true)
	{
		m_EndFrame.fIndex += GET_TIME * m_EndFrame.fCount * TARGET_SPEED;

		if (m_EndFrame.fIndex >= m_EndFrame.fMax)
		{
			m_EndFrame.fIndex = 0.f;
			m_bDeleteCheck = true;
		}
	}
}

CBossBullet::CBossBullet()
{
}

CBossBullet::CBossBullet(INFO Boss)
{
	m_pPlayer = CObjMgr::GetInstance()->FindGameObject<CPlayer>();
	m_pBoss = CObjMgr::GetInstance()->FindGameObject<CBoss>();

	INFO Player = m_pPlayer->GetNormInfo();
	float BossDir = 1.f;

	if (m_pBoss->GetBossRightCheck() == 2.f)
	{
		BossDir = 1.f;
	}
	else
	{
		BossDir = -1.f;
	}

	m_tInfo.vPos.x = Boss.vPos.x - ((Boss.fCX / 2.f) * BossDir);
	m_tInfo.vPos.y = Boss.vPos.y + 20;
	m_tInfo.vDir = Player.vPos - m_tInfo.vPos;

	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
	D3DXVec3Normalize(&m_tInfo.vLook, &m_tInfo.vLook);

	float fCos = D3DXVec3Dot(&m_tInfo.vDir, &m_tInfo.vLook);

	fAngle = acosf(fCos);

	if (m_tInfo.vPos.y < Player.vPos.y)
	{
		fAngle = 2 * D3DX_PI - fAngle;
	}
}


CBossBullet::~CBossBullet()
{
}
