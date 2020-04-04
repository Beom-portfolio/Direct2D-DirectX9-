#pragma once

#include "Include.h"

class CGameObject;
class CCollisionMgr
{
	DECLARE_SINGLETON(CCollisionMgr)
//����, �÷��̾ �浹
//��ų, �÷��̾ �浹
//���߿�..
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
//�κ�
public:
	bool InvenDragCheckCollisionCheck(RECT _pObj, D3DXVECTOR3 Mouse);
	bool InvenItemSwapCheck(CGameObject * Dest, D3DXVECTOR3 Mouse);
	bool ShopSellCheck(CGameObject * Dest, D3DXVECTOR3 Mouse);
public:
	CCollisionMgr();
	~CCollisionMgr();
};

