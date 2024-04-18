// ADD_PLANET.cpp: 구현 파일
//

#include "pch.h"
#include "VPC_2019132003_GGR.h"
#include "afxdialogex.h"
#include "ADD_PLANET.h"


// ADD_PLANET 대화 상자

IMPLEMENT_DYNAMIC(ADD_PLANET, CDialogEx)

ADD_PLANET::ADD_PLANET(CWnd* pParent /*=nullptr*/)
	: CDialogEx(ID_ADD_PLANET, pParent)
	, ADD_NAME(_T(""))
	, ADD_SPEED(0)
	, ADD_LIFE(0)
	, ADD_RAD(10)
{

}

ADD_PLANET::~ADD_PLANET()
{
}

void ADD_PLANET::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, ADD_NAME);
	DDX_Text(pDX, IDC_EDIT6, ADD_SPEED);
	DDX_Text(pDX, IDC_EDIT5, ADD_RAD);
	DDX_Text(pDX, IDC_EDIT2, ADD_LIFE);
	DDX_Control(pDX, IDC_RADIO1, ADD_DIR1);
	DDX_Control(pDX, IDC_RADIO2, ADD_DIR2);
}


BEGIN_MESSAGE_MAP(ADD_PLANET, CDialogEx)
	ON_BN_CLICKED(IDOK, &ADD_PLANET::OnBnClickedOk)
END_MESSAGE_MAP()


// ADD_PLANET 메시지 처리기


void ADD_PLANET::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (ADD_DIR1.GetCheck())
	{
		ADD_SEL = 1;
	}
	else if (ADD_DIR2.GetCheck())
	{
		ADD_SEL = -1;
	}
	CDialogEx::OnOK();
}

