#pragma once
// ListenSocket 명령 대상
#include "DataSocket.h"

class ListenSocket : public CSocket
{
public:
	ListenSocket();
	virtual ~ListenSocket();
	virtual void OnAccept(int nErrorCode);
	DataSocket* pp_Data = NULL;
};


