#include "stdafx.h"
#include "EffectBuffer.h"
#include "Player.h"
#include "ObjMgr.h"
#include "TimeMgr.h"
#include "Device.h"
#include "GameObject.h"
#include "Monster.h"
#include "ObjMgr.h"
#include "Boss.h"
#include "Player.h"
#include "ShakeMgr.h"

bool CEffectBuffer::g_bAllSkillCheck = false;

void CEffectBuffer::WorldMatrixCheck(INFO & rInfo)
{
	if (g_bAllSkillCheck == false)
	{
		D3DXMATRIX matTrans, matParent;

		D3DXMatrixTranslation(&matTrans, rInfo.vPos.x, rInfo.vPos.y, 0.f);

		if (CObjMgr::GetInstance()->FindGameObject<CMonster>() != NULL)
		{
			for (size_t i = 0; i < pMonvector->size(); ++i)
			{
				if ((*pMonvector)[i]->GetTargetCheck() == true)
				{
					matParent = (*pMonvector)[i]->GetInfo()->matWorld;
				}
			}

			for (size_t i = 0; i < pMonBackvector->size(); ++i)
			{
				if ((*pMonBackvector)[i]->GetTargetCheck() == true)
				{
					matParent = (*pMonBackvector)[i]->GetInfo()->matWorld;
				}
			}
		}

		if (pBoss != NULL)
		{
			if (pBoss->GetTargetCheck() == true)
			{
				matParent = pBoss->GetInfo()->matWorld;
			}
		}

		rInfo.matWorld = matTrans * matParent;
	}
	else
	{
		rInfo.vPos = CObjMgr::GetInstance()->FindGameObject<CPlayer>()->GetNormInfo().vPos;

		//전체 공격 스킬
		D3DXMATRIX matScale, matTrans;

		D3DXMatrixScaling(&matScale, 4.5f, 4.5f, 0.f);
		D3DXMatrixTranslation(&matTrans, 
			rInfo.vPos.x + CGameObject::m_vScroll.x,
			rInfo.vPos.y + CGameObject::m_vScroll.y, 0.f);

		rInfo.matWorld = matScale * matTrans;
	}
}

void CEffectBuffer::FrameMove(void)
{
	
	if (m_bOnceCheck == true)
	{
		if (g_bAllSkillCheck == false)
		{
			m_tFrame.fIndex += GET_TIME * m_tFrame.fCount * 0.7f;

			//몬스터 경직

			if (m_tFrame.fIndex >= m_tFrame.fMax)
			{
				if (CObjMgr::GetInstance()->FindGameObject<CMonster>() != NULL)
				{
					for (size_t i = 0; i < pMonvector->size(); ++i)
					{
						if ((*pMonvector)[i]->GetTargetCheck() == true)
						{
							if ((*pMonvector)[i]->GetMonsterHitCheck() == false)
							{
								(*pMonvector)[i]->SetMonsterHitCheck(true);
							}
						}
					}

					for (size_t i = 0; i < pMonBackvector->size(); ++i)
					{
						if ((*pMonBackvector)[i]->GetTargetCheck() == true)
						{
							if ((*pMonBackvector)[i]->GetMonsterHitCheck() == false)
							{
								(*pMonBackvector)[i]->SetMonsterHitCheck(true);
							}
						}
					}
				}

				if (pBoss != NULL)
				{
					if (pBoss->GetTargetCheck() == true)
					{
						if (pBoss->GetMonsterHitCheck() == false)
						{
							pBoss->SetMonsterHitCheck(true);
						}
					}
				}

				m_tFrame.fIndex = 0.f;
				m_bOnceCheck = false;
				g_bAllSkillCheck = false;
			}
		}
		else
		{
			m_tFrame.fIndex += GET_TIME * m_tFrame.fCount * 0.5f;

			CShakeMgr::GetInstance()->SetShake(SHAKE_RANDOM, 25.f, D3DXVECTOR3(1.f, 1.f, 0.f));
			CShakeMgr::GetInstance()->Progress();

			if (CObjMgr::GetInstance()->FindGameObject<CMonster>() != NULL && m_myTime > 0.3f)
			{
				for (size_t i = 0; i < pMonvector->size(); ++i)
				{

					(*pMonvector)[i]->SetMonsterHitCheck(true);

				}

				for (size_t i = 0; i < pMonBackvector->size(); ++i)
				{

					(*pMonBackvector)[i]->SetMonsterHitCheck(true);

				}

				m_myTime = 0.f;
			}


			if (pBoss != NULL && m_myTime > 0.2f)
			{
				pBoss->SetMonsterHitCheck(true);

				vector<CMonster*> *TempJelly = CObjMgr::GetInstance()->FindGameObject<CBoss>()->GetJelly();

				for (size_t i = 0; i < TempJelly->size(); ++i)
				{
					(*TempJelly)[i]->SetMonsterHitCheck(true);
				}

				m_myTime = 0.f;
			}


			//

			if (m_tFrame.fIndex >= m_tFrame.fMax)
			{

				if (CObjMgr::GetInstance()->FindGameObject<CMonster>() != NULL)
				{
					for (size_t i = 0; i < pMonvector->size(); ++i)
					{

						(*pMonvector)[i]->SetMonsterHitCheck(true);

					}

					for (size_t i = 0; i < pMonBackvector->size(); ++i)
					{

						(*pMonBackvector)[i]->SetMonsterHitCheck(true);

					}
				}

				if (pBoss != NULL)
				{
					pBoss->SetMonsterHitCheck(true);
				}

				m_tFrame.fIndex = 0.f;
				m_bOnceCheck = false;
				g_bAllSkillCheck = false;
			}
		}
	}
}


