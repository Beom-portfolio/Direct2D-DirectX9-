
// Tool76View.cpp : CTool76View Ŭ������ ����
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

//Ÿ��

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTool76View

//##��ũ�� �� ��� ó��.
IMPLEMENT_DYNCREATE(CTool76View, CScrollView)						//����

BEGIN_MESSAGE_MAP(CTool76View, CScrollView)							//����
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)			//����
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)		//����
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CTool76View::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CTool76View ����/�Ҹ�

CTool76View::CTool76View()
{
	// Ÿ���� ó��..
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	m_xyCount.iXCount = 30;
	m_xyCount.iYCount = 100;
}

CTool76View::~CTool76View()
{
	CDevice::GetInstance()->DestroyInstance();
}

BOOL CTool76View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

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


// CTool76View �μ�

void CTool76View::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CTool76View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CTool76View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CTool76View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
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


// CTool76View ����

#ifdef _DEBUG
void CTool76View::AssertValid() const
{
	CView::AssertValid();
}

void CTool76View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTool76Doc* CTool76View::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTool76Doc)));
	return (CTool76Doc*)m_pDocument;
}
#endif //_DEBUG


// CTool76View �޽��� ó����

void CTool76View::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	SetScrollSizes(MM_TEXT, CSize(TILECX * m_xyCount.iXCount, (TILECY / 2) * m_xyCount.iYCount) );

	//MM_TEXT	  : 1:1 �ȼ������� ó���ϴ� �ɼ�.
	//MM_HIMETRIC : 0.01mm


	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	//AfxGetMainWnd() : â �׵θ��� ������ �Լ��̴�.
	//��ȯŸ���� CWnd(�θ�)���������̹Ƿ� �ڽİ�ü�� Ÿ������ 
	//����ȯ�� �ؼ� ����Ѵ�.

	RECT rcWindow;
	

	pMainFrame->GetWindowRect(&rcWindow);
	//��ü �������� ����� ������ �Լ�.


	SetRect(&rcWindow, 
		0, 
		0, 
		rcWindow.right - rcWindow.left, 
		rcWindow.bottom - rcWindow.top);
	//�������� ũ�⸦ 0,0�������� ���������ֱ� ���ؼ� ...


	RECT rcMainView;
	GetClientRect(&rcMainView);
	//���� ��â�� ũ�⸦ ������ �Լ�.


	//���� �������� ���̸� ������.
	float fX = float(rcWindow.right - rcMainView.right);

	//���� �������� ���̸� ������.
	float fY = float(rcWindow.bottom - rcMainView.bottom);

	pMainFrame->SetWindowPos(
		NULL,		//�������� ũ�⸦ ����� ���·� ����� ��ġ�� �����ϴ� ����.
		0,
		0,
		int(WINCX + fX),
		int(WINCY + fY),
		SWP_NOZORDER
		);


	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	g_hWnd = m_hWnd;


	if(FAILED(CDevice::GetInstance()->Init3D() ) )
	{
		AfxMessageBox(L"��ġ ���� ����!");
	}

	//m_pSingleTexture =  new CSingleTexture;
	//m_pSingleTexture->InsertTexture(L"../Texture/Cube1.png");

	//BackGround//
//////////////////////////////////////////////////////////////////////////
	if( FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Resorce/Stage/BossRoom.png"
		, L"Boss"
		, TEX_SINGLE)))
	{
		AfxMessageBox(L"�̱� �̹��� �ε� ����!");
	}

	if( FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Resorce/Stage/Dungeon.png"
		, L"Dungeon"
		, TEX_SINGLE)))
	{
		AfxMessageBox(L"�̱� �̹��� �ε� ����!");
	}

	if( FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Resorce/Stage/Field.png"
		, L"Field"
		, TEX_SINGLE)))
	{
		AfxMessageBox(L"�̱� �̹��� �ε� ����!");
	}

	if( FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Resorce/Stage/House.png"
		, L"House"
		, TEX_SINGLE)))
	{
		AfxMessageBox(L"�̱� �̹��� �ε� ����!");
	}

	if( FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Resorce/Stage/Smithy.png"
		, L"Smithy"
		, TEX_SINGLE)))
	{
		AfxMessageBox(L"�̱� �̹��� �ε� ����!");
	}

	if( FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Resorce/Stage/Smithy2.png"
		, L"Smithy2"
		, TEX_SINGLE)))
	{
		AfxMessageBox(L"�̱� �̹��� �ε� ����!");
	}

	if( FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Resorce/Stage/Store.png"
		, L"Store"
		, TEX_SINGLE)))
	{
		AfxMessageBox(L"�̱� �̹��� �ε� ����!");
	}

	if( FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Resorce/Stage/Town.png"
		, L"Town"
		, TEX_SINGLE)))
	{
		AfxMessageBox(L"�̱� �̹��� �ε� ����!");
	}

	if( FAILED(CTextureMgr::GetInstance()->InsertTexture(L"../Texture/Resorce/Stage/Town2.png"
		, L"Town2"
		, TEX_SINGLE)))
	{
		AfxMessageBox(L"�̱� �̹��� �ε� ����!");
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
		AfxMessageBox(L"��Ƽ �̹��� �ε� ����!");
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
		AfxMessageBox(L"��Ƽ �̹��� �ε� ����!");
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
		AfxMessageBox(L"��Ƽ �̹��� �ε� ����!");
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

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
