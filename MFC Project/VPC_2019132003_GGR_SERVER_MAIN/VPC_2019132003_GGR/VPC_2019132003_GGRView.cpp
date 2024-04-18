
// VPC_2019132003_GGRView.cpp: CVPC2019132003GGRView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "VPC_2019132003_GGR.h"
#endif

#include "VPC_2019132003_GGRDoc.h"
#include "VPC_2019132003_GGRView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CVPC2019132003GGRView

IMPLEMENT_DYNCREATE(CVPC2019132003GGRView, CView)

BEGIN_MESSAGE_MAP(CVPC2019132003GGRView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_START_SIMUL, &CVPC2019132003GGRView::OnStartSimul)
	ON_WM_TIMER()
	ON_COMMAND(ID_EDIT_EXPLANET, &CVPC2019132003GGRView::OnEditExplanet)
	ON_COMMAND(ID_ADD_PLANET, &CVPC2019132003GGRView::OnAddPlanet)
	ON_COMMAND(ID_END_SIMUL, &CVPC2019132003GGRView::OnEndSimul)
	ON_COMMAND(ID_START_DATA, &CVPC2019132003GGRView::OnStartData)
	ON_COMMAND(ID_EDIT_MOON, &CVPC2019132003GGRView::OnEditMoon)
	ON_COMMAND(ID_ADD_SETTLE, &CVPC2019132003GGRView::OnAddSettle)
	ON_COMMAND(ID_DELETE_PLANET, &CVPC2019132003GGRView::OnDeletePlanet)
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_PAUSE, &CVPC2019132003GGRView::OnPause)
	ON_COMMAND(ID_32791, &CVPC2019132003GGRView::On32791)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CVPC2019132003GGRView 생성/소멸

CVPC2019132003GGRView::CVPC2019132003GGRView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	SetBackGround();
}

CVPC2019132003GGRView::~CVPC2019132003GGRView()
{
}

BOOL CVPC2019132003GGRView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CVPC2019132003GGRView 그리기

void CVPC2019132003GGRView::OnDraw(CDC* pDC)
{
	CVPC2019132003GGRDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	Play();

	CBrush bbrush;
	bbrush.CreateStockObject(NULL_BRUSH);
	pDC->SelectObject(bbrush);
	ORBIT* SO = Start_Orbit;
	ORBIT_SETTLE* SOS = Start_Orbit_Set;
	PLANET* SP = Start_Planet;
	while (SO != NULL)
	{
		pDC->Ellipse(SO->GetOrbit());
		SO = SO->NEXT;
	}
	while (SOS != NULL)
	{
		pDC->Ellipse(SOS->GetSetOrbit());
		SOS = SOS->NEXT;
	}
	CBrush obrush;
	obrush.CreateStockObject(WHITE_BRUSH);
	pDC->SelectObject(obrush);
	while (SP != NULL)
	{
		pDC->Ellipse(SP->GetPlanetLoc());
		pDC->DrawTextW(SP->GetPlanetName(), SP->GetPlanetLoc(), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		SP = SP->NEXT;
	}
}


// CVPC2019132003GGRView 인쇄

BOOL CVPC2019132003GGRView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CVPC2019132003GGRView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CVPC2019132003GGRView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CVPC2019132003GGRView 진단

#ifdef _DEBUG
void CVPC2019132003GGRView::AssertValid() const
{
	CView::AssertValid();
}

void CVPC2019132003GGRView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CVPC2019132003GGRDoc* CVPC2019132003GGRView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVPC2019132003GGRDoc)));
	return (CVPC2019132003GGRDoc*)m_pDocument;
}
#endif //_DEBUG


// CVPC2019132003GGRView 메시지 처리기


