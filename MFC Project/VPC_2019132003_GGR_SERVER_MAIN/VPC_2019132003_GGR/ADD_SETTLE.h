#pragma once
#include "afxdialogex.h"
#include "PLANET.h"

// ADD_SETTLE 대화 상자

class ADD_SETTLE : public CDialogEx
{
	DECLARE_DYNAMIC(ADD_SETTLE)

public:
	ADD_SETTLE(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	ADD_SETTLE(PLANET* Start);
	virtual ~ADD_SETTLE();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = ID_ADD_SETTLE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	PLANET* Start = NULL;
	CComboBox Settle_Combo;
	CButton Settle_Dir1;
	CButton Settle_Dir2;
	CString Settle_Name;
	int Settle_Rad;
	int Settle_Speed;
	int Settle_Life;
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeCombo1();
	CString Sel_Planet_Name;
	afx_msg void OnBnClickedOk();
	int Settle_Dir;
};
