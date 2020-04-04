// MiniView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool76.h"
#include "MiniView.h"

#include "afxwin.h"
#include "Device.h"
#include "BackGround.h"
#include "MainFrm.h"
#include "Tool76View.h"
#include "Tile.h"
#include "ToolObject.h"

// CMiniView

IMPLEMENT_DYNCREATE(CMiniView, CView)

CMiniView::CMiniView()
{

}

CMiniView::~CMiniView()
{
}

BEGIN_MESSAGE_MAP(CMiniView, CView)
END_MESSAGE_MAP()


// CMiniView �׸����Դϴ�.

void CMiniView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.


	CBackGround* pBack = ((CMainFrame*)AfxGetMainWnd())->GetMainView()->GetMainBack();
	CTile* pTile = ((CMainFrame*)AfxGetMainWnd())->GetMainView()->GetMainTile();
	CToolObject* pToolObj = ((CMainFrame*)AfxGetMainWnd())->GetMainView()->GetMainToolObj();

	//SetScrollSizes(MM_TEXT, CSize((TILECX * pTile->GetMiniSize().fXSize) * pTile->GetXYCount().iXCount
	//						, ((TILECY * pTile->GetMiniSize().fYSize) / 2) * pTile->GetXYCount().iYCount));

	CDevice::GetInstance()->Render_Begin();

	pBack->MiniMapRender();
	pToolObj->MiniMapRender();
	pTile->MiniMapRender();

	CDevice::GetInstance()->Render_End(m_hWnd);
}

// CMiniView �����Դϴ�.

#ifdef _DEBUG
void CMiniView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CMiniView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMiniView �޽��� ó�����Դϴ�.
