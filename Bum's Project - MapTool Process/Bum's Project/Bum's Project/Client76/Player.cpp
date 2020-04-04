#include "StdAfx.h"
#include "Player.h"
#include "TextureMgr.h"
#include "Device.h"
#include "TimeMgr.h"
#include "Mouse.h"
#include "AStar.h"
#include "ObjMgr.h"
#include "Tile.h"
#include "Weapon.h"
#include "EffectFactory.h"
#include "EffectBuffer.h"
#include "Client76.h"
#include "CollisionMgr.h"
#include "Monster.h"
#include "Tree.h"
#include "Boss.h"
#include "DataSubject.h"
#include "Factory.h"
#include "HpBar.h"
#include "MpBar.h"
#include "Damage.h"
#include "NormEffect.h"
#include "Critical.h"
#include "BossBullet.h"
#include "Inven.h"
#include "Shop.h"
#include "EffectBuffer.h"
#include "Cursor.h"
#include "Equip.h"
#include "Status.h"
#include "SceneMgr.h"

bool CPlayer::g_bCriCheck = false;
bool CPlayer::g_WalkCheck = true;
/////////////////////////////////

HRESULT CPlayer::Initialize(void)
{
	Player_Weapon = new CWeapon;

	AS_Test = new CAStar;

	m_tInfo.vPos = D3DXVECTOR3(1380.f, 1128.f, 0.f);
	
	m_wstrObjKey = L"Stand";
	m_wstrStateKey = L"Down";

	m_tFrame = FRAME(0.f, 5.f, 5.f);

	m_RightCheck = 1.f;

	m_bRunCheck = true;

	m_bAttachCheck = false;

	m_bSkillCheck = false;

	m_fTime = 0.f;

	m_bChangeCheck = false;

	m_bAStarCheck = false;

	m_bYSortCheck = true;

	m_MouseCollCheck = false;

	m_MonsterMouseCheck = false;

	m_MouseCollBossCheck = false;

	m_BossMouseCheck = false;

	m_bLevelUpCheck = false;

	fSpeed = 200.f;

	//스크롤값

	Player_Weapon->Initialize();

	m_tInfo.fCX = 30;
	m_tInfo.fCY = 50;

	m_rc = RectMake(m_tInfo.vPos.x,
		m_tInfo.vPos.y + 30,
		m_tInfo.fCX,
		m_tInfo.fCY);

	m_RenderType = RENDER_WORLD;

	//HP, MP
	m_tData = UNIT_DATA(g_iHp , g_iMp);

	CDataSubject::GetInstance()->AddData(MESSAGE_PLAYER_DATA, &m_tData);
	CDataSubject::GetInstance()->Notify(MESSAGE_PLAYER_DATA, &m_tData);

	CDataSubject::GetInstance()->AddData(MESSAGE_PLAYER_MATRIX, &m_tInfo.matWorld);
	CDataSubject::GetInstance()->Notify(MESSAGE_PLAYER_MATRIX, &m_tInfo.matWorld);


	//Attack
	m_iAttack = 123;
	m_iMagicalDamage = 0;

	m_MonsterMouseCheck = false;

	m_fHoldTerm = 0.f;

	//Effect
	m_tLevelUp = FRAME(0.f, 30.f, 30.f);
	m_tLevelUp2 = FRAME(0.f, 20.f, 20.f);

	return S_OK;
}