void CVPC2019132003GGRView::SetBackGround()
{
	// TODO: 여기에 구현 코드 추가.

	PLANET* SUN = new PLANET;
	Start_Planet = SUN;
	SUN->SetPlanetName(_T("SUN"));
	SUN->SetPlanetSpeed(600);
	SUN->SetPlanetLife(100);
	SUN->SetPlanetDir(-1);
	SUN->Loc.left = 370;
	SUN->Loc.top = 370;
	SUN->Loc.right = 430;
	SUN->Loc.bottom = 430;



	ORBIT* M_Orbit = new ORBIT;
	Start_Orbit = M_Orbit;
	CRect M_Rect;
	M_Rect.left = 350;
	M_Rect.top = 250;
	M_Rect.right = 650;
	M_Rect.bottom = 550;
	M_Orbit->Orbit = M_Rect;

	PLANET* M = new PLANET;
	SUN->NEXT = M;
	M->Orbit = M_Rect;
	M->SetPlanetName(_T("M"));
	M->SetPlanetSpeed(6);
	M->SetPlanetLife(15);
	M->SetPlanetDir(-1);
	M->SetPlanetSize(15);
	M->SetPlanetLoc();



	ORBIT* V_Orbit = new ORBIT;
	M_Orbit->NEXT = V_Orbit;
	CRect V_Rect;
	V_Rect.left = 300;
	V_Rect.top = 175;
	V_Rect.right = 800;
	V_Rect.bottom = 625;
	V_Orbit->Orbit = V_Rect;

	PLANET* V = new PLANET;
	M->NEXT = V;
	V->Orbit = V_Rect;
	V->SetPlanetName(_T("V"));
	V->SetPlanetSpeed(5);
	V->SetPlanetLife(10);
	V->SetPlanetDir(1);
	V->SetPlanetSize(20);
	V->SetPlanetLoc();



	ORBIT* E_Orbit = new ORBIT;
	V_Orbit->NEXT = E_Orbit;
	CRect E_Rect;
	E_Rect.left = 200;
	E_Rect.top = 100;
	E_Rect.right = 1000;
	E_Rect.bottom = 700;
	E_Orbit->Orbit = E_Rect;
	E_Orbit->NEXT = NULL;

	PLANET* E = new PLANET;
	V->NEXT = E;
	E->Orbit = E_Rect;
	E->SetPlanetName(_T("E"));
	E->SetPlanetSpeed(4);
	E->SetPlanetLife(30);
	E->SetPlanetDir(-1);
	E->SetPlanetSize(20);
	E->SetPlanetLoc();

	ORBIT_SETTLE* MOON_Orbit = new ORBIT_SETTLE;
	Start_Orbit_Set = MOON_Orbit;
	MOON_Orbit->Name = _T("MOON");
	MOON_Orbit->P = E;
	MOON_Orbit->SetSetOrbit();
	MOON_Orbit->NEXT = NULL;

	PLANET* MOON = new PLANET;
	Start_Settlelite = (SETTLLITE *)MOON;
	Point_Moon = MOON;
	E->NEXT = MOON;
	MOON->SET = TRUE;
	MOON->Orbit = MOON_Orbit->GetSetOrbit();
	MOON->SetPlanetName(_T("MOON"));
	MOON->SetPlanetSpeed(3);
	MOON->SetPlanetLife(20);
	MOON->SetPlanetDir(-1);
	MOON->SetPlanetSize(15);
	MOON->SetPlanetLoc();
	MOON->NEXT = NULL;


}


void CVPC2019132003GGRView::Play()
{
	// TODO: 여기에 구현 코드 추가.
	PLANET* SP = Start_Planet;
	SP = SP->NEXT;
	while (SP != NULL)
	{
		if (SP->SET == TRUE)
		{
			ORBIT_SETTLE* SOS = Start_Orbit_Set;
			while (SOS != NULL)
			{
				if (SOS->Name == SP->Name)
				{
					SOS = SOS;
					break;
				}
				else SOS = SOS->NEXT;
			}
			SP->Orbit = SOS->GetSetOrbit();
		}
		SP->SetPlanetLoc();
		SP = SP->NEXT;
	}
	ORBIT_SETTLE* OS = Start_Orbit_Set;
	while (OS != NULL)
	{
		OS->SetSetOrbit();
		OS = OS->NEXT;
	}
}


