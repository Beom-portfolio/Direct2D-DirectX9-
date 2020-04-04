// UnitTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool76.h"
#include "UnitTool.h"


void CUnitTool::Release()
{
	map<CString, UNIT_DATA*>::iterator iter;
	map<CString, UNIT_DATA*>::iterator iter_end;

	iter	 = m_mapUnitData.begin();
	iter_end = m_mapUnitData.end();

	for(iter; iter != iter_end; ++iter)
	{
		safe_delete(iter->second);
	}
	m_mapUnitData.clear();
}

// CUnitTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CUnitTool, CDialog)

CUnitTool::CUnitTool(CWnd* pParent /*=NULL*/)
	: CDialog(CUnitTool::IDD, pParent)
	, m_strName(_T(""))
	, m_iAtt(0)
	, m_iHp(0)
	, bStartRadioButtonCheck(true)
{

}

CUnitTool::~CUnitTool()
{
	Release();
	
}

void CUnitTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CHAR_NAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_ATTACK, m_iAtt);
	DDV_MinMaxInt(pDX, m_iAtt, 0, 6000);
	DDX_Text(pDX, IDC_EDIT_HP, m_iHp);
	DDX_Control(pDX, IDC_LIST_UNIT_DATA, m_listboxUnitData);
	//DDX_Control(pDX, IDC_RADIO1, m_iRadio1);

	DDX_Control(pDX, IDC_RADIO1, m_iRadio[0]);
	DDX_Control(pDX, IDC_RADIO2, m_iRadio[1]);
	DDX_Control(pDX, IDC_RADIO3, m_iRadio[2]);

	if(bStartRadioButtonCheck)
	{
		bStartRadioButtonCheck = false;
		m_iRadio[0].SetCheck(TRUE);
	}
	
	DDX_Control(pDX, IDC_BUTTON_BITMAP, m_BitmapButton);

	HBITMAP hBitmap = (HBITMAP)LoadImage(NULL,
								L"../Texture/JusinLogo1.bmp",
								IMAGE_BITMAP,
								100,
								100,
								LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	m_BitmapButton.SetBitmap(hBitmap);
}


BEGIN_MESSAGE_MAP(CUnitTool, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CUnitTool::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CUnitTool::OnBnClickedButtonDelete)
	ON_LBN_SELCHANGE(IDC_LIST_UNIT_DATA, &CUnitTool::OnLbnSelchangeListUnitData)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CUnitTool::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CUnitTool::OnBnClickedButtonLoad)
END_MESSAGE_MAP()


// CUnitTool 메시지 처리기입니다.

void CUnitTool::OnBnClickedButtonAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);

	map<CString, UNIT_DATA*>::iterator iter;

	iter = m_mapUnitData.find(m_strName);

	if(iter != m_mapUnitData.end())
	{
		AfxMessageBox(L"중복된 이름이 있습니다!");
		return ;
	}


	UNIT_DATA* pUnitData = new UNIT_DATA;

	pUnitData->wstrName = m_strName;
	pUnitData->iHp		= m_iHp;
	pUnitData->iAtt		= m_iAtt;

	for(int i = 0; i < 3; ++i)
	{
		if(m_iRadio[i].GetCheck())
		{
			pUnitData->byJobIndex = i;
			break;
		}
	}
	
	pUnitData->byItem = 0;

	if( ((CButton*)GetDlgItem(IDC_CHECK_WEAPON))->GetCheck() )
		pUnitData->byItem |= ITEM_WEAPON;

	if( ((CButton*)GetDlgItem(IDC_CHECK_ARMOR))->GetCheck() )
		pUnitData->byItem |= ITEM_ARMOR;

	if( ((CButton*)GetDlgItem(IDC_CHECK_POTION))->GetCheck() )
		pUnitData->byItem |= ITEM_POTION;

	UpdateData(FALSE);

	m_listboxUnitData.AddString(m_strName);
	m_mapUnitData.insert(make_pair(m_strName, pUnitData));
}

void CUnitTool::OnBnClickedButtonDelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	UpdateData(TRUE);

	CString strSelectName;		//내가 선택한 항목의 이름을 보관할 변수.

	//현재 내가 몇번째 항목을 선택했는지를 보관할 변수.
	int iSelectIndex = m_listboxUnitData.GetCurSel();

	if(iSelectIndex == -1)
		return;

	m_listboxUnitData.GetText(iSelectIndex, strSelectName);


	map<CString, UNIT_DATA*>::iterator iter;

	iter = m_mapUnitData.find(strSelectName);

	if(iter == m_mapUnitData.end())
	{
		AfxMessageBox(L"찾는이름이 없습니다.");
		return ;
	}

	safe_delete(iter->second);
	m_mapUnitData.erase(strSelectName);

	m_listboxUnitData.DeleteString(iSelectIndex);

	UpdateData(FALSE);

}

