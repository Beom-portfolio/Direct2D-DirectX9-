// Popup.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool76.h"
#include "Popup.h"
#include "Include.h"
#include "MySheet.h"


// CPopup 대화 상자입니다.

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


// CPopup 메시지 처리기입니다.

BOOL CPopup::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	//[17.07.21_03] : 시트클래스를 동적할당 받는다.
	m_pMySheet = new CMySheet;
	
	//시트클래스를 동적할당은 받았지만 시트자체를 생성하지 않았기 때문에
	//탭 기능들이 들어갈수 있도록 시트를 만들어 준다.
	m_pMySheet->Create(this, WS_CHILD | WS_VISIBLE);			

	//생성된 시트의 크기를 지정하자.
	m_pMySheet->MoveWindow(0, 0, 500, 400);




	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
