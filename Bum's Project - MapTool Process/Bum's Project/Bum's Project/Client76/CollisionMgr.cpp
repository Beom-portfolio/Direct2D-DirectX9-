#include "stdafx.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "GameObject.h"
#include "SceneMgr.h"
#include "Monster.h"
#include "BlueWolf.h"
#include "Boss.h"
#include "Player.h"
#include "Shop.h"
#include "UserInterface.h"

IMPLEMENT_SINGLETON(CCollisionMgr)

//몬스터 , 플레이어
eCollisionDir CCollisionMgr::CollisionRect(CGameObject * _pObj, eObjectType Type)
{
	INFO& rDestInfo = (_pObj->GetNormInfo());

	list<CGameObject*>::iterator iter = 
		CObjMgr::GetInstance()->GetList()[Type].begin();
	list<CGameObject*>::iterator iter_end =
		CObjMgr::GetInstance()->GetList()[Type].end();

	RECT rc = { 0 };

	for (iter; iter != iter_end; ++iter)
	{
		INFO& rSourceInfo = (*iter)->GetNormInfo();

		if (IntersectRect(&rc, _pObj->GetRect(), (*iter)->GetRect()))
		{
			SetRect(&rc, 0, 0, rc.right - rc.left, rc.bottom - rc.top);

			if (rDestInfo.vPos.y < rSourceInfo.vPos.y)
			{
				if (rc.right > rc.bottom)		//위쪽에서 부딪힘.
				{
					return COL_DIR_U;
				}
			}
			else
			{
				//아래쪽에서.
				if (rc.right > rc.bottom)		//내가 아래쪽.
				{
					return COL_DIR_D;
				}
			}

			if (rDestInfo.vPos.x > rSourceInfo.vPos.x)		//내가 오른쪽
			{
				return COL_DIR_R;
			}
			else	//내가 왼쪽.
			{
				return COL_DIR_L;
			}
		}
	}

	return COL_NONE;
}



