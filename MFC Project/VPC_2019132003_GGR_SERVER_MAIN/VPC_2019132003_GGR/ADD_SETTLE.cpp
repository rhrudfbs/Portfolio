// ADD_SETTLE.cpp: 구현 파일
//

#include "pch.h"
#include "VPC_2019132003_GGR.h"
#include "afxdialogex.h"
#include "ADD_SETTLE.h"


// ADD_SETTLE 대화 상자

IMPLEMENT_DYNAMIC(ADD_SETTLE, CDialogEx)

ADD_SETTLE::ADD_SETTLE(CWnd* pParent /*=nullptr*/)
	: CDialogEx(ID_ADD_SETTLE, pParent)
	, Settle_Name(_T(""))
	, Settle_Rad(10)
	, Settle_Speed(0)
	, Settle_Life(0)
{

}

ADD_SETTLE::ADD_SETTLE(PLANET* Start)
	: CDialogEx(ID_ADD_SETTLE), Start(Start)
	, Settle_Name(_T(""))
	, Settle_Rad(10)
	, Settle_Speed(0)
	, Settle_Life(0)
{

}

ADD_SETTLE::~ADD_SETTLE()
{
}

void ADD_SETTLE::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, Settle_Combo);
	DDX_Control(pDX, IDC_RADIO1, Settle_Dir1);
	DDX_Control(pDX, IDC_RADIO2, Settle_Dir2);
	DDX_Text(pDX, IDC_EDIT1, Settle_Name);
	DDX_Text(pDX, IDC_EDIT2, Settle_Rad);
	DDX_Text(pDX, IDC_EDIT3, Settle_Speed);
	DDX_Text(pDX, IDC_EDIT4, Settle_Life);
}


BEGIN_MESSAGE_MAP(ADD_SETTLE, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &ADD_SETTLE::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDOK, &ADD_SETTLE::OnBnClickedOk)
END_MESSAGE_MAP()


// ADD_SETTLE 메시지 처리기

BOOL ADD_SETTLE::OnInitDialog()
{
	// 상위 클래스의 OnInitDialog() 함수 호출
	if (!CDialog::OnInitDialog())
		return FALSE;

	// 초기화 작업 수행
	PLANET* P = Start;
	while (P != NULL)
	{
		if (P->SET == FALSE || P->Name != _T("SUN"))
		{
			Settle_Combo.AddString(P->GetPlanetName());
		}
		P = P->NEXT;
	}
	return TRUE;
}


void ADD_SETTLE::OnCbnSelchangeCombo1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Settle_Combo.GetLBText(Settle_Combo.GetCurSel(), Sel_Planet_Name);
}


void ADD_SETTLE::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (Settle_Dir1.GetCheck())
	{
		Settle_Dir = 1;
	}
	else if (Settle_Dir2.GetCheck())
	{
		Settle_Dir = -1;
	}
	CDialogEx::OnOK();
}
