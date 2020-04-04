#pragma once


// CUnitTool 대화 상자입니다.

#include "Include.h"
#include "afxwin.h"

class CUnitTool : public CDialog
{
	DECLARE_DYNAMIC(CUnitTool)

private:
	//##[17.07.14_07] : 추가되는 유닛정보들을 관리하기 위한 컨테이너  -> Key 유닛이름
	map<CString, UNIT_DATA*>	m_mapUnitData;

public:
	void Release();

public:
	CUnitTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CUnitTool();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_UNITTOOL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	// 플레이어 이름
	CString m_strName;
	int m_iAtt;
	// 플레이어 체력
	int m_iHp;
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonDelete();
	CListBox m_listboxUnitData;
	afx_msg void OnLbnSelchangeListUnitData();
	//CButton m_iRadio1;
	//CButton m_iRadio2;
	//CButton m_iRadio3;
	
	//##[17.07.17_00]  : 라디오버튼 배열로 선언해보기.
	CButton	m_iRadio[3];


	bool bStartRadioButtonCheck;
	CButton m_BitmapButton;
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonLoad();
};
