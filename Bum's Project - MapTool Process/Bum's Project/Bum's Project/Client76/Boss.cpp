#include "stdafx.h"
#include "Boss.h"
#include "TextureMgr.h"
#include "Device.h"
#include "TimeMgr.h"
#include "Mouse.h"
#include "AStar.h"
#include "ObjMgr.h"
#include "Tile.h"
#include "Player.h"
#include "TextureMgr.h"
#include "Device.h"
#include "TimeMgr.h"
#include "Mouse.h"
#include "AStar.h"
#include "ObjMgr.h"
#include "Tile.h"
#include "Weapon.h"
#include "CollisionMgr.h"
#include "EffectFactory.h"
#include "EffectBuffer.h"
#include "ShakeMgr.h"
#include "BossBullet.h"
#include "MonHpBar.h"
#include "Damage.h"
#include "NormEffect.h"
#include "Critical.h"
#include "Monster.h"
#include "Jelly.h"

HRESULT CBoss::Initialize(void)
{
	m_pPlayer = CObjMgr::GetInstance()->GetList()[OBJ_TYPE_PLAYER].front();

	AS_Test = new CAStar;

	m_tInfo.vPos = D3DXVECTOR3(1560.f, 830.f, 0.f);

	m_wstrObjKey = L"BB_STAND";
	m_wstrStateKey = L"Left";

	m_eDir = DIR_LD;
	m_MonState = MONSTER_STAND;

	m_tFrame = FRAME(0.f, 1.f, 1.f);

	m_RightCheck = 2.f;

	m_bAttachCheck = false;

	m_bRunCheck = false;

	m_bAStarCheck = false;

	m_fTime = 0.f;

	m_bChangeCheck = false;

	fSpeed = 30.f;

	m_MonColDir = COL_NONE;

	m_tInfo.fCX = 230;
	m_tInfo.fCY = 230;

	m_rc = RectMake(m_tInfo.vPos.x,
		m_tInfo.vPos.y,
		m_tInfo.fCX,
		m_tInfo.fCY);

	m_TargetCheck = false;

	m_TargetFrame = FRAME(0.f, 8.f, 8.f);

	m_RenderType = RENDER_WORLD;
	//
	m_MonsterHitCheck = false;

	m_bCollCheck = false;

	m_bBackRenderCheck = false;

	//Hp, Mp
	m_iHp = 50000;
	m_iMaxHp = m_iHp;
	m_pBossHpBar = new CMonHpBar(m_tInfo.vPos, m_iHp, int(m_tInfo.fCY / 2.f));
	m_pBossHpBar->Initialize();

	//Attack
	m_iAttack = 600;

	m_bPlayerHitCheck = false;

	//
	m_bDeadCheck = false;

	m_MonsterAttackCheck = false;

	m_fUp = 0.f;

	m_Alpa = 255;
	//

	m_fAttackTerm = 0.f;

	//
	m_tJellyPattern = 0.f;
	m_tShieldPattern = 0.f;
	m_tHoldingPattern = 0.f;

	///
	m_ImpactFrame = FRAME(0, 5.f, 5.f);
	m_bImpactCheck = false;
	m_bShieldCheck = false;
	m_fWalkSpeed = 1.4f;

	m_fBossTerm = 1.f;

	m_PhaseOne = false;
	m_PhaseTwo = false;
	m_PhaseThree = false;

	///
	m_ShieldFrame = FRAME(0, 14.f, 14.f);


	m_bHoldingCheck = false;

	m_HoldingFrame = FRAME(0, 6.f, 6.f);

	m_iHoldingCount = 0;

	return S_OK;
}

