#pragma once
#include "afxwin.h"

// CMonsterTool 대화 상자입니다.
#include "Include.h"

class CMonsterTool : public CDialog
{
	DECLARE_DYNAMIC(CMonsterTool)
private:
	map<CString, CImage*>		m_ObjPngImage;
	OBJINFO						m_ObjInfo;
public:
	int		m_iDrawID;

public:
	void HorizontalScroll(void);
public:
	CMonsterTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMonsterTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MONSTERTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLbnSelchangeListImagePath();
	CListBox m_listBoxImagePath;
	afx_msg void OnDropFiles(HDROP hDropInfo);
	CStatic m_Picture;
	afx_msg void OnStnClickedPictureMonster();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonLoad();
};
