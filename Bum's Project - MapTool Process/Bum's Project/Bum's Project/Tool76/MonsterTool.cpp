// MonsterTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool76.h"
#include "MonsterTool.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "Tool76View.h"
#include "BackGround.h"
#include "Tile.h"
#include "MiniView.h"
#include "Monster.h"
#include "afxdialogex.h"

// CMonsterTool ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CMonsterTool, CDialog)

void CMonsterTool::HorizontalScroll(void)
{
	CString strName;
	CSize	Size;

	int iCX = 0;

	CDC* pDc = m_listBoxImagePath.GetDC();


	for (int i = 0; i < m_listBoxImagePath.GetCount(); ++i)
	{
		m_listBoxImagePath.GetText(i, strName);

		Size = pDc->GetTextExtent(strName);

		if (Size.cx > iCX)
		{
			iCX = Size.cx;
		}
	}

	m_listBoxImagePath.ReleaseDC(pDc);

	if (m_listBoxImagePath.GetHorizontalExtent() < iCX)
	{
		m_listBoxImagePath.SetHorizontalExtent(iCX);
	}
}

CMonsterTool::CMonsterTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MONSTERTOOL, pParent)
{

}

CMonsterTool::~CMonsterTool()
{
	map<CString, CImage*>::iterator  iter = m_ObjPngImage.begin();
	map<CString, CImage*>::iterator  iter_end = m_ObjPngImage.end();

	for (iter; iter != iter_end; ++iter)
	{
		iter->second->Destroy();
		safe_delete(iter->second);
	}
	if (!m_ObjPngImage.empty())
		m_ObjPngImage.clear();
}

void CMonsterTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MONSTER_LIST, m_listBoxImagePath);
	DDX_Control(pDX, IDC_PICTURE_MONSTER, m_Picture);
}

void CMonsterTool::OnLbnSelchangeListImagePath()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData(TRUE);

	CString strName;

	int iSelectIndex = m_listBoxImagePath.GetCurSel();

	if (iSelectIndex < 0)
		return;

	m_listBoxImagePath.GetText(iSelectIndex, strName);

	map<CString, CImage*>::iterator iter;

	iter = m_ObjPngImage.find(strName);

	if (iter == m_ObjPngImage.end())
		return;

	m_Picture.SetBitmap(*iter->second);


	int i = 0;

	for (i = 0; i < strName.GetLength(); ++i)
	{
		if (isdigit(strName[i]) != 0)
		{
			break;
		}
	}

	strName.Delete(0, i);

	m_iDrawID = _tstoi(strName);

	((CMainFrame*)AfxGetMainWnd())->GetMainView()
		->GetMainMon()->SetDrawID(m_iDrawID);

	Monster::MonActiveCheck = true;

	UpdateData(FALSE);
}

void CMonsterTool::OnDropFiles(HDROP hDropInfo)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	UpdateData(TRUE);

	int iFileCount = DragQueryFile(hDropInfo, -1, NULL, 0);

	TCHAR szFullPath[MAX_PATH] = L"";

	for (int i = 0; i < iFileCount; ++i)
	{
		DragQueryFile(hDropInfo, i, szFullPath, MAX_PATH);

		std::wstring wstrRelativePath = RelativePath(szFullPath);

		CString strImageName;


		strImageName = PathFindFileName(wstrRelativePath.c_str());



		PathRemoveExtension((LPWSTR)strImageName.operator LPCWSTR());



		map<CString, CImage*>::iterator iter;

		iter = m_ObjPngImage.find(strImageName);

		if (iter == m_ObjPngImage.end())
		{
			CImage* pPngImage = new CImage;

			pPngImage->Load(wstrRelativePath.c_str());

			m_ObjPngImage.insert(make_pair(strImageName, pPngImage));
		}


		m_listBoxImagePath.AddString(strImageName);
	}


	HorizontalScroll();


	CDialog::OnDropFiles(hDropInfo);


	UpdateData(FALSE);
}


BEGIN_MESSAGE_MAP(CMonsterTool, CDialog)
	ON_LBN_SELCHANGE(IDC_MONSTER_LIST, &CMonsterTool::OnLbnSelchangeListImagePath)
	ON_STN_CLICKED(IDC_PICTURE_MONSTER, &CMonsterTool::OnStnClickedPictureMonster)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CMonsterTool::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CMonsterTool::OnBnClickedButtonLoad)
END_MESSAGE_MAP()


// CMonsterTool �޽��� ó�����Դϴ�.


void CMonsterTool::OnStnClickedPictureMonster()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CMonsterTool::OnBnClickedButtonSave()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	CFileDialog		Dlg(
		FALSE,
		L"dat",
		L"*.dat",
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"*.dat",
		this
	);

	if (Dlg.DoModal() == IDCANCEL)
		return;

	Dlg.m_ofn.lpstrInitialDir = L"..\\Data\\Monster";

	vector<MONINFO*>* pVecToolMon = ((CMainFrame*)AfxGetMainWnd())->GetMainView()->GetMainMon()->GetToolMon();

	HANDLE hFile = CreateFile(
		Dlg.GetPathName(),
		GENERIC_WRITE,
		NULL,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	DWORD dwByte = 0;

	for (size_t i = 0; i < pVecToolMon->size(); ++i)
	{
		WriteFile(hFile, (*pVecToolMon)[i], sizeof(MONINFO), &dwByte, NULL);
	}

	CloseHandle(hFile);
}


void CMonsterTool::OnBnClickedButtonLoad()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	CFileDialog Dlg(
		TRUE,
		L"dat",
		L"*.dat",
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"*.dat",
		this
	);

	if (Dlg.DoModal() == IDCANCEL)
		return;

	Dlg.m_ofn.lpstrInitialDir = L"..\\Data\\Monster";

	vector<MONINFO*>* pVecToolMon = ((CMainFrame*)AfxGetMainWnd())->GetMainView()->GetMainMon()->GetToolMon();

	DWORD dwByte = 0;

	HANDLE hFile = CreateFile(
		Dlg.GetPathName(),
		GENERIC_READ,
		NULL,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	for (size_t i = 0; i < pVecToolMon->size(); ++i)
	{
		safe_delete((*pVecToolMon)[i]);
	}
	pVecToolMon->clear();

	while (true)
	{
		MONINFO* pObjData = new MONINFO;

		ReadFile(hFile, pObjData, sizeof(MONINFO), &dwByte, NULL);

		if (dwByte == 0)
		{
			safe_delete(pObjData);
			break;
		}

		pVecToolMon->push_back(pObjData);
	}

	CloseHandle(hFile);

	CTool76View* pMain = ((CMainFrame*)AfxGetMainWnd())->GetMainView();

	pMain->Invalidate(FALSE);

	CMiniView *pMini = ((CMainFrame*)AfxGetMainWnd())->GetMiniView();

	pMini->Invalidate(FALSE);
}
