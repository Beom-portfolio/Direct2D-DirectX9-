// MyForm.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool76.h"
#include "MyForm.h"
#include "BackGround.h"
#include "MainFrm.h"
#include "Tool76View.h"
#include "Tile.h"
#include "TextureMgr.h"
#include "MiniView.h"
#include "ToolObject.h"


// CMyForm

IMPLEMENT_DYNCREATE(CMyForm, CFormView)

void CMyForm::AutoInitialize(void)
{
	//
	CTool76View* pMain = ((CMainFrame*)AfxGetMainWnd())->GetMainView();
	pMain->GetMainTile()->Initialize();
	//
}

CMyForm::CMyForm()
	: CFormView(CMyForm::IDD)
	, m_strXCount(_T(""))
	, m_strYCount(_T(""))
{
	m_MiniSize.fXSize = 0.2f;
	m_MiniSize.fYSize = 0.2f;
	m_MiniSize.fZSize = 0.2f;
}

CMyForm::~CMyForm()
{
}

void CMyForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TILE_X, m_strXCount);
	DDX_Text(pDX, IDC_TILE_Y, m_strYCount);
	DDX_Text(pDX, IDC_XPOS, m_strXPos);
	DDX_Text(pDX, IDC_YPOS, m_strYPos);
}

BEGIN_MESSAGE_MAP(CMyForm, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_TEST, &CMyForm::OnBnClickedButtonTest)
	ON_BN_CLICKED(IDC_BUTTON_MAP_TOOL, &CMyForm::OnBnClickedButtonMapTool)
	ON_BN_CLICKED(IDC_BUTTON_PATH_FIND, &CMyForm::OnBnClickedButtonPathFind)
	ON_BN_CLICKED(IDC_BACK_CHANGE, &CMyForm::OnBnClickedBackChange)
	ON_BN_CLICKED(IDC_TILE_CHANGE, &CMyForm::OnBnClickedTileChange)
	ON_BN_CLICKED(IDC_AUTO_CHANGE, &CMyForm::OnBnClickedAutoChange)
	ON_BN_CLICKED(IDC_MINI_PLUS, &CMyForm::OnBnClickedMiniPlus)
	ON_BN_CLICKED(IDC_MINI_MINUS, &CMyForm::OnBnClickedMiniMinus)
	ON_BN_CLICKED(IDC_OBJTOOL, &CMyForm::OnBnClickedObjtool)
	ON_BN_CLICKED(IDC_SHOW_INDEX, &CMyForm::OnBnClickedShowIndex)
	ON_BN_CLICKED(IDC_MONSTER_TOOL, &CMyForm::OnBnClickedMonsterTool)
END_MESSAGE_MAP()


// CMyForm 진단입니다.

#ifdef _DEBUG
void CMyForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMyForm 메시지 처리기입니다.

void CMyForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	//////////////////////////////////////////////////////////////////////////
	m_StageType = STAGE_FIELD;
}

void CMyForm::OnBnClickedButtonTest()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	//##[17.07.14_04] -> m_UnitTool.GetSafeHwnd() : 객체가 생성되었는지를 판단해주는 함수.
	if(m_UnitTool.GetSafeHwnd() == NULL)
		m_UnitTool.Create(IDD_UNITTOOL);

	m_UnitTool.ShowWindow(SW_SHOW);
	//##[17.07.14_06]
	//UpdateData() : 컨트롤에서 입력받은 정보를 변수에 추가시키기 위해서 사용하는 함수.

	//UpdateData(TRUE);	// : 컨트롤에 있는 정보를 변수에 입력받고 싶다면 TRUE
	//UpdateData(FALSE);	// : 변수의 정보를 컨트롤에 입력하고 싶다면 FALSE
}

void CMyForm::OnBnClickedButtonMapTool()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(m_MapTool.GetSafeHwnd() == NULL)
		m_MapTool.Create(IDD_MAPTOOL);

	m_MapTool.ShowWindow(SW_SHOW);
}

void CMyForm::OnBnClickedButtonPathFind()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if(m_PathFind.GetSafeHwnd() == NULL)
		m_PathFind.Create(IDD_PATHFIND);

	m_PathFind.ShowWindow(SW_SHOW);
}

void CMyForm::OnBnClickedBackChange()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int i = m_StageType;
	++i;
	
	if(i > STAGE_TOWN2)
	{
		i = STAGE_FIELD;
	}

	m_StageType = static_cast<eStageType>(i);

	CBackGround *pBack = ((CMainFrame*)AfxGetMainWnd())->GetMainView()->GetMainBack();
	pBack->SetStageType(static_cast<eStageType>(i));

	CTool76View *pMain = ((CMainFrame*)AfxGetMainWnd())->GetMainView();
	pMain->Invalidate(FALSE);

	CMiniView *pMini = ((CMainFrame*)AfxGetMainWnd())->GetMiniView();
	pMini->Invalidate(FALSE);
}

