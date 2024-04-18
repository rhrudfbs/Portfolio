#pragma once
#include "afxdialogex.h"


// ADD_PLANET 대화 상자

class ADD_PLANET : public CDialogEx
{
	DECLARE_DYNAMIC(ADD_PLANET)

public:
	ADD_PLANET(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~ADD_PLANET();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = ID_ADD_PLANET };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString ADD_NAME;
	int ADD_SPEED;
	int ADD_RAD;
	int ADD_LIFE;
	CButton ADD_DIR1;
	CButton ADD_DIR2;
	afx_msg void OnBnClickedOk();
	int ADD_SEL;
};
