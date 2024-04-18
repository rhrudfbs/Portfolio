// DataSocket.cpp: 구현 파일
//

#include "pch.h"
#include "VPC_2019132003_GGR.h"
#include "DataSocket.h"
#include "MainFrm.h"

// DataSocket


DataSocket::DataSocket()
{
}

DataSocket::~DataSocket()
{
}



// DataSocket 멤버 함수
#include "VPC_2019132003_GGRDoc.h"
#include "PLANET.h"
#include "ORBIT.h"
#include "ORBIT_SETTLE.h"
#include "SETTLLITE.h"
class CVPC2019132003GGRView : public CView
{
protected: // serialization에서만 만들어집니다.
	CVPC2019132003GGRView() noexcept;

	// 특성입니다.
public:
	CVPC2019132003GGRDoc* GetDocument() const;

	// 작업입니다.
public:

	// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// 구현입니다.
public:
	virtual ~CVPC2019132003GGRView();
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;

protected:

	// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	void SetBackGround();
	ORBIT* Start_Orbit = NULL;
	PLANET* Start_Planet = NULL;
	ORBIT_SETTLE* Start_Orbit_Set = NULL;
	PLANET* Point_Moon = NULL;
	int count;
	void Play();
	afx_msg void OnStartSimul();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnEditExplanet();
	afx_msg void OnAddPlanet();
	afx_msg void OnEndSimul();
	afx_msg void OnStartData();
	afx_msg void OnEditMoon();
	afx_msg void OnAddSettle();
	afx_msg void OnDeletePlanet();
	PLANET* Deleted_Planet = NULL;
	SETTLLITE* Start_Settlelite = NULL;
	afx_msg void OnPause();
	afx_msg void On32791();
	afx_msg void OnDestroy();
	void Get_Data();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CString Adata = NULL;
	BOOL CC = FALSE;
};

void DataSocket::OnClose(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	ShutDown();
	Close();
	CVPC2019132003GGRApp* pMain = (CVPC2019132003GGRApp*)AfxGetMainWnd();
	pMain->m_pListenSocket = NULL;
	pMain->m_pDataSocket = NULL;
	AfxMessageBox(_T("Connect Disabled"));
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CVPC2019132003GGRView* pView = (CVPC2019132003GGRView*)pFrame->GetActiveView();
	pView->CC = FALSE;
	CSocket::OnClose(nErrorCode);
}


void DataSocket::AssertValid() const
{
	CSocket::AssertValid();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	return;
}