int CPlayer::Update(void)
{
	m_iAttack = g_iAtt;

	//Rect
	m_rc = RectMake(m_tInfo.vPos.x,
		m_tInfo.vPos.y - 30,
		m_tInfo.fCX,
		m_tInfo.fCY);

	//크리티컬
	if (rand() % 100 >= 60)
	{
		g_bCriCheck = true;
	}
	else
	{
		g_bCriCheck = false;
	}

	//

	m_iCriticalDamage = m_iMagicalDamage * 2;

	KeyCheck();
	AStarMove();
	PlayerState();
	MyMatrixCheck();
	MyFrameCheck();
	PlayerScrollCheck();

	m_testrc = RectMake(m_tInfo.vPos.x + m_vScroll.x,
		m_tInfo.vPos.y + m_vScroll.y - 30,
		m_tInfo.fCX,
		m_tInfo.fCY);

	D_CAST(CWeapon*,Player_Weapon)->Update(m_tInfo, m_eDir, m_eState);

	if(CObjMgr::GetInstance()->FindGameObject<CMonster>() != NULL)
	{
		vector<CMonster*>* m_MonBackVec = CObjMgr::GetInstance()->FindGameObject<CMonster>()->GetMonsterBackVec();
		vector<CMonster*>* m_MonVec = CObjMgr::GetInstance()->FindGameObject<CMonster>()->GetMonsterVec();

		for (size_t i = 0; i < m_MonVec->size(); ++i)
		{
			if ((*m_MonVec)[i]->GetPlayerHitCheck() == true)
			{
				if ((*m_MonVec)[i]->GetMonsterState() == MONSTER_ATTACK)
				{
					PlayerDamage(m_iMonsterDamage);

					m_eState = PLAYER_DAMAGE;

					m_bChangeCheck = true;

					(*m_MonVec)[i]->SetPlayerHitCheck(false);
				}
			}
		}

		for (size_t i = 0; i < m_MonBackVec->size(); ++i)
		{
			if ((*m_MonBackVec)[i]->GetPlayerHitCheck() == true)
			{
				if ((*m_MonBackVec)[i]->GetMonsterState() == MONSTER_ATTACK)
				{
					PlayerDamage(m_iMonsterDamage);

					m_eState = PLAYER_DAMAGE;

					m_bChangeCheck = true;

					(*m_MonBackVec)[i]->SetPlayerHitCheck(false);
				}
			}
		}
	}

	if (CObjMgr::GetInstance()->FindGameObject<CBoss>() != NULL)
	{
		vector<CMonster*> *TempJelly = CObjMgr::GetInstance()->FindGameObject<CBoss>()->GetJelly();

		CBoss* Temp = CObjMgr::GetInstance()->FindGameObject<CBoss>();
		vector<CBossBullet*>* vecBullet = Temp->GetBossBullet();
		
		vector<CBossBullet*>::iterator iter = vecBullet->begin();
		vector<CBossBullet*>::iterator iter_end = vecBullet->end();

		for (auto i = iter; i != iter_end;)
		{
			if (CCollisionMgr::GetInstance()
				->PlayerBossBulletCollisionCheck(*i) == true)
			{
				PlayerDamage(m_iBossDamage);

				m_eState = PLAYER_DAMAGE;

				m_bChangeCheck = true;

				i = vecBullet->erase(i);
			}
			else
			{
				++i;
			}

			iter_end = vecBullet->end();
		}

		//

		for (size_t i = 0; i < TempJelly->size(); ++i)
		{
			if ((*TempJelly)[i]->GetPlayerHitCheck() == true)
			{
				if ((*TempJelly)[i]->GetMonsterState() == MONSTER_ATTACK)
				{
					PlayerDamage(m_iMonsterDamage);

					m_eState = PLAYER_DAMAGE;

					m_bChangeCheck = true;

					(*TempJelly)[i]->SetPlayerHitCheck(false);
				}
			}
		}
	}


	if (CPlayer::g_WalkCheck == false)
	{
		if (m_fHoldTerm > 1.f)
		{
			PlayerDamage(int(m_iBossDamage * 0.1f));

			m_eState = PLAYER_DAMAGE;

			m_bChangeCheck = true;
	
			m_fHoldTerm = 0.f;
		}
	}


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
	vector<CNormEffect*>::iterator iter_E		= m_vecDmgEffect.begin();
	vector<CNormEffect*>::iterator iter_end_E   = m_vecDmgEffect.end();

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
	vector<CCritical*>::iterator iter_C     = m_vecCriEffect.begin();
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


	CDataSubject::GetInstance()->Notify(MESSAGE_PLAYER_DATA, &m_tData);
	

	m_fTime += GET_TIME;
	m_fHoldTerm += GET_TIME;

	return 0;
}

