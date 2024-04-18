#pragma once
#include "afxdialogex.h"


// Edit_Moon 대화 상자

class Edit_Moon : public CDialogEx
{
	DECLARE_DYNAMIC(Edit_Moon)

public:
	Edit_Moon(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~Edit_Moon();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = ID_EDIT_MOON };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CButton MOON_DIR1;
	CButton MOON_DIR2;
	int MOON_RAD;
	int MOON_LIFE;
	int MOON_SEL;
	afx_msg void OnBnClickedOk();
	int MOON_SPEED;
};
