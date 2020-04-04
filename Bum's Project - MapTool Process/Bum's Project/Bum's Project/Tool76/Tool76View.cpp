
// Tool76View.cpp : CTool76View 클래스의 구현
//

#include "stdafx.h"
#include "Tool76.h"

#include "Tool76Doc.h"
#include "Tool76View.h"

#include "MainFrm.h"

#include "Device.h"

#include "SingleTexture.h"

#include "TextureMgr.h"
#include "BackGround.h"

#include "Mouse.h"

#include "MiniView.h"
#include "MapTool.h"
#include "MyForm.h"
#include "Tile.h"
#include "ToolObject.h"
#include "ObjTool.h"
#include "Monster.h"

//타일

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTool76View

//##스크롤 바 상속 처리.
IMPLEMENT_DYNCREATE(CTool76View, CScrollView)						//변경

BEGIN_MESSAGE_MAP(CTool76View, CScrollView)							//변경
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)			//변경
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)		//변경
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CTool76View::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CTool76View 생성/소멸

CTool76View::CTool76View()
{
	// 타일의 처음..
	// TODO: 여기에 생성 코드를 추가합니다.
	m_xyCount.iXCount = 30;
	m_xyCount.iYCount = 100;
}

CTool76View::~CTool76View()
{
	CDevice::GetInstance()->DestroyInstance();
}

BOOL CTool76View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}


void CTool76View::OnDraw(CDC* pDC)
{
	CTool76Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	SetXYCount(m_pTile->GetXYCount());

	SetScrollSizes(MM_TEXT, CSize(TILECX * m_xyCount.iXCount, (TILECY / 2) * m_xyCount.iYCount));

	CDevice::GetInstance()->Render_Begin();

	m_pBackGround->Render();

	m_pToolObject->Render();

	m_pMonster->Render();

	m_pTile->Render();

	CDevice::GetInstance()->Render_End();

}


// CTool76View 인쇄

void CTool76View::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CTool76View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CTool76View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CTool76View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CTool76View::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CTool76View::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CTool76View 진단

#ifdef _DEBUG
void CTool76View::AssertValid() const
{
	CView::AssertValid();
}

void CTool76View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTool76Doc* CTool76View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTool76Doc)));
	return (CTool76Doc*)m_pDocument;
}
#endif //_DEBUG


// CTool76View 메시지 처리기

void CTool76View::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	SetScrollSizes(MM_TEXT, CSize(TILECX * m_xyCount.iXCount, (TILECY / 2) * m_xyCount.iYCount) );

	//MM_TEXT	  : 1:1 픽셀단위로 처리하는 옵션.
	//MM_HIMETRIC : 0.01mm


	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	//AfxGetMainWnd() : 창 테두리를 얻어오는 함수이다.
	//반환타입은 CWnd(부모)포인터형이므로 자식객체의 타입으로 
	//형변환을 해서 사용한다.

	RECT rcWindow;
	

	pMainFrame->GetWindowRect(&rcWindow);
	//전체 프레임의 사이즈를 얻어오는 함수.


	SetRect(&rcWindow, 
		0, 
		0, 
		rcWindow.right - rcWindow.left, 
		rcWindow.bottom - rcWindow.top);
	//프레임의 크기를 0,0기준으로 재조정해주기 위해서 ...


	RECT rcMainView;
	GetClientRect(&rcMainView);
	//순수 뷰창의 크기를 얻어오는 함수.


	//가로 프레임의 길이를 구하자.
	float fX = float(rcWindow.right - rcMainView.right);

	//세로 프레임의 길이를 구하자.
	float fY = float(rcWindow.bottom - rcMainView.bottom);

	pMainFrame->SetWindowPos(
		NULL,		//프레임의 크기를 계산한 상태로 출력할 위치를 결정하는 인자.
		0,
		0,
		int(WINCX + fX),
		int(WINCY + fY),
		SWP_NOZORDER
		);


	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	g_hWnd = m_hWnd;


	if(FAILED(CDevice::GetInstance()->Init3D() ) )
	{
		AfxMessageBox(L"장치 생성 실패!");
	}

	//m_pSingleTexture =  new CSingleTexture;
	//m_pSingleTexture->InsertTexture(L"../Texture/Cube1.png");

	//BackGround//
//////////////////////////////////////////////////////////////////////////
	if( FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Resorce/Stage/BossRoom.png"
		, L"Boss"
		, TEX_SINGLE)))
	{
		AfxMessageBox(L"싱글 이미지 로드 실패!");
	}

	if( FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Resorce/Stage/Dungeon.png"
		, L"Dungeon"
		, TEX_SINGLE)))
	{
		AfxMessageBox(L"싱글 이미지 로드 실패!");
	}

	if( FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Resorce/Stage/Field.png"
		, L"Field"
		, TEX_SINGLE)))
	{
		AfxMessageBox(L"싱글 이미지 로드 실패!");
	}

	if( FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Resorce/Stage/House.png"
		, L"House"
		, TEX_SINGLE)))
	{
		AfxMessageBox(L"싱글 이미지 로드 실패!");
	}

	if( FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Resorce/Stage/Smithy.png"
		, L"Smithy"
		, TEX_SINGLE)))
	{
		AfxMessageBox(L"싱글 이미지 로드 실패!");
	}

	if( FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Resorce/Stage/Smithy2.png"
		, L"Smithy2"
		, TEX_SINGLE)))
	{
		AfxMessageBox(L"싱글 이미지 로드 실패!");
	}

	if( FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Resorce/Stage/Store.png"
		, L"Store"
		, TEX_SINGLE)))
	{
		AfxMessageBox(L"싱글 이미지 로드 실패!");
	}

	if( FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Resorce/Stage/Town.png"
		, L"Town"
		, TEX_SINGLE)))
	{
		AfxMessageBox(L"싱글 이미지 로드 실패!");
	}

	if( FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Resorce/Stage/Town2.png"
		, L"Town2"
		, TEX_SINGLE)))
	{
		AfxMessageBox(L"싱글 이미지 로드 실패!");
	}