void CPlayer::Render(void)
{


	if (CObjMgr::GetInstance()->FindGameObject<CTree>() != NULL)
		CObjMgr::GetInstance()->FindGameObject<CTree>()->RenderBack();

	if(CObjMgr::GetInstance()->FindGameObject<CMonster>() != NULL)
		CObjMgr::GetInstance()->FindGameObject<CMonster>()->RenderBack();

	if (CObjMgr::GetInstance()->FindGameObject<CBoss>() != NULL)
	{
		if (CObjMgr::GetInstance()->FindGameObject<CBoss>()
			->GetBackRenderCheck() == true)
		{
			CObjMgr::GetInstance()->FindGameObject<CBoss>()->BackRender();
		}
	}

	//Rectangle(GetDC(g_hWnd), m_testrc.left, m_testrc.top, m_testrc.right, m_testrc.bottom);

	if (m_bYSortCheck == true)
	{
		Player_Weapon->Render();
		RenderPlayer();
	}
	else
	{
		RenderPlayer();
		Player_Weapon->Render();
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

	if (m_bLevelUpCheck == true)
		RenderLevelUp();
}

void CPlayer::Release(void)
{
	safe_delete(Player_Weapon);
	CDataSubject::GetInstance()->RemoveData(MESSAGE_PLAYER_DATA, &m_tData);
	CDataSubject::GetInstance()->RemoveData(MESSAGE_PLAYER_MATRIX, &m_tInfo.matWorld);
}

void CPlayer::RenderPlayer(void)
{
	const TEX_INFO* pPlayerTex =
		CTextureMgr::GetInstance()->GetTexture(
			m_wstrObjKey.c_str(),
			m_wstrStateKey.c_str(),
			static_cast<int>(m_tFrame.fIndex)
		);

	if (pPlayerTex == NULL)
	{
		ERROR_MSG(L"플레이어 이미지 X");
		return;
	}

	float fX = CENTER_POS(pPlayerTex->ImageInfo.Width);
	float fY = CENTER_POS(pPlayerTex->ImageInfo.Height) + 30;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tInfo.matWorld);

	CDevice::GetInstance()->GetSprite()->Draw(
		pPlayerTex->pTexture,
		NULL,
		&D3DXVECTOR3(fX, fY, 0.f),
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);
}

void CPlayer::RenderLevelUp(void)
{
	const TEX_INFO* pLevelTex =
		CTextureMgr::GetInstance()->GetTexture(
			L"Effect",
			L"LevelUp",
			static_cast<int>(m_tLevelUp.fIndex)
		);

	if (pLevelTex == NULL)
	{
		ERROR_MSG(L"1 이미지 X");
		return;
	}

	float fX = CENTER_POS(pLevelTex->ImageInfo.Width)  - 10;
	float fY = CENTER_POS(pLevelTex->ImageInfo.Height) + 110;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tLevelUpInfo.matWorld);

	CDevice::GetInstance()->GetSprite()->Draw(
		pLevelTex->pTexture,
		NULL,
		&D3DXVECTOR3(fX, fY, 0.f),
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);
	////////////////////////////////////////////////////
	/*const TEX_INFO* pLevelETex =
		CTextureMgr::GetInstance()->GetTexture(
			L"Effect",
			L"LevelUpEffect",
			static_cast<int>(m_tLevelUp2.fIndex)
		);

	if (pLevelETex == NULL)
	{
		ERROR_MSG(L"2이미지 X");
		return;
	}

	fX = CENTER_POS(pLevelETex->ImageInfo.Width);
	fY = CENTER_POS(pLevelETex->ImageInfo.Height) + 30;

	CDevice::GetInstance()->GetSprite()->SetTransform(&m_tLevelUpInfo.matWorld);

	CDevice::GetInstance()->GetSprite()->Draw(
		pLevelETex->pTexture,
		NULL,
		&D3DXVECTOR3(fX, fY, 0.f),
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);*/
}

void CPlayer::MyMatrixCheck(void)
{
	CDataSubject::GetInstance()->Notify(MESSAGE_PLAYER_DATA, &m_tData);

	D3DXMATRIX matTrans;
	D3DXMATRIX matScale;

	
	D3DXMatrixScaling(&matScale,
		m_RightCheck, 1.f, 1.f);

	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x + m_vScroll.x,
		m_tInfo.vPos.y + m_vScroll.y,
		0.f
	);

	//UI
	m_tInfo.matWorld = matTrans;
	CDataSubject::GetInstance()->Notify(MESSAGE_PLAYER_MATRIX, &m_tInfo.matWorld);

	//
	m_tInfo.matWorld = matScale * matTrans;



	//Effect
	D3DXMATRIX matEffectTrans;
	D3DXMATRIX matEffectScale;


	D3DXMatrixScaling(&matEffectScale,
		1.f, 1.f, 1.f);

	D3DXMatrixTranslation(&matEffectTrans,
		m_tInfo.vPos.x + m_vScroll.x,
		m_tInfo.vPos.y + m_vScroll.y,
		0.f
	);

	m_tLevelUpInfo.matWorld = matEffectScale * matEffectTrans;

}