//TileChange 버튼을 누르면 맵 배경 크기에 맞추어 타일을 조정합니다.

void CMyForm::OnBnClickedTileChange()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	//수동
	GetDlgItemText(IDC_TILE_X, m_strXCount);
	GetDlgItemText(IDC_TILE_Y, m_strYCount);

	m_XYCount.iXCount = _ttoi(m_strXCount);
	m_XYCount.iYCount = _ttoi(m_strYCount);
	//

	CTile *pTile = ((CMainFrame*)AfxGetMainWnd())->GetMainView()->GetMainTile();
	pTile->SetXYCount(m_XYCount);

	AutoInitialize();

	CTool76View *pToolView = ((CMainFrame*)AfxGetMainWnd())->GetMainView();
	pToolView->Invalidate(FALSE);

	CMiniView *pMini = ((CMainFrame*)AfxGetMainWnd())->GetMiniView();
	pMini->Invalidate(FALSE);
}


void CMyForm::OnBnClickedAutoChange()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	//자동
	const TEX_INFO* pStageTex =
		CTextureMgr::GetInstance()->GetTexture(((CMainFrame*)AfxGetMainWnd())
			->GetMainView()
			->GetMainBack()
			->GetBackType());

	// + 1는 혹시 모를 타일 부족에 대비하기 위함.
	m_XYCount.iXCount = int(pStageTex->ImageInfo.Width / TILECX) + 1;	
	m_XYCount.iYCount = int(pStageTex->ImageInfo.Height / (TILECY / 2)) + 1;
	//

	CTile *pTile = ((CMainFrame*)AfxGetMainWnd())->GetMainView()->GetMainTile();
	pTile->SetXYCount(m_XYCount);

	AutoInitialize();

	CTool76View *pToolView = ((CMainFrame*)AfxGetMainWnd())->GetMainView();
	pToolView->Invalidate(FALSE);

	CMiniView *pMini = ((CMainFrame*)AfxGetMainWnd())->GetMiniView();
	pMini->Invalidate(FALSE);
}


void CMyForm::OnBnClickedMiniPlus()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_MiniSize.fXSize += 0.1f;
	m_MiniSize.fYSize += 0.1f;
	m_MiniSize.fZSize += 0.1f;

	//백그라운드적용
	((CMainFrame*)AfxGetMainWnd())->GetMainView()->GetMainBack()
		->SetMiniSize(m_MiniSize);

	//타일적용
	((CMainFrame*)AfxGetMainWnd())->GetMainView()->GetMainTile()
		->SetMiniSize(m_MiniSize);

	//오브젝트적용
	((CMainFrame*)AfxGetMainWnd())->GetMainView()->GetMainToolObj()
		->SetMiniSize(m_MiniSize);

	//미니맵에 적용(바로)
	CMiniView *pMini = ((CMainFrame*)AfxGetMainWnd())->GetMiniView();
	pMini->Invalidate(FALSE);
}


void CMyForm::OnBnClickedMiniMinus()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_MiniSize.fXSize -= 0.1f;
	m_MiniSize.fYSize -= 0.1f;
	m_MiniSize.fZSize -= 0.1f;

	//백그라운드적용
	((CMainFrame*)AfxGetMainWnd())->GetMainView()->GetMainBack()
		->SetMiniSize(m_MiniSize);

	//타일적용
	((CMainFrame*)AfxGetMainWnd())->GetMainView()->GetMainTile()
		->SetMiniSize(m_MiniSize);

	//오브젝트적용
	((CMainFrame*)AfxGetMainWnd())->GetMainView()->GetMainToolObj()
		->SetMiniSize(m_MiniSize);

	//미니맵에 적용(바로)
	CMiniView *pMini = ((CMainFrame*)AfxGetMainWnd())->GetMiniView();
	pMini->Invalidate(FALSE);
}


void CMyForm::OnBnClickedObjtool()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_ObjTool.GetSafeHwnd() == NULL)
	{
		m_ObjTool.Create(IDD_OBJTOOL);
	}

	m_ObjTool.ShowWindow(SW_SHOW);
}


void CMyForm::OnBnClickedShowIndex()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CTile *pMainTile = ((CMainFrame*)AfxGetMainWnd())->GetMainView()->GetMainTile();

	if (pMainTile->GetTextRender() == false)
	{
		pMainTile->SetTextRender(true);
	}
	else
	{
		pMainTile->SetTextRender(false);
	}

	((CMainFrame*)AfxGetMainWnd())->GetMainView()->Invalidate(FALSE);
}

void CMyForm::OnBnClickedMonsterTool()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_MonTool.GetSafeHwnd() == NULL)
	{
		m_MonTool.Create(IDD_MONSTERTOOL);
	}

	m_MonTool.ShowWindow(SW_SHOW);
}