int CBoss::Update(void)
{
	//Rect
	m_rc = RectMake(m_tInfo.vPos.x,
		m_tInfo.vPos.y + 10,
		m_tInfo.fCX,
		m_tInfo.fCY);

	m_AttackRange = RectMake(m_tInfo.vPos.x,
		m_tInfo.vPos.y + 10,
		m_tInfo.fCX + 250,
		m_tInfo.fCY + 250);

	//Rectangle(GetDC(g_hWnd), m_AttackRange.left, m_AttackRange.top, m_AttackRange.right, m_AttackRange.bottom);

	CObjMgr::GetInstance()->FindGameObject<CPlayer>()
		->SetBossDamage(m_iAttack);

	m_bCollCheck =
		CCollisionMgr::GetInstance()->PlayerAttackRangeCollisionRect(this);

	CShakeMgr::GetInstance()->Progress();

	//Bullet
	vector<CBossBullet*>::iterator iter_B = m_vecBullet.begin();
	vector<CBossBullet*>::iterator iter_end_B = m_vecBullet.end();

	for (auto i = iter_B; i != iter_end_B;)
	{
		if ((*i)->Update() == 1)
		{
			++i;
		}
		else
		{
			i = m_vecBullet.erase(i);
		}

		iter_end_B = m_vecBullet.end();
	}


	if (m_MonState != MONSTER_DIE)
	{
		AI();
		AStarMove();
	}
	else
	{
		m_TargetCheck = false;
	}
	MonsterState();
	MyMatrixCheck();
	MyFrameCheck();
	YSorting();
	YSortJelly();

	///
	vector<CDamage*>::iterator iter_D = m_vecDamage.begin();
	vector<CDamage*>::iterator iter_end_D = m_vecDamage.end();

	for (auto i = iter_D; i != iter_end_D;)
	{
		if ((*i)->Update(m_tInfo.vPos) == 1)
		{
			++i;
		}
		else
		{
			i = m_vecDamage.erase(i);
		}

		iter_end_D = m_vecDamage.end();
	}

	///
	vector<CNormEffect*>::iterator iter_E = m_vecDmgEffect.begin();
	vector<CNormEffect*>::iterator iter_end_E = m_vecDmgEffect.end();

	for (auto i = iter_E; i != iter_end_E;)
	{
		if ((*i)->Update(m_tInfo.vPos) == 1)
		{
			++i;
		}
		else
		{
			i = m_vecDmgEffect.erase(i);
		}

		iter_end_E = m_vecDmgEffect.end();
	}


	///
	vector<CCritical*>::iterator iter_C = m_vecCriEffect.begin();
	vector<CCritical*>::iterator iter_end_C = m_vecCriEffect.end();

	for (auto i = iter_C; i != iter_end_C;)
	{
		if ((*i)->Update(m_tInfo.vPos) == 1)
		{
			++i;
		}
		else
		{
			i = m_vecCriEffect.erase(i);
		}

		iter_end_C = m_vecCriEffect.end();
	}

	m_pBossHpBar->Update(m_tInfo.vPos, m_iHp);
	m_pBossHpBar->SetHp(m_iHp);

	if (m_bDeadCheck == true)
	{
		m_fUp += DEAD_UP_SPEED;
		m_Alpa -= DEAD_ALPA_SPEED;

		if (m_Alpa <= 0.f)
		{
			//delete this;
			return 1;
		}
	}

	//젤리삐
	vector<CMonster*>::iterator iter = m_vecJelly.begin();
	vector<CMonster*>::iterator iter_end = m_vecJelly.end();

	for (auto i = iter; i != iter_end;)
	{
		if ((*i)->Update() == 1)
		{
			++i;
		}
		else
		{
			i = m_vecJelly.erase(i);
		}

		iter_end = m_vecJelly.end();
	}
	
	vector<CMonster*>::iterator iter_b = m_vecBackJelly.begin();
	vector<CMonster*>::iterator iter_b_end = m_vecBackJelly.end();

	for (auto i = iter_b; i != iter_b_end;)
	{
		if ((*i)->Update() == 1)
		{
			++i;
		}
		else
		{
			i = m_vecBackJelly.erase(i);
			iter_b_end = m_vecBackJelly.end();
		}
	}
	//

	m_fTime += GET_TIME;
	m_fAttackTerm += GET_TIME;

	return 0;
}

