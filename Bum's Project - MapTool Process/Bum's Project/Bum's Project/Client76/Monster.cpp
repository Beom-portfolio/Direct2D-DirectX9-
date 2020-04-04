#include "stdafx.h"
#include "Monster.h"
#include "SceneMgr.h"
#include "Mouse.h"
#include "TimeMgr.h"
#include "Device.h"
#include "TextureMgr.h"
#include "BlueWolf.h"
#include "ObjMgr.h"
#include "Player.h"
#include "RedWolf.h"
#include "DarkCow.h"
#include "Jelly.h"
#include "CreedWizard.h"

HRESULT CMonster::Initialize(void)
{
	m_fTime = 0.f;

	LoadMonster();

	m_RenderType = RENDER_WORLD;

	return S_OK;
}

int CMonster::Update(void)
{

	/*for (size_t i = 0; i < m_vecMon.size(); ++i)
	{
		m_vecMon[i]->Update();
	}

	for (size_t i = 0; i < m_vecMon_Back.size(); ++i)
	{
		m_vecMon_Back[i]->Update();
	}*/
	vector<CMonster*>::iterator iter = m_vecMon.begin();
	vector<CMonster*>::iterator iter_end = m_vecMon.end();

	for (auto i = iter; i != iter_end;)
	{
		if ((*i)->Update() == 1)
		{
			++i;
		}
		else
		{
			i = m_vecMon.erase(i);
		}

		iter_end = m_vecMon.end();
	}

	///
	vector<CMonster*>::iterator iter_B = m_vecMon_Back.begin();
	vector<CMonster*>::iterator iter_end_B = m_vecMon_Back.end();

	for (auto i = iter_B; i != iter_end_B;)
	{
		if ((*i)->Update() == 1)
		{
			++i;
		}
		else
		{
			i = m_vecMon_Back.erase(i);
		}

		iter_end_B = m_vecMon_Back.end();
	}

	YSorting();

	return 0;
}

void CMonster::Render(void)
{

	for (size_t i = 0; i < m_vecMon.size(); ++i)
	{
		m_vecMon[i]->Render();
	}
}

void CMonster::Release(void)
{
	for (size_t i = 0; i < m_vecMon.size(); ++i)
	{
		safe_delete(m_vecMon[i]);
	}
	m_vecMon.clear();
}

void CMonster::YSorting(void)
{
	vector<CMonster*>::iterator iter_back = m_vecMon_Back.begin();
	vector<CMonster*>::iterator iter_back_end = m_vecMon_Back.end();

	vector<CMonster*>::iterator iter_front = m_vecMon.begin();
	vector<CMonster*>::iterator iter_front_end = m_vecMon.end();

	CPlayer* m_pPlayer = CObjMgr::GetInstance()->FindGameObject<CPlayer>();

	//菊率 -> 第率
	if (!(m_vecMon.empty()))
	{
		for (auto i = iter_front;
			i != iter_front_end;)
		{
			INFO PlayerInfo = m_pPlayer->GetNormInfo();
			INFO MonsterInfo = (*i)->GetNormInfo();

			if ((PlayerInfo.vPos.y + (PlayerInfo.fCY / 2.f)) >
				MonsterInfo.vPos.y + (MonsterInfo.fCY / 2.f))
			{
				//持绊
				m_vecMon_Back.push_back(*i);
				//瘤快绊
				i = m_vecMon.erase(i);

				//iter_front = m_vecMon.begin();
				iter_front_end = m_vecMon.end();
			}
			else
			{
				++i;
			}
		}
	}


	//第率 -> 菊率
	if (!(m_vecMon_Back.empty()))
	{
		iter_back = m_vecMon_Back.begin();
		iter_back_end = m_vecMon_Back.end();

		for (auto i = iter_back;
			i != iter_back_end;)
		{

			INFO PlayerInfo = m_pPlayer->GetNormInfo();
			INFO MonsterInfo = (*i)->GetNormInfo();

			if ((PlayerInfo.vPos.y + (PlayerInfo.fCY / 2.f)) <
				MonsterInfo.vPos.y + (MonsterInfo.fCY / 2.f))
			{
				//持绊
				m_vecMon.push_back(*i);
				//瘤快绊
				i = m_vecMon_Back.erase(i);

				//iter_back = m_vecMon_Back.begin();
				iter_back_end = m_vecMon_Back.end();
			}
			else
			{
				++i;
			}
		}
	}
}

void CMonster::RenderBack(void)
{
	for (size_t i = 0; i < m_vecMon_Back.size(); ++i)
	{
		m_vecMon_Back[i]->Render();
	}
}

void CMonster::LoadMonster(void)
{
	DWORD dwByte = 0;

	HANDLE hFile;

	eSceneType eType = CSceneMgr::GetInstance()->GetSceneType();

	switch (eType)
	{
	case SCENE_STAGE:
		hFile = CreateFile(
			L"../Data/Monster/Stage.dat",
			GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);
		break;
	}

	Release();

	while (true)
	{
		MONINFO* pMonData = new MONINFO;

		ReadFile(hFile, pMonData, sizeof(MONINFO), &dwByte, NULL);

		if (dwByte == 0)
		{
			safe_delete(pMonData);
			break;
		}

		CMonster* pVecData = MonsterType(pMonData->byDrawID);

		pVecData->m_tInfo.vPos = pMonData->vPos;
		pVecData->m_tInfo.vDir = pMonData->vDir;
		pVecData->m_tInfo.vSize = pMonData->vSize;

		m_vecMon.push_back(pVecData);
	}
}

CMonster* CMonster::MonsterType(BYTE Type)
{
	eMonsterType MonType = static_cast<eMonsterType>(Type);

	CMonster*    MonTempData;

	switch (MonType)
	{
	case MON_TYPE_BLUEWOLF:
		MonTempData = new CBlueWolf;
		MonTempData->Initialize();
		break;
	case MON_TYPE_REDWOLF:
		MonTempData = new CRedWolf;
		MonTempData->Initialize();
		break;
	case MON_TYPE_DARKCOW:
		MonTempData = new CDarkCow;
		MonTempData->Initialize();
		break;
	case MON_TYPE_JELLY:
		MonTempData = new CJelly;
		MonTempData->Initialize();
		break;
	case MON_TYPE_CREEDWIZARD:
		MonTempData = new CCreedWizard;
		MonTempData->Initialize();
		break;
	}

	return MonTempData;
}

CMonster::CMonster()
{
}


CMonster::~CMonster()
{
	Release();
}