void CVPC2019132003GGRView::OnStartSimul()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (Deleted_Planet != NULL)
	{
		PLANET* DP = Deleted_Planet;
		while (DP->NEXT != NULL)
		{
			if (DP->NEXT == NULL)
			{
				delete DP;
				DP = NULL;
				DP = Deleted_Planet;
			}
			else DP = DP->NEXT;
		}
		delete Deleted_Planet;

		Deleted_Planet = NULL;
	}
	count = 0;
	PLANET* P = Start_Planet;
	while (P != NULL)
	{
		P->time = 0;
		P = P->NEXT;
	}
	SetTimer(1, 1, NULL);
}


void CVPC2019132003GGRView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	count++;
	if (nIDEvent == 1)
	{
		PLANET* SP = Start_Planet;
		while (SP != NULL)
		{
			if (SP->Dir == 1)
			{
				SP->time += 1;
			}
			else if (SP->Dir == -1)
			{
				SP->time -= 1;
			}
			SP = SP->NEXT;
		}
		SP = Start_Planet;
		while (SP != NULL)
		{
			if (SP->Life < (count / 60))
			{
				SP = SP;
				PLANET* SP2 = Start_Planet;
				while (SP2 != NULL)
				{
					if (SP2->NEXT == SP)
					{
						SP2 = SP2;
						break;
					}
					else SP2 = SP2->NEXT;
				}
				SP2->NEXT = SP->NEXT;
				
				if (Deleted_Planet == NULL)
				{
					Deleted_Planet = SP;
					SP->NEXT = NULL;
				}

				else
				{
					PLANET* DP = Deleted_Planet;
					while (DP->NEXT != NULL)
					{
						DP = DP->NEXT;
					}

					SP->NEXT = NULL;
					DP->NEXT = SP;
				}

				SP = Start_Planet;
			}
			else SP = SP->NEXT;
		}
		Invalidate();

		if (count == 1200)
		{
			KillTimer(1);

			if (CC == FALSE)
			{
				CString sur_P;
				CString del_P;
				SP = Start_Planet;
				if (SP != NULL)
				{
					if (SP->SET == FALSE)
					{
						sur_P.Format(Start_Planet->GetPlanetName());
					}
					SP = SP->NEXT;
				}
				while (SP != NULL)
				{
					if (SP->SET == FALSE)
					{
						CString TP;
						TP.Format(SP->GetPlanetName());
						sur_P = sur_P + _T("\n") + TP;
					}
					SP = SP->NEXT;
				}

				PLANET* DP = Deleted_Planet;
				if (DP != NULL)
				{
					if (DP->SET == FALSE)
					{
						del_P.Format(Deleted_Planet->GetPlanetName());
					}
					DP = DP->NEXT;
				}
				while (DP != NULL)
				{
					if (DP->SET == FALSE)
					{
						CString TP;
						TP.Format(DP->GetPlanetName());
						del_P = del_P + _T("\n") + TP;
					}
					DP = DP->NEXT;
				}

				CString sur_S;
				CString del_S;
				SP = Start_Planet;
				if (SP != NULL)
				{
					if (SP->SET == TRUE)
					{
						sur_S.Format(Start_Planet->GetPlanetName());
					}
					SP = SP->NEXT;
				}
				while (SP != NULL)
				{
					if (SP->SET == TRUE)
					{
						CString TP;
						TP.Format(SP->GetPlanetName());
						sur_S = sur_S + _T("\n") + TP;
					}
					SP = SP->NEXT;
				}
				DP = Deleted_Planet;
				if (DP != NULL)
				{
					if (DP->SET == TRUE)
					{
						del_S.Format(Deleted_Planet->GetPlanetName());
					}
					DP = DP->NEXT;
				}
				while (DP != NULL)
				{
					if (DP->SET == TRUE)
					{
						CString TP;
						TP.Format(DP->GetPlanetName());
						del_S = del_S + _T("\n") + TP;
					}
					DP = DP->NEXT;
				}


				CString Result_P;
				Result_P.Format(_T("Alived Planets\n"));
				Result_P = Result_P + sur_P;
				CString middle1;
				middle1.Format(_T("\n\nExtincted Planets\n"));
				Result_P = Result_P + middle1;
				Result_P = Result_P + del_P;
				CString middle2;
				middle2.Format(_T("\n\nAlived Settlelites\n"));
				Result_P = Result_P + middle2;
				Result_P = Result_P + sur_S;
				CString middle3;
				middle3.Format(_T("\n\nExtincted Settlelites\n"));
				Result_P = Result_P + middle3;
				Result_P = Result_P + del_S;

				Adata.Format(Result_P);
				Play();
				Invalidate();


				AfxMessageBox(Result_P);

				//스택 포인터로 메모리 할당 해제
				DP = Deleted_Planet;
				while (DP->NEXT != NULL)
				{
					if (DP->NEXT == NULL)
					{
						delete DP;
						DP = NULL;
						DP = Deleted_Planet;
					}
					else DP = DP->NEXT;
				}
				delete Deleted_Planet;

				Deleted_Planet = NULL;
			}
			else if (CC == TRUE)
			{
				CVPC2019132003GGRApp* pMain = (CVPC2019132003GGRApp*)AfxGetMainWnd();
				CString str = _T("========Result========");
				pMain->m_pDataSocket->Send((LPCTSTR)str, str.GetLength() * sizeof(TCHAR));
				Sleep(100);
				str = _T(" ");
				pMain->m_pDataSocket->Send((LPCTSTR)str, str.GetLength() * sizeof(TCHAR));

				str = _T("---Survived Planet---");
				pMain->m_pDataSocket->Send((LPCTSTR)str, str.GetLength() * sizeof(TCHAR));
				Sleep(100);

				CString sur_P;
				CString del_P;
				SP = Start_Planet;
				if (SP != NULL)
				{
					if (SP->SET == FALSE)
					{
						sur_P.Format(Start_Planet->GetPlanetName());
						pMain->m_pDataSocket->Send((LPCTSTR)sur_P, sur_P.GetLength() * sizeof(TCHAR));
						Sleep(100);
					}
					SP = SP->NEXT;
				}
				while (SP != NULL)
				{
					if (SP->SET == FALSE)
					{
						CString TP;
						TP.Format(SP->GetPlanetName());
						sur_P = sur_P + _T("\n") + TP;
						pMain->m_pDataSocket->Send((LPCTSTR)TP, TP.GetLength() * sizeof(TCHAR));
						Sleep(100);
					}
					SP = SP->NEXT;
				}

				str = _T(" ");
				pMain->m_pDataSocket->Send((LPCTSTR)str, str.GetLength() * sizeof(TCHAR));
				Sleep(100);
				str = _T("---Extincted Planet---");
				pMain->m_pDataSocket->Send((LPCTSTR)str, str.GetLength() * sizeof(TCHAR));
				Sleep(100);

				PLANET* DP = Deleted_Planet;
				if (DP != NULL)
				{
					if (DP->SET == FALSE)
					{
						del_P.Format(Deleted_Planet->GetPlanetName());
						pMain->m_pDataSocket->Send((LPCTSTR)del_P, del_P.GetLength() * sizeof(TCHAR));
						Sleep(100);
					}
					DP = DP->NEXT;
				}
				while (DP != NULL)
				{
					if (DP->SET == FALSE)
					{
						CString TP;
						TP.Format(DP->GetPlanetName());
						del_P = del_P + _T("\n") + TP;
						pMain->m_pDataSocket->Send((LPCTSTR)TP, TP.GetLength() * sizeof(TCHAR));
						Sleep(100);
					}
					DP = DP->NEXT;
				}

				str = _T(" ");
				pMain->m_pDataSocket->Send((LPCTSTR)str, str.GetLength() * sizeof(TCHAR));
				Sleep(100);
				str = _T("---Survived Settlelites---");
				pMain->m_pDataSocket->Send((LPCTSTR)str, str.GetLength() * sizeof(TCHAR));
				Sleep(100);

				CString sur_S;
				CString del_S;
				SP = Start_Planet;
				if (SP != NULL)
				{
					if (SP->SET == TRUE)
					{
						sur_S.Format(Start_Planet->GetPlanetName());
						pMain->m_pDataSocket->Send((LPCTSTR)sur_S, sur_S.GetLength() * sizeof(TCHAR));
						Sleep(100);
					}
					SP = SP->NEXT;
				}
				while (SP != NULL)
				{
					if (SP->SET == TRUE)
					{
						CString TP;
						TP.Format(SP->GetPlanetName());
						sur_S = sur_S + _T("\n") + TP;
						pMain->m_pDataSocket->Send((LPCTSTR)TP, TP.GetLength() * sizeof(TCHAR));
						Sleep(100);
					}
					SP = SP->NEXT;
				}
				str = _T(" ");
				pMain->m_pDataSocket->Send((LPCTSTR)str, str.GetLength() * sizeof(TCHAR));
				Sleep(100);
				str = _T("---Extincted Settlelites---");
				pMain->m_pDataSocket->Send((LPCTSTR)str, str.GetLength() * sizeof(TCHAR));
				Sleep(100);
				DP = Deleted_Planet;
				if (DP != NULL)
				{
					if (DP->SET == TRUE)
					{
						del_S.Format(Deleted_Planet->GetPlanetName());
						pMain->m_pDataSocket->Send((LPCTSTR)del_S, del_S.GetLength() * sizeof(TCHAR));
						Sleep(100);
					}
					DP = DP->NEXT;
				}
				while (DP != NULL)
				{
					if (DP->SET == TRUE)
					{
						CString TP;
						TP.Format(DP->GetPlanetName());
						del_S = del_S + _T("\n") + TP;
						pMain->m_pDataSocket->Send((LPCTSTR)TP, TP.GetLength() * sizeof(TCHAR));
						Sleep(100);
					}
					DP = DP->NEXT;
				}


				CString Result_P;
				Result_P.Format(_T("Alived Planets\n"));
				Result_P = Result_P + sur_P;
				CString middle1;
				middle1.Format(_T("\n\nExtincted Planets\n"));
				Result_P = Result_P + middle1;
				Result_P = Result_P + del_P;
				CString middle2;
				middle2.Format(_T("\n\nAlived Settlelites\n"));
				Result_P = Result_P + middle2;
				Result_P = Result_P + sur_S;
				CString middle3;
				middle3.Format(_T("\n\nExtincted Settlelites\n"));
				Result_P = Result_P + middle3;
				Result_P = Result_P + del_S;

				Adata.Format(Result_P);
				Play();
				Invalidate();


				AfxMessageBox(Result_P);

				//스택 포인터로 메모리 할당 해제
				DP = Deleted_Planet;
				while (DP->NEXT != NULL)
				{
					if (DP->NEXT == NULL)
					{
						delete DP;
						DP = NULL;
						DP = Deleted_Planet;
					}
					else DP = DP->NEXT;
				}
				delete Deleted_Planet;

				Deleted_Planet = NULL;
			}
		}
	}
	CView::OnTimer(nIDEvent);
}


