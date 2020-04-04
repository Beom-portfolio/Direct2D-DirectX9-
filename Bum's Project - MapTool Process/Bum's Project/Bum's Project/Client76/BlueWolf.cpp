#include "stdafx.h"
#include "BlueWolf.h"
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
#include "DataSubject.h"
#include "MonHpBar.h"
#include "Damage.h"
#include "NormEffect.h"
#include "Critical.h"


HRESULT CBlueWolf::Initialize(void)
{
	m_pPlayer = CObjMgr::GetInstance()->GetList()[OBJ_TYPE_PLAYER].front();

	AS_Test = new CAStar;

	m_wstrObjKey = L"B_STAND";
	m_wstrStateKey = L"LDOWN";

	m_eDir = DIR_LD;
	m_MonState = MONSTER_STAND;

	m_tFrame = FRAME(0.f, 6.f, 6.f);

	m_RightCheck = 1.f;

	m_bAttachCheck = false;

	m_bRunCheck = false;

	m_bAStarCheck = false;

	m_fTime = 0.f;

	m_bChangeCheck = false;

	fSpeed = 50.f;

	m_MonColDir = COL_NONE;

	m_tInfo.fCX = 128;
	m_tInfo.fCY = 128;

	m_rc = RectMake(m_tInfo.vPos.x,
		m_tInfo.vPos.y,
		m_tInfo.fCX,
		m_tInfo.fCY);

	m_TargetCheck = false;

	m_TargetFrame = FRAME(0.f, 8.f, 8.f);

	//
	m_MonsterHitCheck = false;

	m_bCollCheck = false;


	//Hp, Mp
	m_iHp = 3000;
	m_pMonHpBar = new CMonHpBar(m_tInfo.vPos, m_iHp, int(m_tInfo.fCY / 2.f));
	m_pMonHpBar->Initialize();

	//Attack
	m_iAttack = 100;

	m_bPlayerHitCheck = false;

	//
	m_bPlayerHitCheck = false;

	m_bDeadCheck = false;

	m_MonsterAttackCheck = false;

	m_fUp = 0.f;

	m_Alpa = 255;
	//

	return S_OK;
}

int CBlueWolf::Update(void)
{
	//Rect
	m_rc = RectMake(m_tInfo.vPos.x,
		m_tInfo.vPos.y,
		m_tInfo.fCX,
		m_tInfo.fCY);

	m_bCollCheck =
		CCollisionMgr::GetInstance()->MonPlayerCollisionRect(this);

	if (m_bDeadCheck == false)
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

	m_pMonHpBar->Update(m_tInfo.vPos, m_iHp);
	m_pMonHpBar->SetHp(m_iHp);

	if (m_bDeadCheck == true)
	{
		m_fUp += DEAD_UP_SPEED;
		m_Alpa -= DEAD_ALPA_SPEED;

		if (m_Alpa <= 0.f)
		{
			return 0;
		}
	}

	m_fTime += GET_TIME;

	return 1;
}