void CBoss::Render(void)
{
	if (m_bBackRenderCheck == false)
	{
		for (size_t i = 0; i < m_vecBackJelly.size(); ++i)
		{
			m_vecBackJelly[i]->Render();
		}
	}

	if (m_TargetCheck == true &&
		m_bBackRenderCheck == false
		)
	{
		D3DXMATRIX TempScale;

		const TEX_INFO* pTargetTex =
			CTextureMgr::GetInstance()->GetTexture(
				L"Effect",
				L"TagetOn",
				static_cast<int>(m_TargetFrame.fIndex)
			);

		if (pTargetTex == NULL)
		{
			ERROR_MSG(L"타깃 이미지 X");
			return;
		}

		D3DXMATRIX matTrans;
		D3DXMATRIX matScale;

		D3DXMatrixScaling(&matScale,
			3.f, 3.f, 3.f);

		D3DXMatrixTranslation(&matTrans,
			m_tInfo.vPos.x + m_vScroll.x,
			m_tInfo.vPos.y + m_vScroll.y,
			0.f
		);

		m_tInfo.matWorld = matScale * matTrans;

		float fX = CENTER_POS(pTargetTex->ImageInfo.Width);
		float fY = CENTER_POS(pTargetTex->ImageInfo.Height) - 40;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(
			pTargetTex->pTexture,
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255)
		);
	}
	//
	if (m_bBackRenderCheck == false)
	{
		MyMatrixCheck();

		const TEX_INFO* pMonsterTex =
			CTextureMgr::GetInstance()->GetTexture(
				m_wstrObjKey.c_str(),
				m_wstrStateKey.c_str(),
				static_cast<int>(m_tFrame.fIndex)
			);

		if (pMonsterTex == NULL)
		{
			ERROR_MSG(L"보스 이미지 X");
			return;
		}

		float fX = CENTER_POS(pMonsterTex->ImageInfo.Width);
		float fY = CENTER_POS(pMonsterTex->ImageInfo.Height);

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(
			pMonsterTex->pTexture,
			NULL,
			&D3DXVECTOR3(fX, fY + m_fUp, 0.f),
			NULL,
			D3DCOLOR_ARGB(m_Alpa, 255, 255, 255)
		);

		//물감옥
		if (m_bShieldCheck == true)
		{
			const TEX_INFO* pShieldTex =
				CTextureMgr::GetInstance()->GetTexture(
					L"Effect",
					L"WaterJail",
					static_cast<int>(m_ShieldFrame.fIndex)
				);

			if (pShieldTex == NULL)
			{
				ERROR_MSG(L"물감옥 이미지 X");
				return;
			}

			D3DXMATRIX matTrans;
			D3DXMATRIX matScale;

			D3DXMatrixScaling(&matScale,
				2.f, 2.f, 0.f);

			D3DXMatrixTranslation(&matTrans,
				m_tInfo.vPos.x + m_vScroll.x,
				m_tInfo.vPos.y + m_vScroll.y,
				0.f
			);

			m_tInfo.matWorld = matScale * matTrans;

			fX = CENTER_POS(pShieldTex->ImageInfo.Width);
			fY = CENTER_POS(pShieldTex->ImageInfo.Height);

			CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

			CDevice::GetInstance()->GetSprite()->Draw(
				pShieldTex->pTexture,
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(m_Alpa, 255, 255, 255)
			);
		}

		//임펙트
		if (m_bImpactCheck == true)
		{
			const TEX_INFO* pImpactTex =
				CTextureMgr::GetInstance()->GetTexture(
					L"Impact",
					L"Impact",
					static_cast<int>(m_ImpactFrame.fIndex)
				);

			if (pImpactTex == NULL)
			{
				ERROR_MSG(L"임펙트 이미지 X");
				return;
			}

			D3DXMATRIX matTrans;
			D3DXMATRIX matScale;

			D3DXMatrixScaling(&matScale,
				3.f, 3.f, 0.f);

			D3DXMatrixTranslation(&matTrans,
				m_tInfo.vPos.x + m_vScroll.x,
				m_tInfo.vPos.y + m_vScroll.y,
				0.f
			);

			m_tInfo.matWorld = matScale * matTrans;

			fX = CENTER_POS(pImpactTex->ImageInfo.Width);
			fY = CENTER_POS(pImpactTex->ImageInfo.Height) - 30.f;

			CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

			CDevice::GetInstance()->GetSprite()->Draw(
				pImpactTex->pTexture,
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(m_Alpa, 255, 255, 255)
			);
		}

		//홀딩
		if (m_bHoldingCheck == true)
		{
			const TEX_INFO* pHoldTex =
				CTextureMgr::GetInstance()->GetTexture(
					L"Effect",
					L"Hold",
					static_cast<int>(m_HoldingFrame.fIndex)
				);

			if (pHoldTex == NULL)
			{
				ERROR_MSG(L"물감옥 이미지 X");
				return;
			}

			fX = CENTER_POS(pHoldTex->ImageInfo.Width);
			fY = CENTER_POS(pHoldTex->ImageInfo.Height);

			CDevice::GetInstance()->GetSprite()->SetTransform(&m_tHoldInfo.matWorld);

			CDevice::GetInstance()->GetSprite()->Draw(
				pHoldTex->pTexture,
				NULL,
				&D3DXVECTOR3(fX, fY, 0.f),
				NULL,
				D3DCOLOR_ARGB(m_Alpa, 255, 255, 255)
			);
		}
	}

	m_pBossHpBar->Render();
	
	//젤리삐
	if (m_bBackRenderCheck == true)
	{
		for (size_t i = 0; i < m_vecJelly.size(); ++i)
		{
			m_vecJelly[i]->Render();
		}
	}

	//Bullet
	for (size_t i = 0; i < m_vecBullet.size(); ++i)
	{
		m_vecBullet[i]->Render();
	}

	for (size_t i = 0; i < m_vecCriEffect.size(); ++i)
	{
		m_vecCriEffect[i]->Render();
	}

	for (size_t i = 0; i < m_vecDamage.size(); ++i)
	{
		m_vecDamage[i]->Render();
	}

	for (size_t i = 0; i < m_vecDmgEffect.size(); ++i)
	{
		m_vecDmgEffect[i]->Render();
	}

}

void CBoss::Release(void)
{
	safe_delete(m_pBossHpBar);
}

