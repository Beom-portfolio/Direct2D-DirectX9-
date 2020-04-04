// MyForm.cpp : ���� �����Դϴ�.
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


// CMyForm �����Դϴ�.

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


// CMyForm �޽��� ó�����Դϴ�.

void CMyForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	//////////////////////////////////////////////////////////////////////////
	m_StageType = STAGE_FIELD;
}

void CMyForm::OnBnClickedButtonTest()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	//##[17.07.14_04] -> m_UnitTool.GetSafeHwnd() : ��ü�� �����Ǿ������� �Ǵ����ִ� �Լ�.
	if(m_UnitTool.GetSafeHwnd() == NULL)
		m_UnitTool.Create(IDD_UNITTOOL);

	m_UnitTool.ShowWindow(SW_SHOW);
	//##[17.07.14_06]
	//UpdateData() : ��Ʈ�ѿ��� �Է¹��� ������ ������ �߰���Ű�� ���ؼ� ����ϴ� �Լ�.

	//UpdateData(TRUE);	// : ��Ʈ�ѿ� �ִ� ������ ������ �Է¹ް� �ʹٸ� TRUE
	//UpdateData(FALSE);	// : ������ ������ ��Ʈ�ѿ� �Է��ϰ� �ʹٸ� FALSE
}

void CMyForm::OnBnClickedButtonMapTool()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(m_MapTool.GetSafeHwnd() == NULL)
		m_MapTool.Create(IDD_MAPTOOL);

	m_MapTool.ShowWindow(SW_SHOW);
}

void CMyForm::OnBnClickedButtonPathFind()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	if(m_PathFind.GetSafeHwnd() == NULL)
		m_PathFind.Create(IDD_PATHFIND);

	m_PathFind.ShowWindow(SW_SHOW);
}

void CMyForm::OnBnClickedBackChange()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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

//TileChange ��ư�� ������ �� ��� ũ�⿡ ���߾� Ÿ���� �����մϴ�.

void CMyForm::OnBnClickedTileChange()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	
	//����
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	//�ڵ�
	const TEX_INFO* pStageTex =
		CTextureMgr::GetInstance()->GetTexture(((CMainFrame*)AfxGetMainWnd())
			->GetMainView()
			->GetMainBack()
			->GetBackType());

	// + 1�� Ȥ�� �� Ÿ�� ������ ����ϱ� ����.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_MiniSize.fXSize += 0.1f;
	m_MiniSize.fYSize += 0.1f;
	m_MiniSize.fZSize += 0.1f;

	//��׶�������
	((CMainFrame*)AfxGetMainWnd())->GetMainView()->GetMainBack()
		->SetMiniSize(m_MiniSize);

	//Ÿ������
	((CMainFrame*)AfxGetMainWnd())->GetMainView()->GetMainTile()
		->SetMiniSize(m_MiniSize);

	//������Ʈ����
	((CMainFrame*)AfxGetMainWnd())->GetMainView()->GetMainToolObj()
		->SetMiniSize(m_MiniSize);

	//�̴ϸʿ� ����(�ٷ�)
	CMiniView *pMini = ((CMainFrame*)AfxGetMainWnd())->GetMiniView();
	pMini->Invalidate(FALSE);
}


void CMyForm::OnBnClickedMiniMinus()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_MiniSize.fXSize -= 0.1f;
	m_MiniSize.fYSize -= 0.1f;
	m_MiniSize.fZSize -= 0.1f;

	//��׶�������
	((CMainFrame*)AfxGetMainWnd())->GetMainView()->GetMainBack()
		->SetMiniSize(m_MiniSize);

	//Ÿ������
	((CMainFrame*)AfxGetMainWnd())->GetMainView()->GetMainTile()
		->SetMiniSize(m_MiniSize);

	//������Ʈ����
	((CMainFrame*)AfxGetMainWnd())->GetMainView()->GetMainToolObj()
		->SetMiniSize(m_MiniSize);

	//�̴ϸʿ� ����(�ٷ�)
	CMiniView *pMini = ((CMainFrame*)AfxGetMainWnd())->GetMiniView();
	pMini->Invalidate(FALSE);
}


void CMyForm::OnBnClickedObjtool()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (m_ObjTool.GetSafeHwnd() == NULL)
	{
		m_ObjTool.Create(IDD_OBJTOOL);
	}

	m_ObjTool.ShowWindow(SW_SHOW);
}


void CMyForm::OnBnClickedShowIndex()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (m_MonTool.GetSafeHwnd() == NULL)
	{
		m_MonTool.Create(IDD_MONSTERTOOL);
	}

	m_MonTool.ShowWindow(SW_SHOW);
}
