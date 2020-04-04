// Page1.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool76.h"
#include "Page1.h"


// CPage1 대화 상자입니다.

IMPLEMENT_DYNAMIC(CPage1, CPropertyPage)

CPage1::CPage1()
	: CPropertyPage(CPage1::IDD)
{

}

CPage1::~CPage1()
{
}

void CPage1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPage1, CPropertyPage)
END_MESSAGE_MAP()


// CPage1 메시지 처리기입니다.