void CBoss::AI(void)
{
	D3DXVECTOR3 PlayerPos = CObjMgr::GetInstance()
		->GetList()[OBJ_TYPE_PLAYER].front()
		->GetInfo()->vPos;

	float PlayerRange =
		Distance(PlayerPos.x,
			PlayerPos.y,
			m_tInfo.vPos.x,
			m_tInfo.vPos.y);

	//플레이어가 때렸을시
	if (m_MonsterHitCheck == true)
	{
		MonsterDamage();

		m_MonsterHitCheck = false;
	}
	//플레이어와 매우 가까워지면 공격모션
	
	if (m_bCollCheck == true)
	{
		if (m_MonState != MONSTER_ATTACK)
		{
			if (m_MonState == MONSTER_DIE)
			{

			}
			else
			{
				m_MonState = MONSTER_ATTACK;
				m_bChangeCheck = true;
				m_bAStarCheck = false;
				m_bAttachCheck = true;
			}
		}
	}
	else if (m_bCollCheck == false)
	{
		if (m_MonState == MONSTER_DIE)
		{

		}
		else
		{
			//일정범위에서.
			if (PlayerRange <= 600)
			{
				//플레이어를 따라옴
				if (m_bAStarCheck == false || m_fTime > m_fBossTerm)
				{
					XYCOUNT AStarBackCount = Tile::g_BackCount;

					AS_Test->AStarStartPos(m_tInfo.vPos, PlayerPos);

					m_MonState = MONSTER_WALK;
					m_bAStarCheck = true;
					m_bChangeCheck = true;

					m_fTime = 0.f;
				}
			}
			else
			{
				m_MonState = MONSTER_STAND;
				m_bChangeCheck = true;
				m_bAStarCheck = false;
			}
		}
	}

	//젤리삐 소환 패턴
	if (m_tJellyPattern > 35.f)
	{
		for (int i = 0; i < 15; ++i)
		{
			int		  P_M = 1;
			
			if (rand() % 100 >= 50)
				P_M = 1;
			else
				P_M = -1;

			
			CMonster* Temp = new CJelly;
			Temp->Initialize();
			Temp->SetPos(m_tInfo.vPos.x + (rand() % int(m_tInfo.fCX) * P_M),
				m_tInfo.vPos.y + (rand() % int(m_tInfo.fCY) * P_M));
			m_vecJelly.push_back(Temp);
		}

		m_tJellyPattern = 0.f;
	}

	//보호막 패턴
	if (m_tShieldPattern > 15.f)
	{
		m_bShieldCheck = true;
		m_iShieldCount = 0;

		m_tShieldPattern = 0.f;
	}

	if (m_iShieldCount > 10)
	{
		m_bShieldCheck = false;
	}

	//홀딩 패턴
	if (m_tHoldingPattern > 10.f)
	{
		m_bHoldingCheck = true;
		m_tHoldingPattern = 0.f;
	}

	if (m_iHoldingCount > 4)
	{
		m_bHoldingCheck = false;
		m_iHoldingCount = 0;
		CPlayer::g_WalkCheck = true;
	}

	if (m_bHoldingCheck == true)
	{
		CPlayer::g_WalkCheck = false;
	}
	else
	{
		CPlayer::g_WalkCheck = true;
	}

	float HpPercent = ((float)m_iHp / m_iMaxHp);

	//////////////////////////////////////////////////////////////////////////////
	if (HpPercent <= 0.75f		 &&
		HpPercent > 0.50f)
	{
		if (m_PhaseOne == false)
		{
			m_fWalkSpeed = 1.7f;
			fSpeed = 30.f;
			m_iAttack = 700;
			m_fBossTerm = 0.7f;
			m_tJellyPattern = 35.f;
			m_PhaseOne = true;
		}

		m_tJellyPattern += GET_TIME;
	}
	//////////////////////////////////////////////////////////////////////////////
	else if (HpPercent <= 0.50f  &&
		HpPercent > 0.3f)
	{
		if (m_PhaseTwo == false)
		{
			m_fWalkSpeed = 2.0f;
			fSpeed = 40.f;
			m_iAttack = 900;
			m_fBossTerm = 0.6f;
			m_tShieldPattern = 15.f;
			m_PhaseTwo = true;
		}

		m_tJellyPattern  += GET_TIME;
		m_tShieldPattern += GET_TIME;
	}
	//////////////////////////////////////////////////////////////////////////////
	else if (HpPercent <= 0.3f  &&
		HpPercent > 0.f)
	{
		if (m_PhaseThree == false)
		{
			m_fWalkSpeed = 2.5f;
			fSpeed = 50.f;
			m_iAttack = 1100;
			m_fBossTerm = 0.5f;
			m_tShieldPattern = 5.f;
			m_PhaseThree = true;
		}

		m_tJellyPattern   += GET_TIME;
		m_tShieldPattern  += GET_TIME;
		m_tHoldingPattern += GET_TIME;
	}
}

