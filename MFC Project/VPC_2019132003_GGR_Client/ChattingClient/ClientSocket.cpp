#include "pch.h"
#include "ClientSocket.h"
#include "ChattingClientDlg.h"

void CClientSocket::OnClose(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	ShutDown();
	Close();
	CSocket::OnClose(nErrorCode);
	AfxMessageBox(_T("ERROR : Disconnected from server!"));
}


void CClientSocket::OnReceive(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	char szBuffer[1024];
	::ZeroMemory(szBuffer, 1024);
	//�����ε����͸������Ѵ�.
	if (int bytesRead = Receive(szBuffer, sizeof(szBuffer) - 1) > 0)
	{
		//�����Ѹ޽���������Ʈ������Ѵ�.
		szBuffer[bytesRead] = '\0';
		CString F;
		F.Format(_T("%s"), szBuffer);
		CChattingClientDlg* pMain = (CChattingClientDlg*)AfxGetMainWnd();
		pMain->m_List.AddString(F);
		pMain->m_List.SetCurSel(pMain->m_List.GetCount() - 1);
	}

	CSocket::OnReceive(nErrorCode);
}