#include "Edit_ExPlanet.h"
void CVPC2019132003GGRView::OnEditExplanet()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	Edit_ExPlanet dlg(Start_Planet);
	int res = dlg.DoModal();
	if (res == IDOK)
	{
		PLANET* P = Start_Planet;
		while (P != NULL)
		{
			if (P->Name == dlg.Sel_Planet_Name)
			{
				P = P;
				if (dlg.Sel == TRUE)
				{
					P->Dir = 1;
				}
				else if (dlg.Sel == FALSE)
				{
					P->Dir = -1;
				}
				P->Name = dlg.Edit_Name;
				P->Radius = dlg.Edit_Rad;
				P->Speed = dlg.Edit_Speed;
				P->Life = dlg.Edit_Life;
				Invalidate();
				AfxMessageBox(_T("Planet Edit Complete"));
				break;
			}
			else P = P->NEXT;
		}
	}
	else if (res == IDCANCEL)
	{
		AfxMessageBox(_T("Planet Edit Cancel"));
	}
}


#include "ADD_PLANET.h"
void CVPC2019132003GGRView::OnAddPlanet()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	ADD_PLANET dlg;
	int res = dlg.DoModal();
	if (res == IDOK)
	{
		ORBIT* O = Start_Orbit;
		while (O->NEXT != NULL)
		{
			O = O->NEXT;
		}
		CRect next = O->GetOrbit();
		next.left -= 100;
		next.top -= 100;
		next.right += 100;
		next.bottom += 100;
		ORBIT* NewOrbit = new ORBIT;
		NewOrbit->Orbit = next;
		O->NEXT = NewOrbit;
		NewOrbit->NEXT = NULL;

		PLANET* P = Start_Planet;
		while (P->NEXT != NULL)
		{
			P = P->NEXT;
		}

		PLANET* NewPlanet = new PLANET;
		P->NEXT = NewPlanet;
		NewPlanet->NEXT = NULL;
		NewPlanet->Orbit = NewOrbit->GetOrbit();
		NewPlanet->SetPlanetName(dlg.ADD_NAME);
		NewPlanet->SetPlanetSpeed(dlg.ADD_SPEED);
		NewPlanet->SetPlanetLife(dlg.ADD_LIFE);
		NewPlanet->SetPlanetDir(dlg.ADD_SEL);
		NewPlanet->SetPlanetSize(dlg.ADD_RAD);

		AfxMessageBox(_T("Add Planet Complete"));
		Invalidate();
	}
	else if (res == IDCANCEL)
	{
		AfxMessageBox(_T("Add Planet Cancel"));
	}
}