void CBoss::MonsterState(void)
{
	switch (m_eDir)
	{
	case DIR_U:
		m_wstrStateKey = L"Left";
		m_RightCheck = 2.f;
		break;
	case DIR_D:
		m_wstrStateKey = L"Left";
		m_RightCheck = 2.f;
		break;
	case DIR_L:
		m_wstrStateKey = L"Left";
		m_RightCheck = 2.f;
		break;
	case DIR_R:
		m_wstrStateKey = L"Left";
		m_RightCheck = -2.f;
		break;
	case DIR_RU:
		m_wstrStateKey = L"Left";
		m_RightCheck = -2.f;
		break;
	case DIR_RD:
		m_wstrStateKey = L"Left";
		m_RightCheck = -2.f;
		break;
	case DIR_LU:
		m_wstrStateKey = L"Left";
		m_RightCheck = 2.f;
		break;
	case DIR_LD:
		m_wstrStateKey = L"Left";
		m_RightCheck = 2.f;
		break;
	}

	//상태 변환.
	if (m_bChangeCheck == true)
	{
		switch (m_MonState)
		{
		case MONSTER_STAND:
			m_wstrObjKey = L"BB_STAND";
			m_tFrame = FRAME(0.f, 1.f, 1.f);
			break;
		case MONSTER_WALK:
			m_wstrObjKey = L"BB_WALK";
			m_tFrame = FRAME(0.f, 13.f, 13.f);
			break;
		case MONSTER_ATTACK:
			m_wstrObjKey = L"BB_THROW";
			m_tFrame = FRAME(0.f, 7.f, 7.f);
			m_MonsterAttackCheck = true;
			break;
		case MONSTER_DAMAGE:
			//MonsterDamage();
			break;
		case MONSTER_DIE:
			m_wstrObjKey = L"BB_DEATH";
			m_tFrame = FRAME(0.f, 3.f, 3.f);
			break;
		}

		m_bChangeCheck = false;
	}
}

void CBoss::MonsterDir(int MoveIndex)
{
	int iStartIndex = AS_Test->GetTileIndex(m_tInfo.vPos);

	int iTileNumX = Tile::g_BackCount.iXCount;

	if (iStartIndex - iTileNumX * 2 == MoveIndex)	//UP
		m_eDir = DIR_U;
	else if (iStartIndex + iTileNumX * 2 == MoveIndex)	//DOWN
		m_eDir = DIR_D;
	else if (iStartIndex - 1 == MoveIndex) //LEFT
		m_eDir = DIR_L;
	else if (iStartIndex + 1 == MoveIndex) //RIGHT
		m_eDir = DIR_R;
	else if (iStartIndex - (iTileNumX - (iStartIndex / iTileNumX) % 2) == MoveIndex) // RightUp
		m_eDir = DIR_RU;
	else if (iStartIndex + (iTileNumX + (iStartIndex / iTileNumX) % 2) == MoveIndex) //RightDown
		m_eDir = DIR_RD;
	else if (iStartIndex - (iTileNumX + (iStartIndex / iTileNumX + 1) % 2) == MoveIndex) //LeftUp
		m_eDir = DIR_LU;
	else if (iStartIndex + (iTileNumX + (iStartIndex / iTileNumX) % 2) - 1 == MoveIndex) // LeftDown
		m_eDir = DIR_LD;
}

void CBoss::MyMatrixCheck(void)
{
	D3DXMATRIX matTrans;
	D3DXMATRIX matScale;

	D3DXMatrixScaling(&matScale,
		m_RightCheck, 2.f, 2.f);

	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x + m_vScroll.x,
		m_tInfo.vPos.y + m_vScroll.y,
		0.f
	);

	//Rectangle(GetDC(g_hWnd), m_rc.left, m_rc.top, m_rc.right, m_rc.bottom);

	m_tInfo.matWorld = matScale * matTrans;

	//
	if (m_bHoldingCheck == true)
	{
		D3DXVECTOR3 Temp = CObjMgr::GetInstance()->FindGameObject<CPlayer>()->GetNormInfo().vPos;

		D3DXMATRIX matTrans;
		D3DXMATRIX matScale;

		D3DXMatrixScaling(&matScale,
			2.f, 2.f, 2.f);

		D3DXMatrixTranslation(&matTrans,
			Temp.x + m_vScroll.x,
			Temp.y + m_vScroll.y,
			0.f
		);

		m_tHoldInfo.matWorld = matScale * matTrans;
	}
}

