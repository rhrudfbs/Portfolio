// Edit_Moon.cpp: 구현 파일
//

#include "pch.h"
#include "VPC_2019132003_GGR.h"
#include "afxdialogex.h"
#include "Edit_Moon.h"


// Edit_Moon 대화 상자

IMPLEMENT_DYNAMIC(Edit_Moon, CDialogEx)

Edit_Moon::Edit_Moon(CWnd* pParent /*=nullptr*/)
	: CDialogEx(ID_EDIT_MOON, pParent)
	, MOON_RAD(0)
	, MOON_LIFE(0)
	, MOON_SPEED(0)
{

}

Edit_Moon::~Edit_Moon()
{
}

void Edit_Moon::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO1, MOON_DIR1);
	DDX_Control(pDX, IDC_RADIO2, MOON_DIR2);
	DDX_Text(pDX, IDC_EDIT2, MOON_RAD);
	DDX_Text(pDX, IDC_EDIT4, MOON_LIFE);
	DDX_Text(pDX, IDC_EDIT3, MOON_SPEED);
}


BEGIN_MESSAGE_MAP(Edit_Moon, CDialogEx)
	ON_BN_CLICKED(IDOK, &Edit_Moon::OnBnClickedOk)
END_MESSAGE_MAP()


// Edit_Moon 메시지 처리기


void Edit_Moon::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (MOON_DIR1.GetCheck())
	{
		MOON_SEL = 1;
	}
	else if (MOON_DIR2.GetCheck())
	{
		MOON_SEL = -1;
	}
	CDialogEx::OnOK();
}
