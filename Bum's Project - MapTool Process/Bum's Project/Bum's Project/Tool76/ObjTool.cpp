// ObjTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool76.h"
#include "ObjTool.h"
#include "Include.h"

#include "MainFrm.h"
#include "Tool76View.h"
#include "BackGround.h"
#include "Tile.h"
#include "MiniView.h"
#include "ToolObject.h"
#include "afxdialogex.h"


void CObjTool::HorizontalScroll(void)
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

// CObjTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CObjTool, CDialog)

CObjTool::CObjTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_OBJTOOL, pParent)
	, m_iDrawID(0)
{

}

CObjTool::~CObjTool()
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

void CObjTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_IMAGE_PATH_OBJ, m_listBoxImagePath);
	DDX_Control(pDX, IDC_PICTURE_OBJ, m_Picture);
}


BEGIN_MESSAGE_MAP(CObjTool, CDialog)
	ON_LBN_SELCHANGE(IDC_LIST_IMAGE_PATH_OBJ, &CObjTool::OnLbnSelchangeListImagePath)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CObjTool::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CObjTool::OnBnClickedButtonLoad)
END_MESSAGE_MAP()


// CObjTool 메시지 처리기입니다.


void CObjTool::OnLbnSelchangeListImagePath()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

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
		->GetMainToolObj()->SetDrawID(m_iDrawID);

	CToolObject::ObjActiveCheck = true;

	UpdateData(FALSE);
}

void CObjTool::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

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

void CObjTool::OnBnClickedButtonSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
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

	Dlg.m_ofn.lpstrInitialDir = L"..\\Data\\Object";

	vector<OBJINFO*>* pVecToolObj = ((CMainFrame*)AfxGetMainWnd())->GetMainView()->GetMainToolObj()->GetToolObj();

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

	for (size_t i = 0; i < pVecToolObj->size(); ++i)
	{
		(*pVecToolObj)[i]->bAlpa = false;
		(*pVecToolObj)[i]->fCX = 236;
		(*pVecToolObj)[i]->fCY = 239;
		(*pVecToolObj)[i]->rc = RectMake(
			(*pVecToolObj)[i]->vPos.x,
			(*pVecToolObj)[i]->vPos.y,
			(*pVecToolObj)[i]->fCX,
			(*pVecToolObj)[i]->fCY - 20
		);
		WriteFile(hFile, (*pVecToolObj)[i], sizeof(OBJINFO), &dwByte, NULL);
	}

	CloseHandle(hFile);
}


void CObjTool::OnBnClickedButtonLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

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

	Dlg.m_ofn.lpstrInitialDir = L"..\\Data\\Object";

	vector<OBJINFO*>* pVecToolObj = ((CMainFrame*)AfxGetMainWnd())->GetMainView()->GetMainToolObj()->GetToolObj();
	
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

	for (size_t i = 0; i < pVecToolObj->size(); ++i)
	{
		safe_delete((*pVecToolObj)[i]);
	}
	pVecToolObj->clear();

	while (true)
	{
		OBJINFO* pObjData = new OBJINFO;

		ReadFile(hFile, pObjData, sizeof(OBJINFO), &dwByte, NULL);

		if (dwByte == 0)
		{
			safe_delete(pObjData);
			break;
		}

		pVecToolObj->push_back(pObjData);
	}

	CloseHandle(hFile);

	CTool76View* pMain = ((CMainFrame*)AfxGetMainWnd())->GetMainView();

	pMain->Invalidate(FALSE);

	CMiniView *pMini = ((CMainFrame*)AfxGetMainWnd())->GetMiniView();
	
	pMini->Invalidate(FALSE);
}
