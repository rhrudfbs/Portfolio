#pragma once
#include "afxdialogex.h"
#include "PLANET.h"

// Delete_Planet 대화 상자

class Delete_Planet : public CDialogEx
{
	DECLARE_DYNAMIC(Delete_Planet)

public:
	Delete_Planet(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	Delete_Planet(PLANET* S);
	virtual ~Delete_Planet();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = ID_DELETE_PLANET };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()
public:
	CComboBox Delete_P;
	virtual BOOL OnInitDialog();
	PLANET* Start;
	CString Sel_Del_Planet = NULL;
	afx_msg void OnCbnSelchangeCombo1();
};