void CVPC2019132003GGRView::OnEndSimul()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	count = 1200;
	KillTimer(1);
	PLANET* SP = Start_Planet;
	while (SP != NULL)
	{
		if (SP->Life < (count / 60))
		{
			SP = SP;
			PLANET* P2 = Start_Planet;
			while (P2 != NULL)
			{
				if (P2->NEXT == SP)
				{
					P2 = P2;
					break;
				}
				else P2 = P2->NEXT;
			}
			P2->NEXT = SP->NEXT;
			CString A = SP->GetPlanetName();
			CString B = _T(" Planet Extinct");

			if (count < 1180)
			{
				AfxMessageBox(A + B);
			}

			if (Deleted_Planet == NULL)
			{
				Deleted_Planet = SP;
				SP->NEXT = NULL;
			}

			else
			{
				PLANET* D_P = Deleted_Planet;
				while (D_P->NEXT != NULL)
				{
					D_P = D_P->NEXT;
				}

				SP->NEXT = NULL;
				D_P->NEXT = SP;
			}

			SP = Start_Planet;
		}
		else SP = SP->NEXT;
	}
	CString sur_P;
	CString del_P;
	SP = Start_Planet;
	if (SP != NULL)
	{
		if (SP->SET == FALSE)
		{
			sur_P.Format(Start_Planet->GetPlanetName());
		}
		SP = SP->NEXT;
	}
	PLANET* DP = Deleted_Planet;
	if (DP != NULL)
	{
		if (DP->SET == FALSE)
		{
			del_P.Format(Deleted_Planet->GetPlanetName());
		}
		DP = DP->NEXT;
	}
	while (SP != NULL)
	{
		if (SP->SET == FALSE)
		{
			CString TP;
			TP.Format(SP->GetPlanetName());
			sur_P = sur_P + _T("\n") + TP;
		}
		SP = SP->NEXT;
	}
	while (DP != NULL)
	{
		if (DP->SET == FALSE)
		{
			CString TP;
			TP.Format(DP->GetPlanetName());
			del_P = del_P + _T("\n") + TP;
		}
		DP = DP->NEXT;
	}


	CString sur_S;
	CString del_S;
	SP = Start_Planet;
	if (SP != NULL)
	{
		if (SP->SET == TRUE)
		{
			sur_S.Format(Start_Planet->GetPlanetName());
		}
		SP = SP->NEXT;
	}
	PLANET* DS = Deleted_Planet;
	if (DS != NULL)
	{
		if (DS->SET == TRUE)
		{
			del_S.Format(Deleted_Planet->GetPlanetName());
		}
		DS = DS->NEXT;
	}
	while (SP != NULL)
	{
		if (SP->SET == TRUE)
		{
			CString TP;
			TP.Format(SP->GetPlanetName());
			sur_S = sur_S + _T("\n") + TP;
		}
		SP = SP->NEXT;
	}
	while (DS != NULL)
	{
		if (DS->SET == TRUE)
		{
			CString TP;
			TP.Format(DS->GetPlanetName());
			del_S = del_S + _T("\n") + TP;
		}
		DS = DS->NEXT;
	}


	CString Result_P;
	Result_P.Format(_T("Alived Planets\n"));
	Result_P = Result_P + sur_P;
	CString middle1;
	middle1.Format(_T("\n\nExtincted Planets\n"));
	Result_P = Result_P + middle1;
	Result_P = Result_P + del_P;
	CString middle2;
	middle2.Format(_T("\n\nAlived Settlelites\n"));
	Result_P = Result_P + middle2;
	Result_P = Result_P + sur_S;
	CString middle3;
	middle3.Format(_T("\n\nExtincted Settlelites\n"));
	Result_P = Result_P + middle3;
	Result_P = Result_P + del_S;

	Adata.Format(Result_P);
	Play();
	Invalidate();
	AfxMessageBox(Result_P);

	if (Deleted_Planet != NULL)
	{
		PLANET* DP = Deleted_Planet;
		while (DP->NEXT != NULL)
		{
			if (DP->NEXT == NULL)
			{
				delete DP;
				DP = NULL;
				DP = Deleted_Planet;
			}
			else DP = DP->NEXT;
		}
		delete Deleted_Planet;

		Deleted_Planet = NULL;
	}
}