void CBoss::AStarMove(void)
{
	if (m_bAStarCheck == true)
	{
		list<int>* pBestList = AS_Test->GetBestList();

		if (pBestList->empty())
		{
			m_MonState = MONSTER_STAND;
			m_bChangeCheck = true;
			m_bAStarCheck = false;
			return;
		}

		const vector<TILE*>* pVecTile
			= CObjMgr::GetInstance()->FindGameObject<Tile>()->GetTile();

		if (pVecTile == NULL)
			return;

		int iMoveIndex = pBestList->front();

		//
		MonsterDir(iMoveIndex);
		//

		m_tInfo.vDir = (*pVecTile)[iMoveIndex]->vPos - m_tInfo.vPos;

		float fDist = D3DXVec3Length(&m_tInfo.vDir);

		D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

		m_tInfo.vPos += m_tInfo.vDir * GET_TIME * fSpeed;

		if (fDist < 5.f)
		{
			pBestList->pop_front();
		}
	}
}

void CBoss::MyFrameCheck(void)
{
	if (m_bAttachCheck == true &&
		m_bCollCheck   == true)
	{
		m_tFrame.fIndex += GET_TIME * m_tFrame.fCount;

		//때릴때 hp감소 및 플레이어 경직

		if (m_tFrame.fIndex >= m_tFrame.fMax)
		{
			if (m_MonState == MONSTER_DIE)
			{
				m_tFrame.fIndex = 2.f;
				m_bAStarCheck = false;
				m_bDeadCheck = true;
			}
			else
			{
				CBossBullet* TempBullet = new CBossBullet(m_tInfo);
				TempBullet->Initialize();
				m_vecBullet.push_back(TempBullet);
				m_tFrame.fIndex = 0.f;
				m_MonState = MONSTER_WALK;
				m_bAttachCheck = false;
				m_fTime = 0.f;
			}
		}
	}
	else if (m_MonState == MONSTER_DIE)
	{
		m_tFrame.fIndex += GET_TIME * m_tFrame.fCount;

		if (m_tFrame.fIndex >= m_tFrame.fMax)
		{
			m_tFrame.fIndex = 2.f;
			m_bAStarCheck = false;
			m_bDeadCheck = true;
		}

		m_bPlayerHitCheck = false;
	}
	else if(m_MonState == MONSTER_WALK)
	{
		m_tFrame.fIndex += GET_TIME * m_tFrame.fCount * m_fWalkSpeed;
	
		
		if (m_tFrame.fIndex > m_tFrame.fMax)
		{
			m_tFrame.fIndex = 0.f;
			m_bImpactCheck = true;
			CShakeMgr::GetInstance()->SetShake(SHAKE_RANDOM, 11.f, D3DXVECTOR3(1.f, 1.f, 0.f));
			CShakeMgr::GetInstance()->Progress();
			m_MonState = MONSTER_STAND;
			m_bChangeCheck = true;
		}
	}
	else if(m_MonState == MONSTER_STAND)
	{
		m_tFrame.fIndex += GET_TIME * m_tFrame.fCount;

		if (m_tFrame.fIndex >= m_tFrame.fMax)
			m_tFrame.fIndex = 0.f;

	}

	//타깃
	if (m_TargetCheck == true)
	{
		m_TargetFrame.fIndex += GET_TIME * m_TargetFrame.fCount * TARGET_SPEED;

		if (m_TargetFrame.fIndex >= m_TargetFrame.fMax)
			m_TargetFrame.fIndex = 0.f;
	}

	if (m_bImpactCheck == true)
	{
		m_ImpactFrame.fIndex += GET_TIME * m_ImpactFrame.fCount * TARGET_SPEED;

		if (m_ImpactFrame.fIndex >= m_ImpactFrame.fMax)
		{
			m_ImpactFrame.fIndex = 0.f;
			m_bImpactCheck = false;
		}
	}

	if (m_bShieldCheck == true)
	{
		m_ShieldFrame.fIndex += GET_TIME * m_ShieldFrame.fCount;

		if (m_ShieldFrame.fIndex >= m_ShieldFrame.fMax)
		{
			m_ShieldFrame.fIndex = 0.f;
		}
	}

	if (m_bHoldingCheck == true)
	{
		m_HoldingFrame.fIndex += GET_TIME * m_HoldingFrame.fCount;

		if (m_HoldingFrame.fIndex >= m_HoldingFrame.fMax)
		{
			m_HoldingFrame.fIndex = 0.f;
			++m_iHoldingCount;
		}
	}
}