void DataSocket::OnReceive(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CVPC2019132003GGRView* pView = (CVPC2019132003GGRView*)pFrame->GetActiveView();

	char szBuffer[1024];
	::ZeroMemory(szBuffer, 1024);

	int byteRead = Receive(szBuffer, sizeof(szBuffer) - 1);
	szBuffer[byteRead] = '\0';

	CString F;

	F.Format(_T("%s"), szBuffer);
	Send((LPCTSTR)F, F.GetLength() * sizeof(TCHAR));
	
	if (F == "Go")
	{
		pView->OnStartSimul();
		CString str = _T(" ");
		Send((LPCTSTR)str, str.GetLength() * sizeof(TCHAR));
		Sleep(100);
		str = _T("Simulation Started");
		Send((LPCTSTR)str, str.GetLength() * sizeof(TCHAR));
	}
	else if (F == "Stop")
	{
		pView->count = 1200;
		pView->KillTimer(1);
		PLANET* P = pView->Start_Planet;
		while (P != NULL)
		{
			if (P->Life < (pView->count / 60))
			{
				P = P;
				PLANET* P2 = pView->Start_Planet;
				while (P2 != NULL)
				{
					if (P2->NEXT == P)
					{
						P2 = P2;
						break;
					}
					else P2 = P2->NEXT;
				}
				P2->NEXT = P->NEXT;

				if (pView->Deleted_Planet == NULL)
				{
					pView->Deleted_Planet = P;
					P->NEXT = NULL;
				}

				else
				{
					PLANET* D_P = pView->Deleted_Planet;
					while (D_P->NEXT != NULL)
					{
						D_P = D_P->NEXT;
					}

					P->NEXT = NULL;
					D_P->NEXT = P;
				}

				P = pView->Start_Planet;
			}
			else P = P->NEXT;
		}

		CString str = _T(" ");
		Send((LPCTSTR)str, str.GetLength() * sizeof(TCHAR));
		Sleep(100); 
		str = _T("========Result========");
		Send((LPCTSTR)str, str.GetLength() * sizeof(TCHAR));
		Sleep(10);
		str = _T(" ");
		Send((LPCTSTR)str, str.GetLength() * sizeof(TCHAR));
		Sleep(100);
		str = _T("---Survived Planet---");
		Send((LPCTSTR)str, str.GetLength() * sizeof(TCHAR));
		Sleep(100);
		CString sur_P;
		CString del_P;
		PLANET* SP = pView->Start_Planet;
		if (SP != NULL)
		{
			if (SP->SET == FALSE)
			{
				sur_P.Format(pView->Start_Planet->GetPlanetName());
				Send((LPCTSTR)sur_P, sur_P.GetLength() * sizeof(TCHAR));
				Sleep(100);
			}
			SP = SP->NEXT;
		}
		while (SP != NULL)
		{
			if (SP->SET == FALSE)
			{
				CString TP;
				TP.Format(_T("\n%s"), SP->GetPlanetName());
				sur_P = sur_P + TP;
				TP.Format(SP->GetPlanetName());
				Send((LPCTSTR)TP, TP.GetLength() * sizeof(TCHAR));
				Sleep(100);
			}
			SP = SP->NEXT;
		}

		str = _T(" ");
		Send((LPCTSTR)str, str.GetLength() * sizeof(TCHAR));
		Sleep(100);
		str = _T("---Extincted Planet---");
		Send((LPCTSTR)str, str.GetLength() * sizeof(TCHAR));
		Sleep(100);
		PLANET* DP = pView->Deleted_Planet;
		if (DP != NULL)
		{
			if (DP->SET == FALSE)
			{
				del_P.Format(DP->GetPlanetName());
				Send((LPCTSTR)del_P, del_P.GetLength() * sizeof(TCHAR));
				Sleep(100);
			}
			DP = DP->NEXT;
		}
		while (DP != NULL)
		{
			if (DP->SET == FALSE)
			{
				CString TP;
				TP.Format(_T("\n%s"), DP->GetPlanetName());
				del_P = del_P + TP;
				TP.Format(DP->GetPlanetName());
				Send((LPCTSTR)TP, TP.GetLength() * sizeof(TCHAR));
				Sleep(100);
			}
			DP = DP->NEXT;
		}

		str = _T(" ");
		Send((LPCTSTR)str, str.GetLength() * sizeof(TCHAR));
		Sleep(100);
		str = _T("---Survived Settlelites---");
		Send((LPCTSTR)str, str.GetLength() * sizeof(TCHAR));
		Sleep(100);
		CString sur_S;
		CString del_S;
		PLANET* SS = pView->Start_Planet;
		if (SS != NULL)
		{
			if (SS->SET == TRUE)
			{
				sur_S.Format(_T("%s"), pView->Start_Planet->GetPlanetName());
				Send((LPCTSTR)sur_S, sur_S.GetLength() * sizeof(TCHAR));
				Sleep(100);
			}
			SS = SS->NEXT;
		}
		while (SS != NULL)
		{
			if (SS->SET == TRUE)
			{
				CString TP;
				TP.Format(_T("\n%s"), SS->GetPlanetName());
				sur_S = sur_S + TP;
				TP.Format(SS->GetPlanetName());
				Send((LPCTSTR)TP, TP.GetLength() * sizeof(TCHAR));
				Sleep(100);
			}
			SS = SS->NEXT;
		}
		str = _T(" ");
		Send((LPCTSTR)str, str.GetLength() * sizeof(TCHAR));
		Sleep(100);
		str = _T("---Extincted Settlelites---");
		Send((LPCTSTR)str, str.GetLength() * sizeof(TCHAR));
		Sleep(100);
		PLANET* DS = pView->Deleted_Planet;
		if (DS != NULL)
		{
			if (DS->SET == TRUE)
			{
				del_S.Format(_T("%s"), pView->Deleted_Planet->GetPlanetName());
				Send((LPCTSTR)del_S, del_S.GetLength() * sizeof(TCHAR));
				Sleep(100);
			}
			DS = DS->NEXT;
		}
		while (DS != NULL)
		{
			if (DS->SET == TRUE)
			{
				CString TP;
				TP.Format(_T("\n%s"), DS->GetPlanetName());
				del_S = del_S + TP;
				TP.Format(DS->GetPlanetName());
				Send((LPCTSTR)TP, TP.GetLength() * sizeof(TCHAR));
				Sleep(100);
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

		pView->Play();
		pView->Invalidate();
		AfxMessageBox(Result_P);
		pView->Deleted_Planet = NULL;
	}
	else if (F == "List")
	{
		PLANET* P = pView->Start_Planet;
		CString str1 = _T(" ");
		Send((LPCTSTR)str1, str1.GetLength() * sizeof(TCHAR));
		Sleep(10);
		str1 = _T("----Accessible Planet List----");
		Send((LPCTSTR)str1, str1.GetLength() * sizeof(TCHAR));
		Sleep(10);
		while (P != NULL)
		{
			CString str = P->GetPlanetName();
			Send((LPCTSTR)str, str.GetLength() * sizeof(TCHAR));
			Sleep(10);
			P = P->NEXT;
		}
	}
	else
	{
		CString strData1, strData2, strData3, strData4, strData5;
		PLANET* SearchPlanet = pView->Start_Planet;
		AfxExtractSubString(strData1, F, 0, ' ');
		AfxExtractSubString(strData2, F, 1, ' ');
		AfxExtractSubString(strData3, F, 2, ' ');
		AfxExtractSubString(strData4, F, 3, ' ');
		AfxExtractSubString(strData5, F, 4, ' ');
		if (strData1 == "Edit")
		{
			while (SearchPlanet != NULL)
			{
				if (strData2 == SearchPlanet->GetPlanetName())
				{
					if (strData3 == "Name")
					{
						SearchPlanet->SetPlanetName(strData5);
						pView->Invalidate();
						break;
					}
					else if (strData3 == "Direction")
					{
						if (strData5 == "Clock")
						{
							SearchPlanet->Dir = 1;
						}
						else if (strData5 == "Inclock")
						{
							SearchPlanet->Dir = -1;
						}
						pView->Invalidate();
						break;
					}
					else if (strData3 == "Speed")
					{
						int nvalue = _wtoi(strData5.GetBuffer());
						if (nvalue > 0)
						{
							SearchPlanet->Speed = nvalue;
						}
						pView->Invalidate();
						break;
					}
					else if (strData3 == "Lifetime")
					{
						int nvalue = _wtoi(strData5.GetBuffer());
						if (nvalue > 0)
						{
							SearchPlanet->Life = nvalue;
						}
						pView->Invalidate();
						break;
					}
					else if (strData3 == "Radius")
					{
						int nvalue = _wtoi(strData5.GetBuffer());
						if (nvalue > 0)
						{
							SearchPlanet->Radius = nvalue;
						}
						pView->Invalidate();
						break;
					}
				}
				SearchPlanet = SearchPlanet->NEXT;
			}
			if (SearchPlanet == NULL)
			{
				Sleep(100);

				CString str = _T("Wrong Message Type");

				Send((LPCTSTR)str, str.GetLength() * sizeof(TCHAR));

				Sleep(100);

				str = _T("Please Retype Message Correctly Like Example");

				Send((LPCTSTR)str, str.GetLength() * sizeof(TCHAR));
			}
		}
	}


	CSocket::OnReceive(nErrorCode);
}


int DataSocket::Receive(void* lpBuf, int nBufLen, int nFlags)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CSocket::Receive(lpBuf, nBufLen, nFlags);
}