void CVPC2019132003GGRView::OnStartData()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (Deleted_Planet != NULL)
	{
		PLANET* DP = Deleted_Planet;
		while (DP->NEXT != NULL)
		{
			if (DP->NEXT == NULL)
			{
				delete DP;
				DP = NULL;
				DP = Deleted_Planet;
			}
			else DP = DP->NEXT;
		}
		delete Deleted_Planet;

		Deleted_Planet = NULL;
	}
	SetBackGround();

	Invalidate();
}


#include "Edit_Moon.h"
void CVPC2019132003GGRView::OnEditMoon()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	Edit_Moon dlg(this);
	int res = dlg.DoModal();
	if (res == IDOK)
	{
		Point_Moon->Dir = dlg.MOON_SEL;
		Point_Moon->Life = dlg.MOON_LIFE;
		Point_Moon->Speed = dlg.MOON_SPEED;
		Point_Moon->Radius = dlg.MOON_RAD;
		Invalidate();
		AfxMessageBox(_T("Moon Edit Complete"));
	}
	else if (res == IDCANCEL)
	{
		AfxMessageBox(_T("Moon Edit Cancel"));
	}
}


#include "ADD_SETTLE.h"
void CVPC2019132003GGRView::OnAddSettle()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	ADD_SETTLE dlg(Start_Planet);
	int res = dlg.DoModal();
	if (res == IDOK)
	{
		ORBIT_SETTLE* OS = Start_Orbit_Set;
		while (OS->NEXT != NULL)
		{
			OS = OS->NEXT;
		}
		ORBIT_SETTLE* NewSetOr = new ORBIT_SETTLE;
		OS->NEXT = NewSetOr;
		NewSetOr->NEXT = NULL;
		PLANET* SP = Start_Planet;
		while (SP->Name != dlg.Sel_Planet_Name)
		{
			if (SP->Name == dlg.Sel_Planet_Name)
			{
				SP = SP;
				break;
			}
			SP = SP->NEXT;
		}
		NewSetOr->P = SP;
		NewSetOr->SetSetOrbit();
		NewSetOr->Name = dlg.Settle_Name;

		while (SP->NEXT != NULL)
		{
			SP = SP->NEXT;
		}

		PLANET* NewPlanet = new PLANET;
		SP->NEXT = NewPlanet;
		NewPlanet->NEXT = NULL;
		NewPlanet->SET = TRUE;
		NewPlanet->Orbit = NewSetOr->GetSetOrbit();
		NewPlanet->Name = dlg.Settle_Name;
		NewPlanet->Dir = dlg.Settle_Dir;
		NewPlanet->Life = dlg.Settle_Life;
		NewPlanet->Radius = dlg.Settle_Rad;
		NewPlanet->Speed = dlg.Settle_Speed;
		Invalidate();

		AfxMessageBox(_T("Add Settlelite Complete"));
	}
	else if (res == IDCANCEL)
	{
		AfxMessageBox(_T("Add Settlelite Cancel"));
	}
}