void CBoss::MonsterDamage(void)
{
	int iAttackDamage = CObjMgr::GetInstance()->FindGameObject<CPlayer>()
		->GetPlayerMagicalDamage();

	int iCriticalDamage = iAttackDamage * 2;

	if (m_bShieldCheck == true)
	{
		iAttackDamage   = int(iAttackDamage * 0.3f);
		iCriticalDamage = int(iCriticalDamage * 0.3f);
		++m_iShieldCount;
	}

	if (m_MonsterHitCheck == true)
	{
		//체력감소
		if (CPlayer::g_bCriCheck == true)
		{
			if (m_iHp > 0)
				m_iHp -= iCriticalDamage;

			CCritical *Temp_Cri = new CCritical(m_tInfo.vPos, (int)m_tInfo.fCY - 70);
			Temp_Cri->Initialize();
			m_vecCriEffect.push_back(Temp_Cri);
		}
		else
		{
			if (m_iHp > 0)
				m_iHp -= iAttackDamage;
		}

		CNormEffect *DmgEffectTemp = new CNormEffect(m_tInfo.vPos, EFFECT_MONSTER);
		DmgEffectTemp->Initialize();
		m_vecDmgEffect.push_back(DmgEffectTemp);

		if (CPlayer::g_bCriCheck == true)
		{
			CDamage *Temp = new CDamage(m_tInfo.vPos, 0.2f, iCriticalDamage, (int)m_tInfo.fCY);
			Temp->Initialize();
			m_vecDamage.push_back(Temp);
		}
		else
		{
			CDamage *Temp = new CDamage(m_tInfo.vPos, 0.2f, iAttackDamage, (int)m_tInfo.fCY);
			Temp->Initialize();
			m_vecDamage.push_back(Temp);
		}

		if (m_iHp < 0)
		{
			m_MonState = MONSTER_DIE;

			m_bChangeCheck = true;

			fSpeed = 0.f;
		}
	}

	CSoundMgr::GetInstance()->PlaySound(L"Collision.wav", CSoundMgr::Channel_Eff);
}

void CBoss::YSorting(void)
{
	CPlayer* m_pPlayer = CObjMgr::GetInstance()->FindGameObject<CPlayer>();

	INFO PlayerInfo = m_pPlayer->GetNormInfo();

	//앞 >> 뒤
	if ((PlayerInfo.vPos.y + PlayerInfo.fCY / 2.f) >
		(m_tInfo.vPos.y + 30 + m_tInfo.fCY / 2.f))
	{
		m_bBackRenderCheck = true;
	}
	else
	{
		m_bBackRenderCheck = false;
	}
}

void CBoss::YSortJelly(void)
{
	vector<CMonster*>::iterator iter_back = m_vecBackJelly.begin();
	vector<CMonster*>::iterator iter_back_end = m_vecBackJelly.end();

	vector<CMonster*>::iterator iter_front = m_vecJelly.begin();
	vector<CMonster*>::iterator iter_front_end = m_vecJelly.end();


	//앞쪽 -> 뒤쪽
	if (!(m_vecJelly.empty()))
	{
		for (auto i = iter_front;
			i != iter_front_end;)
		{
			INFO BossInfo = m_tInfo;
			INFO MonsterInfo = (*i)->GetNormInfo();

			if ((BossInfo.vPos.y + (BossInfo.fCY / 2.f)) >
				MonsterInfo.vPos.y + (MonsterInfo.fCY / 2.f))
			{
				//넣고
				m_vecBackJelly.push_back(*i);
				//지우고
				i = m_vecJelly.erase(i);

				//iter_front = m_vecMon.begin();
				iter_front_end = m_vecJelly.end();
			}
			else
			{
				++i;
			}
		}
	}


	//뒤쪽 -> 앞쪽
	if (!(m_vecBackJelly.empty()))
	{
		iter_back = m_vecBackJelly.begin();
		iter_back_end = m_vecBackJelly.end();

		for (auto i = iter_back;
			i != iter_back_end;)
		{

			INFO BossInfo = m_tInfo;
			INFO MonsterInfo = (*i)->GetNormInfo();

			if ((BossInfo.vPos.y + (BossInfo.fCY / 2.f)) <
				MonsterInfo.vPos.y + (MonsterInfo.fCY / 2.f))
			{
				//넣고
				m_vecJelly.push_back(*i);
				//지우고
				i = m_vecBackJelly.erase(i);

				//iter_back = m_vecMon_Back.begin();
				iter_back_end = m_vecBackJelly.end();
			}
			else
			{
				++i;
			}
		}
	}
}