void CUnitTool::OnLbnSelchangeListUnitData()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	
	//##[17.07.14_08]
	CString strSelectName;		//내가 선택한 항목의 이름을 보관할 변수.

	//현재 내가 몇번째 항목을 선택했는지를 보관할 변수.
	int iSelectIndex = m_listboxUnitData.GetCurSel();

	if(iSelectIndex == -1)
		return;

	m_listboxUnitData.GetText(iSelectIndex, strSelectName);

	
	map<CString, UNIT_DATA*>::iterator iter;

	iter = m_mapUnitData.find(strSelectName);

	if(iter == m_mapUnitData.end())
	{
		AfxMessageBox(L"찾는이름이 없습니다.");
		return ;
	}

	m_strName = iter->second->wstrName.c_str();
	m_iAtt	  = iter->second->iAtt;
	m_iHp	  = iter->second->iHp;

	for(int i = 0; i < 3; ++i)
	{
		//일단 모든 라디오 버튼을 모두 꺼준다.
		m_iRadio[i].SetCheck(FALSE);
	}

	m_iRadio[iter->second->byJobIndex].SetCheck(TRUE);


	//((CButton*)GetDlgItem(IDC_CHECK_WEAPON))->SetCheck(FALSE);

	for(int i = IDC_CHECK_WEAPON; i <= IDC_CHECK_POTION; ++i)
	{
		((CButton*)GetDlgItem(i))->SetCheck(FALSE);
	}

	if(iter->second->byItem & ITEM_WEAPON)
		((CButton*)GetDlgItem(IDC_CHECK_WEAPON))->SetCheck(TRUE);

	if(iter->second->byItem & ITEM_ARMOR)
		((CButton*)GetDlgItem(IDC_CHECK_ARMOR))->SetCheck(TRUE);

	if(iter->second->byItem & ITEM_POTION)
		((CButton*)GetDlgItem(IDC_CHECK_POTION))->SetCheck(TRUE);


	UpdateData(FALSE);
}

void CUnitTool::OnBnClickedButtonSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	//##[17.07.17_01] : 파일다이얼로그
	CFileDialog		Dlg(
		FALSE,		//모드설정 : TRUE(로드), FALSE(저장)
		L"dat",		//확장자명
		L"*.dat",	//최초에 띄어줄 파일이름
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,	//이름이 동일한 중복파일에 대해서 처리하는 옵션값.
		L"*.dat",	//파일 형식에 띄어줄 확장자명
		this		
		);


	if(Dlg.DoModal() == IDCANCEL)
		return;
	//DoModal : 프로세스에 대한 독점권이라고 생각하면된다.
	//		    여러개의 창이 열렸을때 모달은 독점.

	Dlg.m_ofn.lpstrInitialDir = L"..\\Data";		//저장시킬 경로를 지정한다.


	HANDLE hFile = CreateFile(
		Dlg.GetPathName(),		//파일 경로.
		GENERIC_WRITE,	//어떤 모드로? : 쓰기전용
		NULL,		//공유모드
		NULL,
		CREATE_ALWAYS,	//파일옵션 : 파일이 있으면 덮어쓰기 -> 없으면 새로 만들라는 인자값.
		FILE_ATTRIBUTE_NORMAL,		//기본값으로 파일을 생성하라는옵션.
		NULL
		);


	DWORD dwByte = 0;

	for(map<CString, UNIT_DATA*>::iterator iter = m_mapUnitData.begin();
		iter != m_mapUnitData.end(); ++iter)
	{
		WriteFile(hFile, iter->second, sizeof(UNIT_DATA), &dwByte, NULL);
	}

	CloseHandle(hFile);
}

void CUnitTool::OnBnClickedButtonLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);

	CFileDialog		Dlg(
		TRUE,		//모드설정 : TRUE(로드), FALSE(저장)
		L"dat",		//확장자명
		L"*.dat",	//최초에 띄어줄 파일이름
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,	//이름이 동일한 중복파일에 대해서 처리하는 옵션값.
		L"*.dat",	//파일 형식에 띄어줄 확장자명
		this		
		);


	if(Dlg.DoModal() == IDCANCEL)
		return;
	
	Release();							//기존에 있던 데이터 모두 반환.
	m_listboxUnitData.ResetContent();		//리스트박스 초기화.


	Dlg.m_ofn.lpstrInitialDir = L"..\\Data";		//로드할 경로.


	HANDLE hFile = CreateFile(
		Dlg.GetPathName(),		//파일 경로.
		GENERIC_READ,	//어떤 모드로? : 읽기
		NULL,		//공유모드
		NULL,
		OPEN_EXISTING,	
		FILE_ATTRIBUTE_NORMAL,		//기본값으로 파일을 생성하라는옵션.
		NULL
		);


	DWORD dwByte = 0;

	while(true)
	{
		UNIT_DATA* pUnitData = new UNIT_DATA;

		ReadFile(hFile, pUnitData, sizeof(UNIT_DATA), &dwByte, NULL);

		if(dwByte == 0)
		{
			safe_delete(pUnitData);
			break;
		}

		m_mapUnitData.insert(make_pair(pUnitData->wstrName.c_str(), pUnitData));
		m_listboxUnitData.AddString(pUnitData->wstrName.c_str());
	}
	

	CloseHandle(hFile);
}
