// Popup.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool76.h"
#include "Popup.h"
#include "Include.h"
#include "MySheet.h"


// CPopup ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CPopup, CDialog)

CPopup::CPopup(CWnd* pParent /*=NULL*/)
	: CDialog(CPopup::IDD, pParent)
	, m_pMySheet(NULL)
{

}

CPopup::~CPopup()
{
	safe_delete(m_pMySheet);
}

void CPopup::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPopup, CDialog)
END_MESSAGE_MAP()


// CPopup �޽��� ó�����Դϴ�.

BOOL CPopup::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	//[17.07.21_03] : ��ƮŬ������ �����Ҵ� �޴´�.
	m_pMySheet = new CMySheet;
	
	//��ƮŬ������ �����Ҵ��� �޾����� ��Ʈ��ü�� �������� �ʾұ� ������
	//�� ��ɵ��� ���� �ֵ��� ��Ʈ�� ����� �ش�.
	m_pMySheet->Create(this, WS_CHILD | WS_VISIBLE);			

	//������ ��Ʈ�� ũ�⸦ ��������.
	m_pMySheet->MoveWindow(0, 0, 500, 400);




	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