//////////////////////////////////////////////////////////////////////////

	//Tile//
//////////////////////////////////////////////////////////////////////////
	if( FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Resorce/Tile/Tile%d.png"
		, L"Back"
		, TEX_MULTI
		, L"Tile"
		, 5)))
	{
		AfxMessageBox(L"멀티 이미지 로드 실패!");
	}
//////////////////////////////////////////////////////////////////////////
	
	//Object//
//////////////////////////////////////////////////////////////////////////
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Resorce/Object/Tree/Tree%d.png"
		, L"Tree"
		, TEX_MULTI
		, L"Object"
		, 50)))
	{
		AfxMessageBox(L"멀티 이미지 로드 실패!");
	}
//////////////////////////////////////////////////////////////////////////

//Monster//
//////////////////////////////////////////////////////////////////////////
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Resorce/Monster/Tool/Mon%d.png"
		, L"Monster"
		, TEX_MULTI
		, L"Monster"
		, 6)))
	{
		AfxMessageBox(L"멀티 이미지 로드 실패!");
	}
//////////////////////////////////////////////////////////////////////////
	
	m_pBackGround = new CBackGround;
	m_pBackGround->Initialize();
	m_pBackGround->SetMainView(this);

	m_pTile = new CTile;
	m_pTile->Initialize();
	m_pTile->SetMainView(this);

	m_pToolObject = new CToolObject;
	m_pToolObject->Initialize();
	m_pToolObject->SetMainView(this);

	m_pMonster = new Monster;
	m_pMonster->Initialize();
	m_pMonster->SetMainView(this);
}

void CTool76View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnLButtonDown(nFlags, point);

	D3DXVECTOR3 vMousePos = CMouse::GetMousePos();
	vMousePos.x += GetScrollPos(0);
	vMousePos.y += GetScrollPos(1);
	vMousePos.z = 0.f;

	((CMainFrame*)AfxGetMainWnd())->GetMyForm()->SetMousePos(vMousePos.x, vMousePos.y);

	CMapTool* pMapTool = ((CMainFrame*)AfxGetMainWnd())->GetMyForm()->GetMapTool();

	
	if (CToolObject::ObjActiveCheck == true)
	{
		m_pToolObject->ClickLButton(vMousePos);
	}
	else if (Monster::MonActiveCheck == true)
	{
		m_pMonster->ClickLButton(vMousePos);
	}
	else
	{
		m_pTile->TileChange(vMousePos, pMapTool->m_iDrawID);
	}

	((CMainFrame*)AfxGetMainWnd())->GetMiniView()->Invalidate(FALSE);

	Invalidate(FALSE);
}

void CTool76View::OnRButtonDown(UINT nFlags, CPoint point)
{
	CView::OnRButtonDown(nFlags, point);

	D3DXVECTOR3 vMousePos = CMouse::GetMousePos();
	vMousePos.x += GetScrollPos(0);
	vMousePos.y += GetScrollPos(1);
	vMousePos.z = 0.f;

	CMapTool* pMapTool = ((CMainFrame*)AfxGetMainWnd())->GetMyForm()->GetMapTool();

	m_pTile->TileChange(vMousePos, 0);

	((CMainFrame*)AfxGetMainWnd())->GetMiniView()->Invalidate(FALSE);

	Invalidate(FALSE);
}

void CTool76View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnKeyDown(nChar, nRepCnt, nFlags);

	switch(nChar)
	{
	case VK_ESCAPE:
		//((CMainFrame*)AfxGetMainWnd())->DestroyWindow();
		dynamic_cast<CMainFrame*>(AfxGetMainWnd())->DestroyWindow();
		break;
	}
}

void CTool76View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CScrollView::OnMouseMove(nFlags, point);
	m_pToolObject->Update();
	m_pMonster->Update();

	//
	D3DXVECTOR3 vMousePos = CMouse::GetMousePos();
	vMousePos.x += GetScrollPos(0);
	vMousePos.y += GetScrollPos(1);
	vMousePos.z = 0.f;

	((CMainFrame*)AfxGetMainWnd())->GetMyForm()
		->SetMousePos(vMousePos.x, vMousePos.y);
	//

	if (GetAsyncKeyState(VK_LBUTTON))
	{
		if (CToolObject::ObjActiveCheck == true)
		{
			//
		}
		else if (Monster::MonActiveCheck == true)
		{
			//
		}
		else 
		{
			OnLButtonDown(nFlags, point);
		}
	}

	if (GetAsyncKeyState(VK_RBUTTON))
		OnRButtonDown(nFlags, point);

	Invalidate(FALSE);
}
