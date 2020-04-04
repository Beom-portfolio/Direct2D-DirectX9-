// Page2.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool76.h"
#include "Page2.h"


// CPage2 대화 상자입니다.

IMPLEMENT_DYNAMIC(CPage2, CPropertyPage)

CPage2::CPage2()
	: CPropertyPage(CPage2::IDD)
{

}

CPage2::~CPage2()
{
}

void CPage2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPage2, CPropertyPage)
END_MESSAGE_MAP()


// CPage2 메시지 처리기입니다.
