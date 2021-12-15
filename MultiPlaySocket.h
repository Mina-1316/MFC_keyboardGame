#pragma once
#include "NetworkHandlerClass.h"

// MultiPlaySocket 명령 대상

//for UDP
class MultiPlaySocket : public CAsyncSocket
{
private:
	NetworkHandler* parent;		//saves parent window.

public:
	MultiPlaySocket();
	virtual ~MultiPlaySocket();

	//Event Handler
	void setParentWnd(NetworkHandler* parent);

	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
};


