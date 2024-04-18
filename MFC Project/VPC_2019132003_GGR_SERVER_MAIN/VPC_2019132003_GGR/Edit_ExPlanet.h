#pragma once
#include "afxdialogex.h"
#include "PLANET.h"

// Edit_ExPlanet 대화 상자

class Edit_ExPlanet : public CDialogEx
{
	DECLARE_DYNAMIC(Edit_ExPlanet)

public:
	Edit_ExPlanet(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	Edit_ExPlanet(PLANET* Start);
	virtual ~Edit_ExPlanet();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = ID_EDIT_EXPLANET };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	PLANET* Start = NULL;
	CComboBox Planet_Combo;
	afx_msg void OnCbnSelchangeCombo1();
	CString Sel_Planet_Name;
	CButton Edit_Dir1;
	CButton Edit_Dir2;
	afx_msg void OnBnClickedOk();
	BOOL Sel;
	CString Edit_Name;
	int Edit_Rad;
	int Edit_Speed;
	int Edit_Life;
};
