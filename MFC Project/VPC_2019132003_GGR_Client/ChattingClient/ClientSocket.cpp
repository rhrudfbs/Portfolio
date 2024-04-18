#include "pch.h"
#include "ClientSocket.h"
#include "ChattingClientDlg.h"

void CClientSocket::OnClose(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	ShutDown();
	Close();
	CSocket::OnClose(nErrorCode);
	AfxMessageBox(_T("ERROR : Disconnected from server!"));
}


void CClientSocket::OnReceive(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	char szBuffer[1024];
	::ZeroMemory(szBuffer, 1024);
	//실제로데이터를수신한다.
	if (int bytesRead = Receive(szBuffer, sizeof(szBuffer) - 1) > 0)
	{
		//수신한메시지를리스트에출력한다.
		szBuffer[bytesRead] = '\0';
		CString F;
		F.Format(_T("%s"), szBuffer);
		CChattingClientDlg* pMain = (CChattingClientDlg*)AfxGetMainWnd();
		pMain->m_List.AddString(F);
		pMain->m_List.SetCurSel(pMain->m_List.GetCount() - 1);
	}

	CSocket::OnReceive(nErrorCode);
}
