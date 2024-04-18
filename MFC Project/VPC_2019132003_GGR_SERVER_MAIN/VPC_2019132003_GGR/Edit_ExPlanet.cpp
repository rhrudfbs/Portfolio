// Edit_ExPlanet.cpp: 구현 파일
//

#include "pch.h"
#include "VPC_2019132003_GGR.h"
#include "afxdialogex.h"
#include "Edit_ExPlanet.h"


// Edit_ExPlanet 대화 상자

IMPLEMENT_DYNAMIC(Edit_ExPlanet, CDialogEx)

Edit_ExPlanet::Edit_ExPlanet(CWnd* pParent /*=nullptr*/)
	: CDialogEx(ID_EDIT_EXPLANET, pParent)
    , Edit_Name(_T(""))
    , Edit_Rad(0)
    , Edit_Speed(0)
    , Edit_Life(0)
{

}

Edit_ExPlanet::Edit_ExPlanet(PLANET* Start)
    : CDialogEx(ID_EDIT_EXPLANET), Start(Start)
{

}

Edit_ExPlanet::~Edit_ExPlanet()
{
}

void Edit_ExPlanet::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO1, Planet_Combo);
    DDX_Control(pDX, IDC_RADIO1, Edit_Dir1);
    DDX_Control(pDX, IDC_RADIO2, Edit_Dir2);
    DDX_Text(pDX, IDC_EDIT1, Edit_Name);
    DDX_Text(pDX, IDC_EDIT2, Edit_Rad);
    DDX_Text(pDX, IDC_EDIT3, Edit_Speed);
    DDX_Text(pDX, IDC_EDIT4, Edit_Life);
}


BEGIN_MESSAGE_MAP(Edit_ExPlanet, CDialogEx)
    ON_CBN_SELCHANGE(IDC_COMBO1, &Edit_ExPlanet::OnCbnSelchangeCombo1)
    ON_BN_CLICKED(IDOK, &Edit_ExPlanet::OnBnClickedOk)
END_MESSAGE_MAP()


// Edit_ExPlanet 메시지 처리기

BOOL Edit_ExPlanet::OnInitDialog()
{
    // 상위 클래스의 OnInitDialog() 함수 호출
    if (!CDialog::OnInitDialog())
        return FALSE;

    // 초기화 작업 수행
    PLANET* P = Start;
    while (P != NULL)
    {
        if (P->SET == FALSE)
        {
            Planet_Combo.AddString(P->GetPlanetName());
        }
        P = P->NEXT;
    }

    return TRUE;
}

void Edit_ExPlanet::OnCbnSelchangeCombo1()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    Planet_Combo.GetLBText(Planet_Combo.GetCurSel(), Sel_Planet_Name);
    PLANET* P = Start;
    while(P != NULL)
    {
        if (P->Name == Sel_Planet_Name)
        {
            P = P;
            break;
        }
        else P = P->NEXT;
    }
    UpdateData(TRUE);
    Edit_Name = P->Name;
    Edit_Rad = P->Radius;
    Edit_Speed = P->Speed;
    Edit_Life = P->Life;
    UpdateData(FALSE);
}


void Edit_ExPlanet::OnBnClickedOk()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    if (Edit_Dir1.GetCheck())
    {
        Sel = TRUE;
    }
    else if (Edit_Dir2.GetCheck())
    {
        Sel = FALSE;
    }
    CDialogEx::OnOK();
}
