#pragma once

// DataSocket 명령 대상

class DataSocket : public CSocket
{
public:
	DataSocket();
	virtual ~DataSocket();
	CSocket* m_pListenSocket = NULL;
	void SetListenSocket(CSocket* L)
	{
		m_pListenSocket = L;
	}
	virtual void OnClose(int nErrorCode);
	virtual void AssertValid() const;
	virtual void OnReceive(int nErrorCode);
	virtual int Receive(void* lpBuf, int nBufLen, int nFlags = 0);
};