void CPlayer::KeyCheck(void)
{
	D3DXVECTOR3 vMouse = CMouse::GetMousePos();

	vMouse.x -= m_vScroll.x;
	vMouse.y -= m_vScroll.y;

	m_MonsterMouseCheck = CCollisionMgr::GetInstance()->MouseCollisionCheck(vMouse);
	m_BossMouseCheck = CCollisionMgr::GetInstance()->MouseBossCollisionCheck(vMouse);

	if (m_MonsterMouseCheck == true || m_BossMouseCheck == true)
	{
		CCursor::m_bBattleCheck = true;
	}
	else
	{
		CCursor::m_bBattleCheck = false;
	}

	if (GetAsyncKeyState(VK_LBUTTON) && m_MonsterMouseCheck == true)
	{
		m_MouseCollCheck =
			CCollisionMgr::GetInstance()->MouseCollision(vMouse, OBJ_TYPE_MONSTER);
	}


	if (GetAsyncKeyState(VK_LBUTTON) && m_BossMouseCheck == true)
	{
		m_MouseCollBossCheck =
			CCollisionMgr::GetInstance()->MouseBossCollision(vMouse);
	}

	if (GetAsyncKeyState(VK_LBUTTON)		 && 
		m_fTime > 0.5f						 && 
		m_MonsterMouseCheck == false		 &&
		m_BossMouseCheck    == false		 &&
		CInven::m_bRenderCheckInven   == false &&
		CShop::m_bRenderCheckShop     == false &&
		CEquip::m_bRenderCheckEquip   == false &&
		CStatus::m_bRenderCheckStatus == false &&
		g_WalkCheck == true)
	{
		CSoundMgr::GetInstance()->StopSound(CSoundMgr::Channel_Player);
		CSoundMgr::GetInstance()->PlaySound(L"VillageRun.wav", CSoundMgr::Channel_Player);

		XYCOUNT AStarBackCount = Tile::g_BackCount;

		AS_Test->AStarStartPos(m_tInfo.vPos, vMouse);

		if (m_bRunCheck == false)
		{
			m_eState = PLAYER_WALK;
		}
		else
		{
			m_eState = PLAYER_RUN;
		}

		m_bAStarCheck = true;
		m_bChangeCheck = true;


		m_fTime = 0.f;
	}
	
	if (GetAsyncKeyState('R') && m_fTime > 0.5f)
	{
		if (m_bRunCheck == false)
		{
			m_bRunCheck = true;
			fSpeed = 300.f;
		}
		else
		{
			m_bRunCheck = false;
			fSpeed = 200.f;
		}

		m_bChangeCheck = true;

		m_fTime = 0.f;
	}
	//
	if (GetAsyncKeyState('I') && m_fTime > 0.5f)
	{
		if (CInven::m_bRenderCheckInven == false)
				CInven::m_bRenderCheckInven = true;
		else
				CInven::m_bRenderCheckInven = false;

		m_fTime = 0.f;
	}
	//
	if (GetAsyncKeyState('P') && m_fTime > 0.5f)
	{
		
		CShop::m_bRenderCheckShop = false;

		if (CInven::m_bRenderCheckInven == true)
			CInven::m_bRenderCheckInven = false;

		m_fTime = 0.f;
	}
	//
	if (GetAsyncKeyState('O') && m_fTime > 0.5f)
	{
		if (CEquip::m_bRenderCheckEquip == false)
			CEquip::m_bRenderCheckEquip = true;
		else
			CEquip::m_bRenderCheckEquip = false;

		m_fTime = 0.f;
	}
	//
	if (GetAsyncKeyState('U') && m_fTime > 0.5f)
	{
		if (CStatus::m_bRenderCheckStatus == false)
			CStatus::m_bRenderCheckStatus = true;
		else
			CStatus::m_bRenderCheckStatus = false;

		m_fTime = 0.f;
	}
	//레벨업
	if (GetAsyncKeyState('L') && m_fTime > 0.3f)
	{
		g_iLevel += 1;
		g_iAtt += 10;
		g_iDef += 5;
		
		CSoundMgr::GetInstance()->PlaySound(L"LevelUp.wav", CSoundMgr::Channel_Eff);

		m_bLevelUpCheck = true;

		m_fTime = 0.f;
	}


	//Test
	//공격 Bash
	if (GetAsyncKeyState(VK_SPACE) && m_fTime > 0.5f)
	{
		m_eState = PLAYER_BASH;

		m_bAttachCheck = true;

		m_bChangeCheck = true;

		CDamage *Temp = new CDamage(m_tInfo.vPos, 0.2f, 1000, (int)m_tInfo.fCY);
		Temp->Initialize();
		m_vecDamage.push_back(Temp);

		if (g_bCriCheck == true)
		{
			CCritical *Temp_Cri = new CCritical(m_tInfo.vPos, (int)m_tInfo.fCY);
			Temp_Cri->Initialize();
			m_vecCriEffect.push_back(Temp_Cri);
		}

		m_fTime = 0.f;
	}
	//Slash
	if (GetAsyncKeyState(VK_CONTROL) && m_fTime > 0.5f)
	{
		m_eState = PLAYER_SLASH;

		m_bAttachCheck = true;

		m_bChangeCheck = true;

		m_fTime = 0.f;
	}

	//Skill
	if (m_tData.iMp - 1000 > 0)
	{
		if (GetAsyncKeyState('1') && m_fTime > 1.f)
		{
			CGameObject* pEffect =
				CEffectFactory<CEffectBuffer>::CreateEffect(PLAYER_SKILL_CRAY);

			CObjMgr::GetInstance()->AddGameObject(pEffect, OBJ_TYPE_EFFECT);

			m_eState = PLAYER_SKILL;

			m_bAttachCheck = true;

			//
			m_bSkillCheck = true;
			//

			m_bChangeCheck = true;

			m_fTime = 0.f;
		}

		if (GetAsyncKeyState('2') && m_fTime > 1.f)
		{
			CGameObject* pEffect =
				CEffectFactory<CEffectBuffer>::CreateEffect(PLAYER_SKILL_FIREEXPLOSION);

			CObjMgr::GetInstance()->AddGameObject(pEffect, OBJ_TYPE_EFFECT);

			m_eState = PLAYER_SKILL;

			m_bAttachCheck = true;

			//
			m_bSkillCheck = true;
			//

			m_bChangeCheck = true;

			m_fTime = 0.f;
		}

		if (GetAsyncKeyState('3') && m_fTime > 1.f)
		{
			CGameObject* pEffect =
				CEffectFactory<CEffectBuffer>::CreateEffect(PLAYER_SKILL_FREEZE);

			CObjMgr::GetInstance()->AddGameObject(pEffect, OBJ_TYPE_EFFECT);

			m_eState = PLAYER_SKILL;

			m_bAttachCheck = true;

			//
			m_bSkillCheck = true;
			//

			m_bChangeCheck = true;

			m_fTime = 0.f;
		}

		if (GetAsyncKeyState('4') && m_fTime > 1.f)
		{
			CGameObject* pEffect =
				CEffectFactory<CEffectBuffer>::CreateEffect(PLAYER_SKILL_ICEUP);

			CObjMgr::GetInstance()->AddGameObject(pEffect, OBJ_TYPE_EFFECT);

			m_eState = PLAYER_SKILL;

			m_bAttachCheck = true;

			//
			m_bSkillCheck = true;
			//

			m_bChangeCheck = true;

			m_fTime = 0.f;
		}

		if (GetAsyncKeyState('5') && m_fTime > 1.f)
		{
			CGameObject* pEffect =
				CEffectFactory<CEffectBuffer>::CreateEffect(PLAYER_SKILL_PURPLEPUG);

			CObjMgr::GetInstance()->AddGameObject(pEffect, OBJ_TYPE_EFFECT);

			m_eState = PLAYER_SKILL;

			m_bAttachCheck = true;

			//
			m_bSkillCheck = true;
			//

			m_bChangeCheck = true;

			m_fTime = 0.f;
		}

		if (GetAsyncKeyState('6') && m_fTime > 1.f)
		{
			CGameObject* pEffect =
				CEffectFactory<CEffectBuffer>::CreateEffect(PLAYER_SKILL_THUNDERBOLT);

			CObjMgr::GetInstance()->AddGameObject(pEffect, OBJ_TYPE_EFFECT);

			m_eState = PLAYER_SKILL;

			m_bAttachCheck = true;

			//
			m_bSkillCheck = true;
			//

			m_bChangeCheck = true;

			m_fTime = 0.f;
		}

		//전체공격 스킬
		if (GetAsyncKeyState('7') && m_fTime > 1.f)
		{
			CGameObject* pEffect =
				CEffectFactory<CEffectBuffer>::CreateEffect(PLAYER_SKILL_BOOM);

			CObjMgr::GetInstance()->AddGameObject(pEffect, OBJ_TYPE_EFFECT);

			m_eState = PLAYER_SKILL;

			m_bAttachCheck = true;

			//
			m_bSkillCheck = true;
			//

			m_bChangeCheck = true;

			CEffectBuffer::g_bAllSkillCheck = true;

			m_fTime = 0.f;
		}
	}

	//데미지(어색해서 사용X) 

}