HRESULT CEffectBuffer::Initialize(eSkill SkillType)
{
	m_pPlayer = CObjMgr::GetInstance()->FindGameObject<CPlayer>();

	m_iPlayerAttack = m_pPlayer->GetAttack();

	m_fTime = 2.5f;

	m_fRotateAngle = 0.f;

	switch (SkillType)
	{
	case PLAYER_SKILL_CRAY:
		m_wstrStateKey = L"Cray";
		m_tFrame = FRAME(0.f, 8.f, 8.f);
		m_iMagicalDamage = int(m_iPlayerAttack * 1.2f);
		CSoundMgr::GetInstance()->PlaySound(L"Falling.wav", CSoundMgr::Channel_Eff);
		break;
	case PLAYER_SKILL_FIREEXPLOSION:
		m_wstrStateKey = L"FireExplosion";
		m_tFrame = FRAME(0.f, 9.f, 9.f);
		m_iMagicalDamage = int(m_iPlayerAttack * 1.4f);
		CSoundMgr::GetInstance()->PlaySound(L"Explosion.wav", CSoundMgr::Channel_Eff);
		break;
	case PLAYER_SKILL_FREEZE:
		m_wstrStateKey = L"Freeze";
		m_tFrame = FRAME(0.f, 7.f, 7.f);
		m_iMagicalDamage = int(m_iPlayerAttack * 1.6f);
		CSoundMgr::GetInstance()->PlaySound(L"Ice.wav", CSoundMgr::Channel_Eff);
		break;
	case PLAYER_SKILL_ICEUP:
		m_wstrStateKey = L"IceUp";
		m_tFrame = FRAME(0.f, 20.f, 20.f);
		m_iMagicalDamage = int(m_iPlayerAttack * 2.2f);
		CSoundMgr::GetInstance()->PlaySound(L"Spike.wav", CSoundMgr::Channel_Eff);
		break;
	case PLAYER_SKILL_PURPLEPUG:
		m_wstrStateKey = L"PurPlePog";
		m_tFrame = FRAME(0.f, 11.f, 11.f);
		m_iMagicalDamage = int(m_iPlayerAttack * 1.1f);
		CSoundMgr::GetInstance()->PlaySound(L"Smoke.wav", CSoundMgr::Channel_Eff);
		break;
	case PLAYER_SKILL_THUNDERBOLT:
		m_wstrStateKey = L"ThunderBolt";
		m_tFrame = FRAME(0.f, 13.f, 13.f);
		m_iMagicalDamage = int(m_iPlayerAttack * 1.8f);
		CSoundMgr::GetInstance()->PlaySound(L"Electric.wav", CSoundMgr::Channel_Eff);
		break;
	case PLAYER_SKILL_BOOM:
		m_wstrStateKey = L"Boom";
		m_tFrame = FRAME(0.f, 19.f, 19.f);
		m_iMagicalDamage = int(m_iPlayerAttack * 0.8f);
		CSoundMgr::GetInstance()->PlaySound(L"Volcano.wav", CSoundMgr::Channel_Eff);
		break;
	}

	m_pPlayer->SetPlayerMagicalDamage(m_iMagicalDamage);

	m_bOnceCheck = true;

	m_myTime = 0.f;

	return S_OK;
}

int CEffectBuffer::Update(INFO & rInfo)
{
	pMonster = CObjMgr::GetInstance()->FindGameObject<CMonster>();
	pBoss = CObjMgr::GetInstance()->FindGameObject<CBoss>();

	pMonvector = pMonster->GetMonsterVec();
	pMonBackvector = pMonster->GetMonsterBackVec();

	WorldMatrixCheck(rInfo);
	FrameMove();

	m_myTime += GET_TIME;
	m_fTime -= GET_TIME;


	if (m_fTime < 0.f)
		return 1;

	return 0;
}

void CEffectBuffer::Render(void)
{
	if(m_bOnceCheck == true)
		CEffectBridge::Render();
}

void CEffectBuffer::Release(void)
{
}

CEffectBuffer::CEffectBuffer()
{
}


CEffectBuffer::~CEffectBuffer()
{
	Release();
}
