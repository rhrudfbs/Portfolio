// ListenSocket.cpp: 구현 파일
//

#include "pch.h"
#include "VPC_2019132003_GGR.h"
#include "ListenSocket.h"

#include "MainFrm.h"

// ListenSocket

ListenSocket::ListenSocket()
{
	pp_Data = NULL;
}

ListenSocket::~ListenSocket()
{
}


// ListenSocket 멤버 함수
#include "VPC_2019132003_GGRDoc.h"
#include "PLANET.h"
#include "ORBIT.h"
#include "ORBIT_SETTLE.h"
#include "SETTLLITE.h"
class CVPC2019132003GGRView : public CView
{
protected: // serialization에서만 만들어집니다.
	CVPC2019132003GGRView() noexcept;
	DECLARE_DYNCREATE(CVPC2019132003GGRView)

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
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

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
	int count = 0;
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


void ListenSocket::OnAccept(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	DataSocket* m_pData = new DataSocket;
	
	BOOL check = Accept(*m_pData);

	if (check == FALSE)
	{
		delete m_pData;
		AfxMessageBox(_T("Connect Failed"));
		return;
	}
	else pp_Data = m_pData;
	AfxMessageBox(_T("Connect Successed"));
	CString str = _T("Connect Successed");

	CVPC2019132003GGRApp* pMain = (CVPC2019132003GGRApp*)AfxGetMainWnd();
	pMain->m_pDataSocket = m_pData;

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CVPC2019132003GGRView* pView = (CVPC2019132003GGRView*)pFrame->GetActiveView();
	pView->CC = TRUE;

	pMain->m_pDataSocket->Send((LPCTSTR)str, str.GetLength() * sizeof(TCHAR));


	CSocket::OnAccept(nErrorCode);
}
