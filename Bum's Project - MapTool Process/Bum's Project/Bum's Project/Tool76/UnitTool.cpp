// UnitTool.cpp : ���� �����Դϴ�.
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

// CUnitTool ��ȭ �����Դϴ�.

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


// CUnitTool �޽��� ó�����Դϴ�.

void CUnitTool::OnBnClickedButtonAdd()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData(TRUE);

	map<CString, UNIT_DATA*>::iterator iter;

	iter = m_mapUnitData.find(m_strName);

	if(iter != m_mapUnitData.end())
	{
		AfxMessageBox(L"�ߺ��� �̸��� �ֽ��ϴ�!");
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	
	UpdateData(TRUE);

	CString strSelectName;		//���� ������ �׸��� �̸��� ������ ����.

	//���� ���� ���° �׸��� �����ߴ����� ������ ����.
	int iSelectIndex = m_listboxUnitData.GetCurSel();

	if(iSelectIndex == -1)
		return;

	m_listboxUnitData.GetText(iSelectIndex, strSelectName);


	map<CString, UNIT_DATA*>::iterator iter;

	iter = m_mapUnitData.find(strSelectName);

	if(iter == m_mapUnitData.end())
	{
		AfxMessageBox(L"ã���̸��� �����ϴ�.");
		return ;
	}

	safe_delete(iter->second);
	m_mapUnitData.erase(strSelectName);

	m_listboxUnitData.DeleteString(iSelectIndex);

	UpdateData(FALSE);

}

void CUnitTool::OnLbnSelchangeListUnitData()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	
	//##[17.07.14_08]
	CString strSelectName;		//���� ������ �׸��� �̸��� ������ ����.

	//���� ���� ���° �׸��� �����ߴ����� ������ ����.
	int iSelectIndex = m_listboxUnitData.GetCurSel();

	if(iSelectIndex == -1)
		return;

	m_listboxUnitData.GetText(iSelectIndex, strSelectName);

	
	map<CString, UNIT_DATA*>::iterator iter;

	iter = m_mapUnitData.find(strSelectName);

	if(iter == m_mapUnitData.end())
	{
		AfxMessageBox(L"ã���̸��� �����ϴ�.");
		return ;
	}

	m_strName = iter->second->wstrName.c_str();
	m_iAtt	  = iter->second->iAtt;
	m_iHp	  = iter->second->iHp;

	for(int i = 0; i < 3; ++i)
	{
		//�ϴ� ��� ���� ��ư�� ��� ���ش�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	//##[17.07.17_01] : ���ϴ��̾�α�
	CFileDialog		Dlg(
		FALSE,		//��弳�� : TRUE(�ε�), FALSE(����)
		L"dat",		//Ȯ���ڸ�
		L"*.dat",	//���ʿ� ����� �����̸�
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,	//�̸��� ������ �ߺ����Ͽ� ���ؼ� ó���ϴ� �ɼǰ�.
		L"*.dat",	//���� ���Ŀ� ����� Ȯ���ڸ�
		this		
		);


	if(Dlg.DoModal() == IDCANCEL)
		return;
	//DoModal : ���μ����� ���� �������̶�� �����ϸ�ȴ�.
	//		    �������� â�� �������� ����� ����.

	Dlg.m_ofn.lpstrInitialDir = L"..\\Data";		//�����ų ��θ� �����Ѵ�.


	HANDLE hFile = CreateFile(
		Dlg.GetPathName(),		//���� ���.
		GENERIC_WRITE,	//� ����? : ��������
		NULL,		//�������
		NULL,
		CREATE_ALWAYS,	//���Ͽɼ� : ������ ������ ����� -> ������ ���� ������ ���ڰ�.
		FILE_ATTRIBUTE_NORMAL,		//�⺻������ ������ �����϶�¿ɼ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData(TRUE);

	CFileDialog		Dlg(
		TRUE,		//��弳�� : TRUE(�ε�), FALSE(����)
		L"dat",		//Ȯ���ڸ�
		L"*.dat",	//���ʿ� ����� �����̸�
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,	//�̸��� ������ �ߺ����Ͽ� ���ؼ� ó���ϴ� �ɼǰ�.
		L"*.dat",	//���� ���Ŀ� ����� Ȯ���ڸ�
		this		
		);


	if(Dlg.DoModal() == IDCANCEL)
		return;
	
	Release();							//������ �ִ� ������ ��� ��ȯ.
	m_listboxUnitData.ResetContent();		//����Ʈ�ڽ� �ʱ�ȭ.


	Dlg.m_ofn.lpstrInitialDir = L"..\\Data";		//�ε��� ���.


	HANDLE hFile = CreateFile(
		Dlg.GetPathName(),		//���� ���.
		GENERIC_READ,	//� ����? : �б�
		NULL,		//�������
		NULL,
		OPEN_EXISTING,	
		FILE_ATTRIBUTE_NORMAL,		//�⺻������ ������ �����϶�¿ɼ�.
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
