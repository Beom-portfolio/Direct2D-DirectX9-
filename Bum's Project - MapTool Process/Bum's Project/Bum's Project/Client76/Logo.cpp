#include "StdAfx.h"
#include "Logo.h"
#include "SceneMgr.h"
#include "ObjMgr.h"
#include "TextureMgr.h"
#include "Device.h"
#include "Stage.h"
#include "TextureMgr.h"
#include "objmgr.h"
#include "Factory.h"
#include "BackGround.h"
#include "Tile.h"
#include "Tree.h"
#include "Player.h"
#include "UserInterface.h"
#include "HpBar.h"
#include "MpBar.h"
#include "Cursor.h"
#include "Portal.h"

CLogo::CLogo(void)
{
	//memset(&m_Crt, 0, sizeof(CRITICAL_SECTION));
}

CLogo::~CLogo(void)
{
	Release();
}

unsigned int CLogo::ImageLoadThreadFunc(void * pArg)
{
	//새로운 스레드가 읽을수 있는 영역.

	//리소스정보를 로드하게 된다.
	CLogo* pLogo = (CLogo*)pArg;

	int iA = 10;

	EnterCriticalSection(&pLogo->GetCrt());

	if (FAILED(CTextureMgr::GetInstance()->LoadImagePath(L"../Data/ImagePath.txt")))
	{
		ERROR_MSG(L"멀티텍스쳐 이미지 로드 실패!");
		return E_FAIL;
	}

	CTextureMgr::GetInstance()->m_wstrCurrentPath = L"이미지 로드 완료!";

	LeaveCriticalSection(&pLogo->GetCrt());

	//다시 설명 : 메모리 릭 주의사항있어요.
	//_endthreadex(0);


	return 0;
}

CRITICAL_SECTION CLogo::GetCrt(void)
{
	return m_Crt;
}

HRESULT CLogo::Initialize(void)
{
	if (FAILED(CTextureMgr::GetInstance()->LoadImagePath(L"../Data/ImagePath.txt")))
	{
		ERROR_MSG(L"멀티텍스쳐 이미지 로드 실패!");
		return E_FAIL;
	}

	//마우스
	CObjMgr::GetInstance()->AddGameObject(
		CFactory<CCursor>::CreateGameObject(),
		OBJ_TYPE_CURSOR);

	//InitializeCriticalSection(&m_Crt);

	/*m_hThread = (HANDLE)_beginthreadex(
		0,
		0,
		ImageLoadThreadFunc,
		this,
		0,
		0);*/

	return S_OK;
}

int CLogo::Update(void)
{
	CObjMgr::GetInstance()->Update();

	if (GetAsyncKeyState(VK_RETURN))
	{
		//WaitForSingleObject(m_hThread, INFINITE);

		//CloseHandle(m_hThread);

		//DeleteCriticalSection(&m_Crt);

		CSceneMgr::GetInstance()->SetChangeScene(SCENE_TOWN2);
	}

	//씬이 변경되더라도.. 씬영역에서의 기능은 마무리 되어야한다.

	return 0;
}

void CLogo::Render(void)
{
	D3DXMATRIX matTrans;

	const TEX_INFO* pLogoPngTex =
		CTextureMgr::GetInstance()->GetTexture(
			L"Logo");

	if (pLogoPngTex == NULL)
	{
		ERROR_MSG(L"로고 이미지 X");
		return;
	}

	D3DXMatrixTranslation(&matTrans
		, 0.f
		, 0.f
		, 0.f);

	CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

	CDevice::GetInstance()->GetSprite()->Draw(
		pLogoPngTex->pTexture,
		NULL,
		&D3DXVECTOR3(0.f, 0.f, 0.f),
		NULL,
		D3DCOLOR_ARGB(255, 255, 255, 255)
	);


	CObjMgr::GetInstance()->Render();

	TCHAR Enter[MIDDLE_STR] = L"";

	wsprintf(Enter, L"PRESS ENTER TO START!!");

	D3DXMatrixTranslation(&matTrans, 290, 510, 0);

	CDevice::GetInstance()->GetSprite()->SetTransform(&matTrans);

	CDevice::GetInstance()->GetFont()->DrawTextW(
		CDevice::GetInstance()->GetSprite(),
		Enter,
		lstrlen(Enter),
		NULL,
		NULL,
		D3DCOLOR_ARGB(255, 0, 0, 0)
	);

}

void CLogo::Release(void)
{
	//CObjMgr::GetInstance()->Release();
	//CObjMgr::GetInstance()->Release(OBJ_TYPE_PLAYER);
}

