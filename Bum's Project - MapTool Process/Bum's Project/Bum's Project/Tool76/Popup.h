#pragma once


// CPopup 대화 상자입니다.

class CMySheet;
class CPopup : public CDialog
{
	DECLARE_DYNAMIC(CPopup)

private:
	//[17.07.21_02]	: 팝업클래스에서 시트를 관리하자.
	CMySheet*		m_pMySheet;

public:
	CPopup(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CPopup();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_POPUP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
