#include "StdAfx.h"
#include "BackGround.h"
#include "TextureMgr.h"
#include "Device.h"
#include "Mouse.h"
#include "TimeMgr.h"
#include "SceneMgr.h"

CBackGround::CBackGround(void)
{
}

CBackGround::~CBackGround(void)
{
	Release();
}

HRESULT	CBackGround::Initialize(void)
{
	LoadBackGround();

	fSpeed = 500.f;

	m_RenderType = RENDER_BACKGROUND;

	return S_OK;
}
 int		CBackGround::Update(void)
{
	MouseScrollCheck();

	return 0;
}
 void	CBackGround::Render(void)
{

	 D3DXMATRIX matTrans;

	 const TEX_INFO* pBackTex =
		 CTextureMgr::GetInstance()->GetTexture(szBackType);

	 D3DXMatrixTranslation(&matTrans
		 , m_BackMainInfo->vPos.x + m_vScroll.x	//0 : x
		 , m_BackMainInfo->vPos.y + m_vScroll.y	//1 : y
		 , 0.f);


	 CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

	 CDevice::GetInstance()->GetSprite()->Draw(
		 pBackTex->pTexture,
		 NULL,
		 &D3DXVECTOR3(0.f
		 , 0.f
		 , 0.f),
		 NULL,
		 D3DCOLOR_ARGB(255, 255, 255, 255)
	 );

	 return;


}
 void	CBackGround::Release(void)
{
	 m_BackInfo.iBackType = NULL;
}

 void CBackGround::LoadBackGround(void)
 {
	 //불러올때 타일수, 타일정보들도 여기에서 한꺼번에 불러오겠다.
	 m_BackMainInfo = new BACK;

	 DWORD dwByte = 0;
	
	 eSceneType eType = CSceneMgr::GetInstance()->GetSceneType();

	 int i = eType;

	 float fX = 0.f;
	 float fY = 0.f;

	 float fCX = 0.f;
	 float fCY = 0.f;
	
	 m_BackMainInfo->vPos = D3DXVECTOR3(fX, fY, 0.f);
	 m_BackMainInfo->StageType = static_cast<eStageType>(i);
	
	 switch (eType)
	 {
	 case SCENE_FIELD:
		 szBackType = L"Field";
		 fCX = 3268.f;
		 fCY = 1712.f;
		 break;

	 case SCENE_STAGE:
		 szBackType = L"Dungeon";
		 fCX = 3418.f;
		 fCY = 1730.f;
		 break;

	 case SCENE_BOSSSTAGE:
		 szBackType = L"Boss";
		 fCX = 2668.f;
		 fCY = 1328.f;
		 break;

	 case SCENE_HOUSE:
		 szBackType = L"House";
		 fCX = 1174.f;
		 fCY = 882.f;
		 break;

	 case SCENE_SMITHY:
		 szBackType = L"Smithy";
		 fCX = 1181.f;
		 fCY = 775.f;
		 break;

	 case SCENE_SMITHY2:
		 szBackType = L"Smithy2";
		 fCX = 1394.f;
		 fCY = 868.f;
		 break;

	 case SCENE_STORE:
		 szBackType = L"Store";
		 fCX = 1277.f;
		 fCY = 991.f;
		 break;

	 case SCENE_TOWN:
		 szBackType = L"Town";
		 fCX = 3502.f;
		 fCY = 2048.f;
		 break;

	 case SCENE_TOWN2:
		 szBackType = L"Town2";
		 fCX = 1600.f;
		 fCY = 1200.f;
		 break;
	 }

	 Release();

	 //이미지의 정보만 가지고옴

	 m_BackMainInfo->vSize = D3DXVECTOR3((fCX / 2.f), (fCY / 2.f), 0.f);
 }

 void CBackGround::MouseScrollCheck(void)
 {
	// D3DXVECTOR3 vMousePos = CMouse::GetMousePos();

	// float fTime = CTimeMgr::GetInstance()->GetTime();
	// 
	////fTime	+=  CTimeMgr::GetInstance()->GetTime();
	////0.08871238 * 스피드

	// //if(fTime > 2)
	//	 //int iA = 10;

	// if(0 > vMousePos.x)
	// {
	//	m_vScroll.x += fTime * fSpeed;
	// }
	// 
	// if(WINCX < vMousePos.x)
	// {
	//	m_vScroll.x -= fTime * fSpeed;
	// }

	// if(0 > vMousePos.y)
	// {
	//	 m_vScroll.y += fTime * fSpeed;
	// }

	// if(WINCY < vMousePos.y)
	// {
	//	 m_vScroll.y -= fTime * fSpeed;
	// }

 }

