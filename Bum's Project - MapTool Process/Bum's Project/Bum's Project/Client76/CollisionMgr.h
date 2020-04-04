#pragma once

#include "Include.h"

class CGameObject;
class CCollisionMgr
{
	DECLARE_SINGLETON(CCollisionMgr)
//몬스터, 플레이어간 충돌
//스킬, 플레이어간 충돌
//나중에..
public:
	//bool WarpPlayer(void);
	eCollisionDir CollisionRect(CGameObject* _pObj, eObjectType Type);
	bool MonPlayerCollisionRect(CGameObject* _pObj);
	bool MouseCollision(D3DXVECTOR3 _pObj, eObjectType Type);
	bool MouseCollisionCheck(D3DXVECTOR3 _pObj);
	bool MouseBossCollision(D3DXVECTOR3 _pObj);
	bool MouseBossCollisionCheck(D3DXVECTOR3 _pObj);
	bool PlayerAttackRangeCollisionRect(CGameObject * _pObj);
	bool PlayerBossBulletCollisionCheck(CGameObject * _pObj);
//인벤
public:
	bool InvenDragCheckCollisionCheck(RECT _pObj, D3DXVECTOR3 Mouse);
	bool InvenItemSwapCheck(CGameObject * Dest, D3DXVECTOR3 Mouse);
	bool ShopSellCheck(CGameObject * Dest, D3DXVECTOR3 Mouse);
public:
	CCollisionMgr();
	~CCollisionMgr();
};

