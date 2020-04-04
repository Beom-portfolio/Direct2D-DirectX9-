#pragma once


// CUnitTool ��ȭ �����Դϴ�.

#include "Include.h"
#include "afxwin.h"

class CUnitTool : public CDialog
{
	DECLARE_DYNAMIC(CUnitTool)

private:
	//##[17.07.14_07] : �߰��Ǵ� ������������ �����ϱ� ���� �����̳�  -> Key �����̸�
	map<CString, UNIT_DATA*>	m_mapUnitData;

public:
	void Release();

public:
	CUnitTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CUnitTool();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_UNITTOOL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	// �÷��̾� �̸�
	CString m_strName;
	int m_iAtt;
	// �÷��̾� ü��
	int m_iHp;
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonDelete();
	CListBox m_listboxUnitData;
	afx_msg void OnLbnSelchangeListUnitData();
	//CButton m_iRadio1;
	//CButton m_iRadio2;
	//CButton m_iRadio3;
	
	//##[17.07.17_00]  : ������ư �迭�� �����غ���.
	CButton	m_iRadio[3];


	bool bStartRadioButtonCheck;
	CButton m_BitmapButton;
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonLoad();
};
