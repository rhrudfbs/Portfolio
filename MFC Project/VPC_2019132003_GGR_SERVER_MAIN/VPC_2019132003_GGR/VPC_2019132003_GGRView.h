
// VPC_2019132003_GGRView.h: CVPC2019132003GGRView 클래스의 인터페이스
//
#include "ORBIT.h"
#include "ORBIT_SETTLE.h"
#include "PLANET.h"
#include "SETTLLITE.h"
#pragma once


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

#ifndef _DEBUG  // VPC_2019132003_GGRView.cpp의 디버그 버전
inline CVPC2019132003GGRDoc* CVPC2019132003GGRView::GetDocument() const
   { return reinterpret_cast<CVPC2019132003GGRDoc*>(m_pDocument); }
#endif