#include "Delete_Planet.h"
void CVPC2019132003GGRView::OnDeletePlanet()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	Delete_Planet dlg(Start_Planet);
	int res = dlg.DoModal();
	if (res == IDOK)
	{
		PLANET* SP = Start_Planet;
		if (SP->GetPlanetName() == dlg.Sel_Del_Planet)
		{
			SP = SP;
			Start_Planet = SP->NEXT;
			delete SP;
		}
		else
		{
			while (SP != NULL)
			{
				if (SP->NEXT->GetPlanetName() == dlg.Sel_Del_Planet)
				{
					SP = SP;
					break;
				}
				else SP = SP->NEXT;
			}
			PLANET* Del = SP->NEXT;
			SP->NEXT = Del->NEXT;
			delete Del;
		}
		Invalidate();
		AfxMessageBox(_T("Extinct Planet Complete"));
	}
	else if (res == IDCANCEL)
	{
		AfxMessageBox(_T("Extinct Planet Cancel"));
	}
}

void CVPC2019132003GGRView::OnPause()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	KillTimer(1);
}


void CVPC2019132003GGRView::On32791()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	SetTimer(1, 1, NULL);
}

void CVPC2019132003GGRView::OnDestroy()
{
	CView::OnDestroy();
	CVPC2019132003GGRApp* pMain = (CVPC2019132003GGRApp*)AfxGetMainWnd();
	CString str = _T("Connect Disabled");

	pMain->m_pDataSocket->Send((LPCTSTR)str, str.GetLength() * sizeof(TCHAR));

	if (pMain->m_pDataSocket != NULL) {
		pMain->m_pDataSocket->ShutDown();
		pMain->m_pDataSocket->Close();
		delete pMain->m_pDataSocket;
	}
	pMain->m_pDataSocket->ShutDown();
	pMain->m_pDataSocket->Close();
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}



void CVPC2019132003GGRView::Get_Data()
{
	// TODO: 여기에 구현 코드 추가.
}



BOOL CVPC2019132003GGRView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		if (GetKeyState(VK_CONTROL) & 0x8000)
		{
			if (pMsg->wParam == 0x58)
			{
				count = 1190;
			}
		}
	}


	return CView::PreTranslateMessage(pMsg);
}