bool CCollisionMgr::MonPlayerCollisionRect(CGameObject * _pObj)
{
	//Player
	CGameObject* pPlayer = CObjMgr::GetInstance()->GetList()[OBJ_TYPE_PLAYER].front();

	RECT rc = { 0 };

	if (IntersectRect(&rc, _pObj->GetRect(), pPlayer->GetRect()))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CCollisionMgr::PlayerAttackRangeCollisionRect(CGameObject * _pObj)
{
	//Player
	CGameObject* pPlayer = CObjMgr::GetInstance()->GetList()[OBJ_TYPE_PLAYER].front();

	RECT rc = { 0 };

	if (IntersectRect(&rc, _pObj->GetAttackRange(), pPlayer->GetRect()))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CCollisionMgr::PlayerBossBulletCollisionCheck(CGameObject * _pObj)
{
	CPlayer* pPlayer = CObjMgr::GetInstance()->FindGameObject<CPlayer>();

	D3DXVECTOR3 PlayervPos = pPlayer->GetNormInfo().vPos;

	POINT PlayerPos = POINT{(long)PlayervPos.x, (long)PlayervPos.y};

	RECT *rc = { 0 };

	rc = _pObj->GetRect();

	if (PtInRect(rc, PlayerPos))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CCollisionMgr::MouseCollision(D3DXVECTOR3 _pObj, eObjectType Type)
{
	int   Check = 0;

	POINT MousePos = POINT{ (long)_pObj.x, (long)_pObj.y };

	CMonster* Temp = CObjMgr::GetInstance()->FindGameObject<CMonster>();

	if (Temp != NULL)
	{
		vector<CMonster*>* Monvector = Temp->GetMonsterVec();
		vector<CMonster*>* MonBackvector = Temp->GetMonsterBackVec();

		RECT *rc = { 0 };

		for (size_t i = 0; i < MonBackvector->size(); ++i)
		{
			rc = (*MonBackvector)[i]->GetRect();

			if (PtInRect(rc, MousePos))
			{
				(*MonBackvector)[i]->setTargetCheck(true);
				++Check;
			}
			else
			{
				(*MonBackvector)[i]->setTargetCheck(false);
			}
		}

		for (size_t i = 0; i < Monvector->size(); ++i)
		{
			rc = (*Monvector)[i]->GetRect();

			if (PtInRect(rc, MousePos))
			{
				(*Monvector)[i]->setTargetCheck(true);
				++Check;
			}
			else
			{
				(*Monvector)[i]->setTargetCheck(false);
			}
		}

		if (Check > 0)
			return true;
		else if (Check == 0)
			return false;
	}

	return false;
}

bool CCollisionMgr::MouseCollisionCheck(D3DXVECTOR3 _pObj)
{
	int   Check = 0;

	POINT MousePos = POINT{ (long)_pObj.x, (long)_pObj.y };

	CMonster* Temp = CObjMgr::GetInstance()->FindGameObject<CMonster>();

	if (Temp != NULL)
	{
		vector<CMonster*>* Monvector = Temp->GetMonsterVec();
		vector<CMonster*>* MonBackvector = Temp->GetMonsterBackVec();

		RECT *rc = { 0 };

		for (size_t i = 0; i < MonBackvector->size(); ++i)
		{
			rc = (*MonBackvector)[i]->GetRect();

			if (PtInRect(rc, MousePos))
			{
				++Check;
				//break;
			}
		}

		for (size_t i = 0; i < Monvector->size(); ++i)
		{
			rc = (*Monvector)[i]->GetRect();

			if (PtInRect(rc, MousePos))
			{
				++Check;
				//break;
			}
		}

		if (Check > 0)
			return true;
		else if (Check == 0)
			return false;
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////////

bool CCollisionMgr::MouseBossCollision(D3DXVECTOR3 _pObj)
{
	POINT MousePos = POINT{ (long)_pObj.x, (long)_pObj.y };

	CBoss* Temp = CObjMgr::GetInstance()->FindGameObject<CBoss>();

	if (Temp != NULL)
	{
		RECT *rc = { 0 };

		rc = Temp->GetRect();

		if (PtInRect(rc, MousePos))
		{
			Temp->setTargetCheck(true);
			return true;
		}
		else
		{
			Temp->setTargetCheck(false);
		}
	}

	return false;
}

bool CCollisionMgr::MouseBossCollisionCheck(D3DXVECTOR3 _pObj)
{
	POINT MousePos = POINT{ (long)_pObj.x, (long)_pObj.y };

	CBoss* Temp = CObjMgr::GetInstance()->FindGameObject<CBoss>();

	if (Temp != NULL)
	{
		RECT *rc = { 0 };
		
		rc = Temp->GetRect();

		if (PtInRect(rc, MousePos))
		{
			return true;
		}

		return false;
	}

	return false;
}

bool CCollisionMgr::InvenDragCheckCollisionCheck(RECT _pObj, D3DXVECTOR3 Mouse)
{
	POINT MousePos = POINT{ (long)Mouse.x, (long)Mouse.y };

	RECT *rc = { 0 };

	rc = &_pObj;

	if (PtInRect(rc, MousePos))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CCollisionMgr::InvenItemSwapCheck(CGameObject * Dest, D3DXVECTOR3 Mouse)
{
	POINT  MousePos = POINT{ (long)Mouse.x, (long)Mouse.y };

	RECT *Dest_rc = { 0 };

	Dest_rc = Dest->GetRect();

	if (PtInRect(Dest_rc, MousePos))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CCollisionMgr::ShopSellCheck(CGameObject * Dest, D3DXVECTOR3 Mouse)
{
	POINT  MousePos = POINT{ (long)Mouse.x, (long)Mouse.y };

	RECT *ShopRect = { 0 };

	ShopRect = Dest->GetRect();

	if (PtInRect(ShopRect, MousePos))
	{
		return true;
	}
	else
	{
		return false;
	}
}

CCollisionMgr::CCollisionMgr()
{

}


CCollisionMgr::~CCollisionMgr()
{
}