void CBoss::BackRender(void)
{
	if (m_bBackRenderCheck == true)
	{
		for (size_t i = 0; i < m_vecBackJelly.size(); ++i)
		{
			m_vecBackJelly[i]->Render();
		}
	}

	if (m_TargetCheck == true)
	{

		const TEX_INFO* pTargetTex =
			CTextureMgr::GetInstance()->GetTexture(
				L"Effect",
				L"TagetOn",
				static_cast<int>(m_TargetFrame.fIndex)
			);

		if (pTargetTex == NULL)
		{
			ERROR_MSG(L"타깃 이미지 X");
			return;
		}

		D3DXMATRIX matTrans;
		D3DXMATRIX matScale;

		D3DXMatrixScaling(&matScale,
			3.f, 3.f, 3.f);

		D3DXMatrixTranslation(&matTrans,
			m_tInfo.vPos.x + m_vScroll.x,
			m_tInfo.vPos.y + m_vScroll.y,
			0.f
		);

		m_tInfo.matWorld = matScale * matTrans;

		float fX = CENTER_POS(pTargetTex->ImageInfo.Width);
		float fY = CENTER_POS(pTargetTex->ImageInfo.Height) + 200;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(
			pTargetTex->pTexture,
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(255, 255, 255, 255)
		);
	}

	MyMatrixCheck();

	const TEX_INFO* pMonsterTex =
		CTextureMgr::GetInstance()->GetTexture(
			m_wstrObjKey.c_str(),
			m_wstrStateKey.c_str(),
			static_cast<int>(m_tFrame.fIndex)
		);

	if (pMonsterTex == NULL)
	{
		ERROR_MSG(L"보스 이미지 X");
		return;
	}

	float fX = CENTER_POS(pMonsterTex->ImageInfo.Width);
	float fY = CENTER_POS(pMonsterTex->ImageInfo.Height);

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	CDevice::GetInstance()->GetSprite()->Draw(
		pMonsterTex->pTexture,
		NULL,
		&D3DXVECTOR3(fX, fY, 0.f),
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);

	//물감옥
	if (m_bShieldCheck == true)
	{
		const TEX_INFO* pShieldTex =
			CTextureMgr::GetInstance()->GetTexture(
				L"Effect",
				L"WaterJail",
				static_cast<int>(m_ShieldFrame.fIndex)
			);

		if (pShieldTex == NULL)
		{
			ERROR_MSG(L"물감옥 이미지 X");
			return;
		}

		D3DXMATRIX matTrans;
		D3DXMATRIX matScale;

		D3DXMatrixScaling(&matScale,
			2.f, 2.f, 0.f);

		D3DXMatrixTranslation(&matTrans,
			m_tInfo.vPos.x + m_vScroll.x,
			m_tInfo.vPos.y + m_vScroll.y,
			0.f
		);

		m_tInfo.matWorld = matScale * matTrans;

		fX = CENTER_POS(pShieldTex->ImageInfo.Width);
		fY = CENTER_POS(pShieldTex->ImageInfo.Height);

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(
			pShieldTex->pTexture,
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(m_Alpa, 255, 255, 255)
		);
	}

	//임펙트
	if (m_bImpactCheck == true)
	{
		const TEX_INFO* pImpactTex =
			CTextureMgr::GetInstance()->GetTexture(
				L"Impact",
				L"Impact",
				static_cast<int>(m_ImpactFrame.fIndex)
			);

		if (pImpactTex == NULL)
		{
			ERROR_MSG(L"임펙트 이미지 X");
			return;
		}

		D3DXMATRIX matTrans;
		D3DXMATRIX matScale;

		D3DXMatrixScaling(&matScale,
			3.f, 3.f, 0.f);

		D3DXMatrixTranslation(&matTrans,
			m_tInfo.vPos.x + m_vScroll.x,
			m_tInfo.vPos.y + m_vScroll.y,
			0.f
		);

		m_tInfo.matWorld = matScale * matTrans;

		fX = CENTER_POS(pImpactTex->ImageInfo.Width);
		fY = CENTER_POS(pImpactTex->ImageInfo.Height) - 30.f;

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(
			pImpactTex->pTexture,
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(m_Alpa, 255, 255, 255)
		);
	}

	//홀딩
	if (m_bHoldingCheck == true)
	{
		const TEX_INFO* pHoldTex =
			CTextureMgr::GetInstance()->GetTexture(
				L"Effect",
				L"Hold",
				static_cast<int>(m_HoldingFrame.fIndex)
			);

		if (pHoldTex == NULL)
		{
			ERROR_MSG(L"물감옥 이미지 X");
			return;
		}

		fX = CENTER_POS(pHoldTex->ImageInfo.Width);
		fY = CENTER_POS(pHoldTex->ImageInfo.Height);

		CDevice::GetInstance()->GetSprite()->SetTransform(&m_tHoldInfo.matWorld);

		CDevice::GetInstance()->GetSprite()->Draw(
			pHoldTex->pTexture,
			NULL,
			&D3DXVECTOR3(fX, fY, 0.f),
			NULL,
			D3DCOLOR_ARGB(m_Alpa, 255, 255, 255)
		);
	}

	if (m_bBackRenderCheck == true)
	{
		for (size_t i = 0; i < m_vecJelly.size(); ++i)
		{
			m_vecJelly[i]->Render();
		}
	}
}

CBoss::CBoss()
{
}

CBoss::~CBoss()
{
	Release();
}
