#include "StdAfx.h"
#include "GameObject.h"

//D3DXVECTOR3 CGameObject::m_vScroll;
D3DXVECTOR3 CGameObject::m_vScroll = D3DXVECTOR3(0.f, 0.f, 0.f);

CGameObject::CGameObject(void)
:m_wstrObjKey(L"")
{
	memset(&m_tInfo, 0, sizeof(INFO));
	
	D3DXMatrixIdentity(&m_tInfo.matWorld);

	m_tInfo.vLook = D3DXVECTOR3(1.f, 0.f, 0.f);
}

CGameObject::~CGameObject(void)
{
}