void CPlayer::AStarMove(void)
{
	if (m_bAStarCheck == true)
	{
		list<int>* pBestList = AS_Test->GetBestList();

		if (pBestList->empty())
		{
			CSoundMgr::GetInstance()->StopSound(CSoundMgr::Channel_Player);
			m_eState = PLAYER_STAND;
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
		PlayerDir(iMoveIndex);
		//

		if ((*pVecTile)[iMoveIndex]->byOption == 2)
		{
			if(CSceneMgr::GetInstance()->GetSceneType() == SCENE_TOWN2)
				CSceneMgr::GetInstance()->SetChangeScene(SCENE_FIELD);
			else if (CSceneMgr::GetInstance()->GetSceneType() == SCENE_STAGE)
				CSceneMgr::GetInstance()->SetChangeScene(SCENE_BOSSSTAGE);
			else
				CSceneMgr::GetInstance()->SetChangeScene(SCENE_TOWN2);
		}
		
		if ((*pVecTile)[iMoveIndex]->byOption == 3)
		{
			CSceneMgr::GetInstance()->SetChangeScene(SCENE_HOUSE);
		}
		
		if ((*pVecTile)[iMoveIndex]->byOption == 4)
		{
			CSceneMgr::GetInstance()->SetChangeScene(SCENE_STAGE);
		}


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

void CPlayer::MyFrameCheck(void)
{
	if (m_bAttachCheck == true)
	{
		m_tFrame.fIndex += GET_TIME * m_tFrame.fCount * ATTACK_SPEED_PLAYER;

		//때릴때 hp감소 및 플레이어 경직

		if (m_tFrame.fIndex >= 3.f	&&
			m_tFrame.fIndex <= m_tFrame.fMax)
		{
		}

		if (m_tFrame.fIndex >= m_tFrame.fMax)
		{
			m_tFrame.fIndex = 0.f;
			m_eState = PLAYER_STAND;
			m_bChangeCheck = true;
			m_bAttachCheck = false;
		}
	}
	else
	{
		m_tFrame.fIndex += GET_TIME * m_tFrame.fCount * MOTION_SPEED_PLAYER;

		if (m_tFrame.fIndex >= m_tFrame.fMax)
			m_tFrame.fIndex = 0.f;
	}

	if (m_bLevelUpCheck == true)
	{
		m_tLevelUp.fIndex += GET_TIME * m_tLevelUp.fCount * MOTION_SPEED_PLAYER;

		if (m_tLevelUp.fIndex >= m_tLevelUp.fMax)
		{
			m_tLevelUp.fIndex = 0.f;
			m_bLevelUpCheck = false;
		}
	}
}

void CPlayer::PlayerScrollCheck(void)
{
	if (400 > m_tInfo.vPos.x + m_vScroll.x)
	{
		m_vScroll.x += GET_TIME * fSpeed;
	}

	if (WINCX - 400 < m_tInfo.vPos.x + m_vScroll.x)
	{
		m_vScroll.x -= GET_TIME * fSpeed;
	}

	if (300 > m_tInfo.vPos.y + m_vScroll.y)
	{
		m_vScroll.y += GET_TIME * fSpeed;
	}

	if (WINCY - 300 < m_tInfo.vPos.y + m_vScroll.y)
	{
		m_vScroll.y -= GET_TIME * fSpeed;
	}
}

void CPlayer::PlayerDamage(int Damage)
{
	int DamageDef = (Damage - g_iDef);

	if ((g_iHp - DamageDef) > 0)
		g_iHp -= DamageDef;

	CNormEffect *DmgEffectTemp = new CNormEffect(m_tInfo.vPos, EFFECT_PLAYER);
	DmgEffectTemp->Initialize();
	m_vecDmgEffect.push_back(DmgEffectTemp);

	CDamage *DmgTemp = new CDamage(m_tInfo.vPos, 0.2f, DamageDef, (int)m_tInfo.fCY + 60);
	DmgTemp->Initialize();
	m_vecDamage.push_back(DmgTemp);

	CSoundMgr::GetInstance()->PlaySound(L"BeAtt.wav", CSoundMgr::Channel_Eff);
}


void CPlayer::PlayerState(void)
{
	switch (m_eDir)
	{
	case DIR_U:
		m_wstrStateKey = L"Up";
		m_RightCheck = 1.f;
		m_bYSortCheck = false;
		break;
	case DIR_D:
		m_wstrStateKey = L"Down";
		m_RightCheck = 1.f;
		m_bYSortCheck = true;
		break;
	case DIR_L:
		m_wstrStateKey = L"Left";
		m_RightCheck = 1.f;
		m_bYSortCheck = true;
		break;
	case DIR_R:
		m_wstrStateKey = L"Left";
		m_RightCheck = -1.f;
		m_bYSortCheck = true;
		break;
	case DIR_RU:
		m_wstrStateKey = L"LU";
		m_RightCheck = -1.f;
		m_bYSortCheck = false;
		break;
	case DIR_RD:
		m_wstrStateKey = L"LD";
		m_RightCheck = -1.f;
		m_bYSortCheck = true;
		break;
	case DIR_LU:
		m_wstrStateKey = L"LU";
		m_RightCheck = 1.f;
		m_bYSortCheck = false;
		break;
	case DIR_LD:
		m_wstrStateKey = L"LD";
		m_RightCheck = 1.f;
		m_bYSortCheck = true;
		break;
	}

	//상태 변환.
	if (m_bChangeCheck == true)
	{
		switch (m_eState)
		{
		case PLAYER_STAND:
			m_wstrObjKey = L"Stand";
			m_tFrame = FRAME(0.f, 5.f, 5.f);
			break;
		case PLAYER_WALK:
			m_wstrObjKey = L"Walk";
			m_tFrame = FRAME(0.f, 10.f, 10.f);
			break;
		case PLAYER_RUN:
			m_wstrObjKey = L"Run";
			m_tFrame = FRAME(0.f, 10.f, 10.f);
			break;
		case PLAYER_BASH:
			m_wstrObjKey = L"Bash";
			m_tFrame = FRAME(0.f, 6.f, 6.f);
			break;
		case PLAYER_SLASH:
			m_wstrObjKey = L"Slash";
			m_tFrame = FRAME(0.f, 5.f, 5.f);
			break;
		case PLAYER_SKILL:
			m_wstrObjKey = L"Skill";
			m_tFrame = FRAME(0.f, 5.f, 5.f);
			g_iMp -= 500;
			break;
		case PLAYER_DAMAGE:
			//m_wstrObjKey = L"Damage";
			//m_tFrame = FRAME(0.f, 2.f, 2.f);
			//PlayerDamage();
			break;
		}

		m_bChangeCheck = false;
	}
}

void CPlayer::PlayerDir(int MoveIndex)
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

CPlayer::CPlayer(void)
{
}

CPlayer::~CPlayer(void)
{
	Release();
}