void CBlueWolf::Render(void)
{
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
	const TEX_INFO* pMonsterTex =
		CTextureMgr::GetInstance()->GetTexture(
			m_wstrObjKey.c_str(),
			m_wstrStateKey.c_str(),
			static_cast<int>(m_tFrame.fIndex)
		);

	if (pMonsterTex == NULL)
	{
		ERROR_MSG(L"몬스터 이미지 X");
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

	m_pMonHpBar->Render();

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

void CBlueWolf::Release(void)
{
	safe_delete(m_pMonHpBar);
}

void CBlueWolf::AI(void)
{
	D3DXVECTOR3 PlayerPos =
		CObjMgr::GetInstance()
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
		if (m_MonState == MONSTER_DAMAGE)
		{
			//데미지를 입었을때 모션
		}
		else
		{
			//데미지를 입지않는 모션
			MonsterDamage();

			m_MonState = MONSTER_DAMAGE;

			m_bChangeCheck = true;

			fSpeed = 0.f;

			m_MonsterHitCheck = false;
		}
	}
	//플레이어와 매우 가까워지면 공격모션
	else if (m_bCollCheck == true)
	{
		if (m_MonState != MONSTER_ATTACK)
		{
			m_MonState = MONSTER_ATTACK;
			m_bChangeCheck = true;
			m_bAStarCheck = false;
			m_bAttachCheck = true;
		}
	}
	else if(m_bCollCheck == false)
	{
		//일정범위에서.
		if (PlayerRange <= 300)
		{
			//플레이어를 따라옴
			if (m_bAStarCheck == false || m_fTime > 1.3f)
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

void CBlueWolf::MonsterState(void)
{
	switch (m_eDir)
	{
	case DIR_U:
		m_wstrStateKey = L"LUP";
		m_RightCheck = 1.f;
		break;
	case DIR_D:
		m_wstrStateKey = L"LDOWN";
		m_RightCheck = 1.f;
		break;
	case DIR_L:
		m_wstrStateKey = L"LDOWN";
		m_RightCheck = 1.f;
		break;
	case DIR_R:
		m_wstrStateKey = L"LDOWN";
		m_RightCheck = -1.f;
		break;
	case DIR_RU:
		m_wstrStateKey = L"LUP";
		m_RightCheck = -1.f;
		break;
	case DIR_RD:
		m_wstrStateKey = L"LDOWN";
		m_RightCheck = -1.f;
		break;
	case DIR_LU:
		m_wstrStateKey = L"LUP";
		m_RightCheck = 1.f;
		break;
	case DIR_LD:
		m_wstrStateKey = L"LDOWN";
		m_RightCheck = 1.f;
		break;
	}

	//상태 변환.
	if (m_bChangeCheck == true)
	{
		switch (m_MonState)
		{
		case MONSTER_STAND:
			m_wstrObjKey = L"B_STAND";
			m_tFrame = FRAME(0.f, 6.f, 6.f);
			break;
		case MONSTER_WALK:
			m_wstrObjKey = L"B_WALK";
			m_tFrame = FRAME(0.f, 6.f, 6.f);
			break;
		case MONSTER_ATTACK:
			m_wstrObjKey = L"B_ATTACK";
			m_tFrame = FRAME(0.f, 8.f, 8.f);
			m_MonsterAttackCheck = true;
			break;
		case MONSTER_DAMAGE:
			m_wstrObjKey = L"B_DAMAGE";
			m_tFrame = FRAME(0.f, 1.f, 1.f);
			break;
		}

		m_bChangeCheck = false;
	}
}

void CBlueWolf::MonsterDir(int MoveIndex)
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

void CBlueWolf::MyMatrixCheck(void)
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


	//

	m_tInfo.matWorld = matScale * matTrans;
}

void CBlueWolf::AStarMove(void)
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

void CBlueWolf::MyFrameCheck(void)
{
	if (m_bAttachCheck == true)
	{
		m_tFrame.fIndex += GET_TIME * m_tFrame.fCount;

		//때릴때 hp감소 및 플레이어 경직

		if (m_tFrame.fIndex >= 4.f && m_MonsterAttackCheck == true)
		{
			m_bPlayerHitCheck = true;
			CObjMgr::GetInstance()->FindGameObject<CPlayer>()
				->SetMonsterDamage(m_iAttack);

			m_MonsterAttackCheck = false;
		}

		if (m_tFrame.fIndex >= m_tFrame.fMax)
		{
			m_tFrame.fIndex = 0.f;
			m_bPlayerHitCheck = false;
			m_MonState = MONSTER_STAND;
			m_bChangeCheck = true;
			m_bAttachCheck = false;
			m_fTime = 0.f;
		}
	}
	else
	{
		m_tFrame.fIndex += GET_TIME * m_tFrame.fCount;

		if (m_tFrame.fIndex > m_tFrame.fMax)
		{
			if (fSpeed == 0.f)
				fSpeed = 50.f;
			m_tFrame.fIndex = 0.f;
		}

		m_bPlayerHitCheck = false;
	}

	//타깃
	if (m_TargetCheck == true)
	{
		m_TargetFrame.fIndex += GET_TIME * m_TargetFrame.fCount * TARGET_SPEED;

		if (m_TargetFrame.fIndex > m_TargetFrame.fMax)
		{
			m_TargetFrame.fIndex = 0.f;
		}
	}
}

void CBlueWolf::MonsterDamage(void)
{
	int iAttackDamage = CObjMgr::GetInstance()->FindGameObject<CPlayer>()
						->GetPlayerMagicalDamage();

	int iCriticalDamage = iAttackDamage * 2;

	if (m_MonsterHitCheck == true)
	{
		//체력감소
		if(CPlayer::g_bCriCheck == true)
		{
			if (m_iHp > 0)
				m_iHp -= iCriticalDamage;

			CCritical *Temp_Cri = new CCritical(m_tInfo.vPos, (int)m_tInfo.fCY);
			Temp_Cri->Initialize();
			m_vecCriEffect.push_back(Temp_Cri);
		}
		else
		{
			if(m_iHp > 0)
				m_iHp -= iAttackDamage;
		}
		

		CNormEffect *DmgEffectTemp = new CNormEffect(m_tInfo.vPos, EFFECT_MONSTER);
		DmgEffectTemp->Initialize();
		m_vecDmgEffect.push_back(DmgEffectTemp);

		if (CPlayer::g_bCriCheck == true)
		{
			CDamage *Temp = new CDamage(m_tInfo.vPos, 0.2f, iCriticalDamage * 10, (int)m_tInfo.fCY);
			Temp->Initialize();
			m_vecDamage.push_back(Temp);
		}
		else
		{
			CDamage *Temp = new CDamage(m_tInfo.vPos, 0.2f, iAttackDamage * 10, (int)m_tInfo.fCY);
			Temp->Initialize();
			m_vecDamage.push_back(Temp);
		}

		if (m_iHp < 0)
		{
			m_bDeadCheck = true;
		}
	}

	CSoundMgr::GetInstance()->PlaySound(L"Collision.wav", CSoundMgr::Channel_Eff);
}

CBlueWolf::CBlueWolf()
{
}


CBlueWolf::~CBlueWolf()
{
	Release();
}
