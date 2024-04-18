// Delete_Planet.cpp: 구현 파일
//

#include "pch.h"
#include "VPC_2019132003_GGR.h"
#include "afxdialogex.h"
#include "Delete_Planet.h"


// Delete_Planet 대화 상자

IMPLEMENT_DYNAMIC(Delete_Planet, CDialogEx)

Delete_Planet::Delete_Planet(CWnd* pParent /*=nullptr*/)
	: CDialogEx(ID_DELETE_PLANET, pParent)
{

}

Delete_Planet::Delete_Planet(PLANET* S)
	: CDialogEx(ID_DELETE_PLANET), Start(S)
{

}

Delete_Planet::~Delete_Planet()
{
}

void Delete_Planet::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO1, Delete_P);
}


BEGIN_MESSAGE_MAP(Delete_Planet, CDialogEx)
    ON_CBN_SELCHANGE(IDC_COMBO1, &Delete_Planet::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// Delete_Planet 메시지 처리기
BOOL Delete_Planet::OnInitDialog()
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
            Delete_P.AddString(P->GetPlanetName());
        }
        P = P->NEXT;
    }
    return TRUE;
}

void Delete_Planet::OnCbnSelchangeCombo1()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    Delete_P.GetLBText(Delete_P.GetCurSel(), Sel_Del_Planet);
}
